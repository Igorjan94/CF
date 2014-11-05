#usage: ./timetable.sh [destination_directory] [source_directory]

#setting default directories
a="/home/igorjan/206round/timetable"
b="/home/igorjan/documents/timetable"
flag=0;
today=0;

while getopts "0ts:d:" opt; do
  case $opt in
    \?) exit 1;;
    s) a=$OPTARG;;
    d) b=$OPTARG;;
    0) flag=1;;
    t) today=1;;
  esac
done

shift $(($OPTIND - 1))
if [ $# -eq 0 ]
	then echo "usage: ./timetable.sh [-d <destination_directory>] [-s <source_directory>] \"from1 to1 ... fromN toN\""
	exit
fi

arg=$1

#create source_directory, clean temporary files
mkdir -p $b
rm -f $b/*.my

#setting script pathes
c="$a/timetableparser.py"
a="$a/loadtimetable.py"

#downloading timetable
if [ $today -eq 1 ]
    then python3 $a $b -t $arg
else
    python3 $a $b $arg
fi

#parsing every downloaded file
for file in $b/*.my
do
    if [ $flag -eq 0 ]
        then python3 $c $file $file.out
    else
        python3 $c $file $file.out 1
    fi
done 

#final renaming and deleting temp files
rm -f $b/*.my
rename '.my.out' '.out' $b/*
