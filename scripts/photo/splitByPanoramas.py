#!/usr/bin/env python3

import PIL.Image
import PIL.ExifTags

import sys
sys.path.append('/home/igorjan/206round/scripts')

from library import *

def getDate(x):
    return datetime.datetime.strptime(x, '%Y:%m:%d %H:%M:%S')

@completion.command()
@click.argument('directory', required=True, type=click.Path(file_okay=False), nargs=1)
def findPanos(directory):
    def getExif(filename):
        try:
            img = PIL.Image.open(os.path.join(directory, filename))
            return dotdict({
                PIL.ExifTags.TAGS[k]: v
                for k, v in img._getexif().items()
                if k in PIL.ExifTags.TAGS
            }, filename = filename)
        except IOError:
            print(filename, 'is not an image')
            return None

    panos = []
    cur = []
    exifs = list(filter(lambda x: x, map(lambda filename: getExif(filename), os.listdir(directory))))
    exifs.sort(key = lambda x: getDate(x.DateTime))

    def isPortrait(exif):
        return exif.ExifImageWidth < exif.ExifImageHeight or exif.Orientation is not None and exif.Orientation % 2 == 0

    for exif in exifs:
        if cur:
            last = cur[-1]
            diff = (getDate(exif.DateTime) - getDate(last.DateTime)).total_seconds()
            # print(last.ExifImageWidth, last.ExifImageHeight, last.Model, last.Orientation)
            if isPortrait(exif) and diff < 60 and diff > 0 and last.Model == exif.Model and last.ExifImageWidth == exif.ExifImageWidth and last.ExifImageHeight == exif.ExifImageHeight:
                cur.append(exif)
            else:
                if len(cur) > 1:
                    panos.append(cur)
                if isPortrait(exif):
                    cur = [exif]
                else:
                    cur = []
        elif isPortrait(exif):
            cur = [exif]
    if len(cur) > 1:
        panos.append(cur)
    for (i, pano) in enumerate(panos):
        # print(i, pano)
        dst = os.path.join(directory, str(i + 1))
        os.mkdir(dst)
        for exif in pano:
            filename = exif.filename
            os.rename(os.path.join(directory, filename), os.path.join(dst, filename))

if __name__ == "__main__":
    completion()
