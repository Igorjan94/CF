
d=$(exiv2 -p e $1 | grep Exif.Image.DateTime | head -1 | awk {'print $4 " " $5'})
d=${d/:/-}
d=${d/:/-}
echo "touch -d $d $1"
exiv2 -v -M"set Exif.Image.DateTime " $d 1>/dev/null 2>&1
touch -d "$d +0300" $1
