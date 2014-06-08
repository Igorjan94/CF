mkdir -p /home/igorjan/documents/timetable
rm -f /home/igorjan/documents/timetable/Лигово-Спб.txt
rm -f /home/igorjan/documents/timetable/Лигово-Тайцы.txt
rm -f /home/igorjan/documents/timetable/Спб-Лигово.txt
rm -f /home/igorjan/documents/timetable/Спб-Зеле.txt
rm -f /home/igorjan/documents/timetable/Зеле-Спб.txt
rm -f /home/igorjan/documents/timetable/Тайцы-Лигово.txt
python3 /home/igorjan/206round/loadtimetable.py
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Ligovo-Spb.txt >/home/igorjan/documents/timetable/Лигово-Спб.txt 
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Tai-Ligovo.txt >/home/igorjan/documents/timetable/Taйцы-Лигово.txt
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Ligovo-Tai.txt >/home/igorjan/documents/timetable/Лигово-Тайцы.txt
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Spb-Ligovo.txt >/home/igorjan/documents/timetable/Спб-Лигово.txt
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Spb-Zele.txt >/home/igorjan/documents/timetable/Спб-Зеле.txt 
python3 /home/igorjan/206round/timetableparser.py /home/igorjan/documents/timetable/Zele-Spb.txt >/home/igorjan/documents/timetable/Зеле-Спб.txt 
