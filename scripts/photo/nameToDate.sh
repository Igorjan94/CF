dateRegex="IMG_([0-9][0-9][0-9][0-9])([0-9][0-9])([0-9][0-9])_([0-9][0-9])([0-9][0-9])([0-9][0-9])"
shift="+0300"
for f in "$@"; do
    if [[ ${f} =~ $dateRegex ]]; then
        year=${BASH_REMATCH[1]}
        month=${BASH_REMATCH[2]}
        day=${BASH_REMATCH[3]}
        hour=${BASH_REMATCH[4]}
        minute=${BASH_REMATCH[5]}
        second=${BASH_REMATCH[5]}
        date="$year-$month-$day $hour:$minute:$second"
        echo "Date found $f $date"
        exiv2 -v -M"set Exif.Image.DateTime $date" $f 1>/dev/null 2>&1
        exiv2 -v -M"set Exif.Image.DateTimeOriginal $date" $f 1>/dev/null 2>&1
        touch -d "$date $shift" "$f"
    fi
done
