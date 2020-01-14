import os
import time
import datetime
from os import listdir
from os.path import isfile, join

from library import *

url = 'https://static-maps.yandex.ru/1.x/?lang=ru_RU&l=map&pl='

def degsToDegs(f):
    degs = int(f[:2])
    mins = int(f[2:4])
    secs = int(f[5:7])
    msecs = int(f[7:9])
    return degs + mins / 60 + secs / 60 / 100 + msecs / 60 / 100 / 100

def getTimeFromString(s, format):
    return int(time.mktime(datetime.datetime.strptime(s, format).timetuple()))


def gpsToHtml(filename, yandex, output):
    rl = filename.readlines()
    start = rl[0].split('/')[3][:-4]
    start = getTimeFromString(start, '%Y%m%d%H%M%S')
    title = datetime.datetime.fromtimestamp(start).strftime('%Y-%m-%d %H:%M:%S')
    lines = list(map(lambda line: line[:-1].split(','), filter(lambda line: line.startswith('$GPRMC'), rl)))
    coords = []
    for line in lines:
        t = line[9][:4] + '20' + line[9][4:] + line[1].split('.')[0]
        t = getTimeFromString(t, '%d%m%Y%H%M%S') + int(line[1][7:]) / 1000
        coords.append([t, degsToDegs(line[3]), degsToDegs(line[5]), float(line[7]) * 1.852])

    points = []
    speeds = []
    commands = []
    last = 0
    lastTime = start
    for t, x, y, s in coords:
        points.append([str(x)[:9], str(y)[:9]])
        speeds.append(int(s))
        commands.append(f"drawtext=text='{int(last)} km/h':enable='between(t,{lastTime - start:.2f},{t - start:.2f})':x=10:y=H-th-10:fontsize=40:fontcolor=red")
        last = s
        lastTime = t

    points = ', '.join(map(lambda x: '[' + ', '.join(x) + ']', points))
    if points:
        output.write(''.join(yandex).replace('POINTS', points).replace('TITLE', title))
        output.close()
    else:
        os.unlink(output.name)
    filename.close()
    print(', \\\n'.join(commands))


@completion.command()
@click.argument('filename', required=True, type=click.File('r'), nargs=1)
@click.option('-y', '--yandex', help='index', type=click.File('r'), default='./yandexMap/index.html')
def getMap(filename, yandex):
    gpsToHtml(filename, yandex.readlines(), open(filename.name.rsplit('.', 1)[0] + '.html', 'w'))

@completion.command()
@click.argument('dir', required=True, type=click.Path(file_okay=False), nargs=1)
@click.option('-y', '--yandex', help='index', type=click.File('r'), default='./yandexMap/index.html')
def getMaps(dir, yandex):
    html = yandex.readlines()
    for f in listdir(dir):
        filename = join(dir, f)
        if isfile(filename) and filename.endswith('.LOG'):
            gpsToHtml(open(filename, 'r'), html, open(filename.rsplit('.', 1)[0] + '.html', 'w'))
    yandex.close()

if __name__ == "__main__":
    completion()
