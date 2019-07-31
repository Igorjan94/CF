import requests
import random
import json
import time

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

json.loads = decorateFunction(json.loads)
requests.Response.json = decorateFunction(requests.Response.json)
