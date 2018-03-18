#!/usr/bin/env python3

import re
import os.path
import argparse
import sys
from pytube import YouTube
import subprocess

def getTime(kwargs):
    since = kwargs.since
    if kwargs.duration != None:
        return '-ss {0} -t {1}'.format(since, kwargs.duration)
    if kwargs.till != None:
        return '-ss {0} -to {1}'.format(since, kwargs.till)
    return '-ss {}'.format(since)

def fileExists(path):
    return os.path.exists(path)

def isUrl(url):
    ok = re.match(r'http://youtube.com/watch\?((?:v=|\/)([0-9A-Za-z_-]{11}).*)', url) != None or \
         re.match(r'https://www.youtube.com/watch\?((?:v=|\/)([0-9A-Za-z_-]{11}).*)', url) != None or \
         fileExists(url)
    if ok:
        return url
    raise argparse.ArgumentTypeError('{0} is not correct youtube url'.format(url))


parser = argparse.ArgumentParser()
parser.add_argument('-s', '--since',    dest = 'since',    type = str,   default = '0'  )
parser.add_argument('-t', '--till',     dest = 'till',     type = str                   )
parser.add_argument('-d', '--duration', dest = 'duration', type = str                   )
parser.add_argument('-o', '--output',   dest = 'output',   type = str                   )
parser.add_argument('-v', '--verbose',  dest = 'verbose',  action = 'store_true'        )
parser.add_argument('url',                                 type = isUrl                 )

args = parser.parse_args()
time = getTime(args)

FFMPEG = 'ffmpeg -i "{0}" {1} -acodec aac -b:a 192k -avoid_negative_ts make_zero "{2}"'
FFMPEGAUDIO = 'ffmpeg -i "{0}" {1} -i "{2}" {1} -acodec aac -b:a 192k -avoid_negative_ts make_zero -map 0:v:0 -map 1:a:0 "{3}"'

def trimDigits(x):
    return int(re.split('^(\d+)', x)[1])

if not args.verbose:
    FFMPEG += ' -v fatal -stats'
    FFMPEGAUDIO += ' -v fatal -stats'

if fileExists(args.url):
    download_file_path = args.url
    if args.output != None: download_file_path = args.output

    process_call_str = FFMPEG.format(args.url, time, download_file_path)
else:
    yt = YouTube(args.url)
    download_file_path = '{0}.mp4'.format(yt.title)
    if args.output != None: download_file_path = args.output

    videos, audios = {}, {}
    for stream in yt.streams.all():
        if stream.resolution != None:
            videos[trimDigits(stream.resolution)] = stream
        if stream.abr != None:
            audios[trimDigits(stream.abr)] = stream
    video = videos[max(videos)]
    if not video.audio_codec:
        audio = audios[max(audios)]
        process_call_str = FFMPEGAUDIO.format(video.url, time, audio.url, download_file_path)
    else:
        process_call_str = FFMPEG.format(video.url, time, download_file_path)

status = subprocess.check_call(process_call_str, shell = True)

