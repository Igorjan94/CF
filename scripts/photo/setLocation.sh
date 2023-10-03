#!/usr/bin/env bash
dir="$2"
[[ -z "$dir" ]] && dir="."

latlong=$(cat /home/igorjan/documents/geolocations.txt | grep $1 | awk '{$1=""; print $0}')
echo $latlong
updateExif.sh $latlong "$dir"
