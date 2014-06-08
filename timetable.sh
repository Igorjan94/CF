a=$2
b=$1
if [ $# -le 1 ]
	then a="/home/igorjan/206round"
fi
if [ $# -eq 0 ]
	then b="/home/igorjan/documents/timetable"
fi
mkdir -p $b
c="$a/timetableparser.py"
a="$a/loadtimetable.py"
python3 $a $b 101 701
python3 $a $b 701 101
python3 $a $b 701 1201
python3 $a $b 1201 701
python3 $a $b 20600 41405
python3 $a $b 41405 20600

python3 $c $b/Лигово-Санкт-Петербург.txt $b/Лигово-Спб.txt 
python3 $c $b/Тайцы-Лигово.txt $b/Taй-Лигово.txt
python3 $c $b/Лигово-Тайцы.txt $b/Лиг-Тайцы.txt
python3 $c $b/Санкт-Петербург-Лигово.txt $b/Спб-Лигово.txt
python3 $c $b/Санкт-Петербург-Зеленогорск.txt $b/Спб-Зеле.txt 
python3 $c $b/Зеленогорск-Санкт-Петербург.txt $b/Зеле-Спб.txt 
