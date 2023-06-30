o="[0-9]*.jpg"
dir=${PWD##*/}
for i in $(ls); do
    if [[ -f $i ]]; then
        continue
    fi
    cd $i
    f=$(ls *IMG* | head -1)
    echo $i $f
    ex=$(exiv2 -p e $f | awk {'{printf $1 "\n"; }'})
    for exifName in $ex; do
        exiv2 -v -M"set $exifName $(exiv2 -p e $f | grep $exifName | head -1 | awk {'{for (i=4; i<NF; i++) printf $i " "; print $NF}'})" $o 1>/dev/null 2>&1
    done
    exiv2 -v -M"set Exif.Image.Orientation 1" $o 1>/dev/null

    for j in $o; do
        if [[ -f $j ]]; then

            #exiv2 $f | grep timestamp | awk '{print $4$5}' | sed 's/:/ /g' | awk '{print $2$3$4}'
            #touch -amt $(exiv2 $f | grep timestamp | awk '{print $4$5}' | sed 's/:/ /g' | awk '{print $2$3$4}') $j
            d="$(date -r $f '+%Y-%m-%d %T %z')"
            echo "touch -d $d $j"
            touch -d "$d" $j
            #touch -amt "04272320" $j
        fi
    done
    for j in $o; do
        if [[ -f $j ]]; then
            echo $dir$j
            cp -p "$j" "../$dir$j"
        fi
    done
    cd ..
done
