#!/bin/bash

COUNTER=1
RADIOLIST=""  # variable where we will keep the list entries for radiolist dialog
OLD=$IFS
IFS=$'\n' 
ar=()
count=15
minutesBefore=57
choose="/home/igorjan/new/Санкт-Петербург—Лигово.out"
gap=7

OPTS=`getopt -o b:c:h:g: -l before:,count:,choose:,gap:,help -- "$@"`
if [ $? != 0 ]; then exit 1; fi
eval set -- "$OPTS"

usage () {
    echo "-o b:c:h:g: -l before:,count:,choose:,gap:,help"
    exit 0
}

#parsing arguments
while true ; do
    case "$1" in
        -h | --help  ) usage           ; shift;;
        -b | --before) minutesBefore=$2; shift 2;;
        -c | --count ) count=$2        ; shift 2;;
        -g | --gap   ) gap=$2          ; shift 2;;
        --choose     ) choose=$2       ; shift 2;;
        --           ) shift           ; break;;
    esac
done
minutesBeforeCritical=$(($minutesBefore - $gap))


for i in $(cat $choose | tail -$count); do
    train=${i:0:5}
    desc=${i:6}
    desc=`sed -E "s/\s+/ /g" <<< $desc`
    desc=`sed "s/^\s//g" <<< $desc`
    desc=`sed "s/\s$//g" <<< $desc`
    off=off
    if [ "$train" == "20:10" ]; then off=on; fi
    ar+=($train "$desc" $off)
done
IFS=$OLD
exec 3>&1;

result=$(dialog --title "Choose train" --default-item "20:10" --radiolist "Time" 0 0 $count "${ar[@]}" 2>&1 1>&3);
exec 3>&-;
minsWarning=`date +%H:%M --date "$result -GMT+3 -$minutesBefore min"`
minsCritical=`date +%H:%M --date "$result -GMT+3 -$minutesBeforeCritical min"`
spaces="                                                                                                                                                                                                        "
for i in $(atq | cut -f 1); do atrm $i; done
at "$minsWarning" <<< "DISPLAY=:0 notify-send -u critical -i dialog-information 'Warning!!!' '\n\n\nРаспидорит электричку $result. Осталось $minutesBefore минут до электрички! $spaces'" 1>&2
at "$minsCritical" <<< "DISPLAY=:0 notify-send -u critical -i dialog-information 'Critical!!!' '\n\n\nУже пидорит электричку $result. Осталось $minutesBeforeCritical минут до электрички! $spaces'" 1>&2
echo "Notifications are installed to $minsWarning and $minsCritical!"
