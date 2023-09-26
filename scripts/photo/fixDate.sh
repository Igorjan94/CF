dateRegex="^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9]\ [0-9][0-9]:[0-9][0-9]:[0-9][0-9]$"
dateShortRegex="^[0-9][0-9][0-9][0-9]-[0-9][0-9]-[0-9][0-9] +"
for f in "$@"; do
    date=$(exiv2 -p e "$f" | grep 'Exif.Photo.DateTimeOriginal' | awk '{print $4 " " $5;}' | sed 's/:/-/' | sed 's/:/-/')
    #date=${date//-/:}
    #date=${date/:/-}
    #date=${date/:/-}
    shift='+0300'
    echo "Trying date $f '$date'"
    if [[ ${date} = '' ]]; then
        date=$(ffmpeg -i "$f" 2>&1 | grep creation_time | head -1 | awk '{ print $3;}' | sed 's/[TZ]/ /g' | sed 's/\.000000//')
        if [[ ${date} = '' ]]; then
            echo "SKIP $f $date"
            ffmpeg -i "$f"
            continue
        fi
        shift='+0000'
    elif ! [[ ${date} =~ $dateRegex ]]; then
        if [[ ${date} =~ $dateShortRegex ]]; then
            #date="${date}00:00"
            echo "Found short date $f $date"
        else
            date=$(exiv2 -p e "$f" | grep 'Exif.Image.DateTime' | awk '{print $4 " " $5; }' | sed 's/:/-/' | sed 's/:/-/')
            echo "Trying original $f $date"
            if ! [[ ${date} =~ $dateRegex ]]; then
                if [[ ${date} =~ $dateShortRegex ]]; then
                    date="${date}00:00"
                    echo "Found short date $f $date"
                else
                    echo "SKIP $f $date"
                    exiv2 -p e "$f"
                    continue
                fi
            fi
        fi
    fi
    echo "Date found $f $date $shift"
    exiv2 -v -M"set Exif.Image.DateTime $date" $f 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.DateTimeDigitized $date" $f 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.DateTimeOriginal $date" $f 1>/dev/null 2>&1
    touch -d "$date $shift" "$f"
done
