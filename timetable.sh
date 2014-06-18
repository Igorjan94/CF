#usage: ./timetable.sh destination_directory source_directory
a=$2
b=$1

#setting default directories
if [ $# -le 1 ]
	then a="/home/igorjan/206round"
fi
if [ $# -eq 0 ]
	then b="/home/igorjan/documents/timetable"
fi

#create source_directory, clean temporary files
mkdir -p $b
rm -f $b/*.txt

#setting script pathes
c="$a/timetableparser.py"
a="$a/loadtimetable.py"

#downloading timetable
python3 $a $b 101 701
python3 $a $b 701 101
python3 $a $b 701 1201
python3 $a $b 1201 701
python3 $a $b 20600 41405
python3 $a $b 41405 20600

#parsing every downloaded file
for file in $b/*.txt
do
	python3 $c $file $file.out 1
done 

#final renaming and deleting temp files
rm $b/*.txt
rename '.out' '' $b/*
