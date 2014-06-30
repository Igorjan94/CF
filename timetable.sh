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
python3 $a $b "Лигово" "Тайцы"\
 "Тайцы" "Лигово"\
 "Лигово" "Санкт-Петербург-Балт."\
 "Санкт-Петербург-Балт." "Лигово"\
 "Санкт-Петербург-Финл." "Зеленогорск"\
 "Зеленогорск" "Санкт-Петербург-Финл."

#parsing every downloaded file
for file in $b/*.txt
do
	python3 $c $file $file.out 1
done 

#final renaming and deleting temp files
rm -f $b/*.txt
rename '.out' '' $b/*
