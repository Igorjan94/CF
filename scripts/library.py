import requests
import random
import json
import time
import os

import click
import click_completion
import click_completion.core

click_completion.init()

@click.group()
def completion():
    pass

@completion.command()
@click.option('--append/--overwrite', help="Append the completion code to the file", default=None)
@click.argument('shell', required=False, type=click_completion.DocumentedChoice(click_completion.core.shells))
@click.argument('path', required=False)
def install(append, shell, path):
    shell, path = click_completion.core.install(shell=shell, path=path, append=append)
    click.echo('%s completion installed in %s' % (shell, path))


class dotdict(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__
    def __init__(self, *args, **kwargs):
        super(dotdict, self).__init__(*args, **kwargs)
        for d in args:
            if isinstance(d, dict):
                for key, value in d.items():
                    if isinstance(value, dict):
                        value = dotdict(value)
                    elif isinstance(value, list) and value and isinstance(value[0], dict):
                        value = list(map(dotdict, value))
                    self[key] = value

        if kwargs:
            for k, v in kwargs.items():
                self[k] = v

def decorateFunction(original):
    def decorated(*args, **kwargs): return dotdict(original(*args, **kwargs))
    return decorated

def unlimited(f, field, max_count, verbose = False, count_field = 'count', offset_field = 'offset', starting_offset = 0, **kwargs):
    kwargs[count_field] = max_count
    if not 'max_iterations' in kwargs:
        max_iterations = -1
    else:
        max_iterations = kwargs['max_iterations']

    offset = starting_offset
    res = []
    iterations = 0
    while True:
        iterations += 1
        if verbose:
            print(f'Getting {max_count}, offset {offset}')
        kwargs[offset_field] = offset
        temp = f(**kwargs)
        if not field in temp:
            time.sleep(2)
            continue
        temp = temp[field]
        if not temp: break

        res += temp
        offset += max_count
        if max_iterations != -1 and iterations >= max_iterations:
            break
        time.sleep(1 / 3)
    return res

json.loads = decorateFunction(json.loads)
requests.Response.json = decorateFunction(requests.Response.json)

def getFilename(filename):
    if filename.startswith('~'):
        filename = os.path.expanduser('~') + filename[1:]
    if not filename.startswith('.') and not filename.startswith('/'):
        filename = './' + filename
    return filename

def saveJsonInFile(j, filename):
    if type(filename) == str:
        filename = getFilename(filename)
        if not os.path.exists(os.path.dirname(filename)):
            os.makedirs(os.path.dirname(filename))
        filename = open(filename, 'w')
    filename.write(json.dumps(j, ensure_ascii=False))
    filename.close()

def loadJsonFromFile(filename):
    if type(filename) == str:
        filename = getFilename(filename)
        if not os.path.exists(filename):
            return None
        filename = open(filename, 'r')
    j = json.loads(''.join(filename.readlines()))
    filename.close()
    return j
