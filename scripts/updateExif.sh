#!/usr/bin/env bash

lat="${1/[.,]/}"
long="${2/[.,]/}"
cd "$3"

exiv2 -v\
    -M"set Exif.GPSInfo.GPSLatitude $lat/1000000 0/1 0/1"\
    -M"set Exif.GPSInfo.GPSLatitudeRef N"\
    -M"set Exif.GPSInfo.GPSLongitude $long/1000000 0/1 0/1"\
    -M"set Exif.GPSInfo.GPSLongitudeRef E" *.JPG *.jpeg *.MOV *.MP4 *.TIF;
