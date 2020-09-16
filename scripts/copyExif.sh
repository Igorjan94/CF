o="[0-9]*.jpg"
dir=${PWD##*/}
for i in $(ls); do
    if [[ -f $i ]]; then
        continue
    fi
    cd $i
    f=$(ls *IMG* | head -1)
    echo $i $f
    exiv2 -v -M"set Exif.Image.Orientation 1" $o 1>/dev/null
    exiv2 -v -M"set Exif.Image.Make $(exiv2 -p e $f | grep Exif.Image.Make | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.Model $(exiv2 -p e $f | grep Exif.Image.Model | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.Software $(exiv2 -p e $f | grep Exif.Image.Software | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.DateTime $(exiv2 -p e $f | grep Exif.Image.DateTime | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.Artist $(exiv2 -p e $f | grep Exif.Image.Artist | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.YCbCrPositioning $(exiv2 -p e $f | grep Exif.Image.YCbCrPositioning | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Image.ExifTag $(exiv2 -p e $f | grep Exif.Image.ExifTag | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.ExposureTime $(exiv2 -p e $f | grep Exif.Photo.ExposureTime | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.FNumber $(exiv2 -p e $f | grep Exif.Photo.FNumber | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.ExposureProgram $(exiv2 -p e $f | grep Exif.Photo.ExposureProgram | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.ISOSpeedRatings $(exiv2 -p e $f | grep Exif.Photo.ISOSpeedRatings | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.SensitivityType $(exiv2 -p e $f | grep Exif.Photo.SensitivityType | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.StandardOutputSensitivity $(exiv2 -p e $f | grep Exif.Photo.StandardOutputSensitivity | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.ExifVersion $(exiv2 -p e $f | grep Exif.Photo.ExifVersion | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.DateTimeOriginal $(exiv2 -p e $f | grep Exif.Photo.DateTimeOriginal | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.DateTimeDigitized $(exiv2 -p e $f | grep Exif.Photo.DateTimeDigitized | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.ComponentsConfiguration $(exiv2 -p e $f | grep Exif.Photo.ComponentsConfiguration | head -1 | awk {'print $4'})" $o 1>/dev/null
    exiv2 -v -M"set Exif.Photo.ExposureBiasValue $(exiv2 -p e $f | grep Exif.Photo.ExposureBiasValue | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.MeteringMode $(exiv2 -p e $f | grep Exif.Photo.MeteringMode | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.Flash $(exiv2 -p e $f | grep Exif.Photo.Flash | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.Photo.FocalLength $(exiv2 -p e $f | grep Exif.Photo.FocalLength | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSVersionID $(exiv2 -p e $f | grep Exif.GPSInfo.GPSVersionID | head -1 | awk {'print $4" "$5" "$6" "$7'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSLatitudeRef $(exiv2 -p e $f | grep Exif.GPSInfo.GPSLatitudeRef | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSLatitude $(exiv2 -p e $f | grep Exif.GPSInfo.GPSLatitude | tail -1 | awk {'print $4" "$5" "$6" "'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSLongitudeRef $(exiv2 -p e $f | grep Exif.GPSInfo.GPSLongitudeRef | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSLongitude $(exiv2 -p e $f | grep Exif.GPSInfo.GPSLongitude | tail -1 | awk {'print $4" "$5" "$6" "'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSAltitudeRef $(exiv2 -p e $f | grep Exif.GPSInfo.GPSAltitudeRef | head -1 | awk {'print $4'})" $o 1>/dev/null 2>&1
    exiv2 -v -M"set Exif.GPSInfo.GPSAltitude $(exiv2 -p e $f | grep Exif.GPSInfo.GPSAltitude | tail -1 | awk {'print $4" "$5" "$6" "'})" $o 1>/dev/null 2>&1

    for j in $o; do
        if [[ -f $j ]]; then

            #exiv2 $f | grep timestamp | awk '{print $4$5}' | sed 's/:/ /g' | awk '{print $2$3$4}'
            #touch -amt $(exiv2 $f | grep timestamp | awk '{print $4$5}' | sed 's/:/ /g' | awk '{print $2$3$4}') $j
            d="$(date -r $f '+%Y-%m-%d %T %z')"
            touch -d "$d" $j
            #touch -amt "04272320" $j
        fi
    done
    for j in $o; do
        if [[ -f $j ]]; then
            echo $dir$j
            cp -p $j ../$dir$j
        fi
    done
    cd ..
done
