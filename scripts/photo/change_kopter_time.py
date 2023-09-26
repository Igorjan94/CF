import os
import sys
import re
import datetime
import shutil
import piexif

rootdir = sys.argv[1]

def updateExifDate(filename, date):
    exif_dict = piexif.load(filename)
    exif_date = date.strftime("%Y:%m:%d %H:%M:%S")
    exif_dict['0th'][piexif.ImageIFD.DateTime] = new_date
    exif_dict['Exif'][piexif.ExifIFD.DateTimeOriginal] = new_date
    exif_dict['Exif'][piexif.ExifIFD.DateTimeDigitized] = new_date
    exif_bytes = piexif.dump(exif_dict)
    piexif.insert(exif_bytes, filename)

def changeDate(filename, date):
    int_date = int(date.timestamp())
    os.utime(filename, (int_date, int_date))

for subdir, dirs, files in os.walk(rootdir):
    for file in files:
        d = re.search(r'VID_(\d{4})(\d{2})(\d{2})_(\d{2})(\d{2})(\d{2})', subdir)
        if not d: continue
        groups = [int(d.group(i)) for i in range(1, 7)]
        date = datetime.datetime(*groups)
        m = re.search(r'(\d{2})_(\d{2})_(\d{2})-outof-(\d{2})_(\d{2})_(\d{2})', file)
        if not m: continue
        groups = [int(m.group(i)) for i in range(1, 7)]
        delta = datetime.timedelta(hours=groups[0], minutes=groups[1], seconds=groups[2])
        date += delta
        # delta = datetime.timedelta(hours=groups[3], minutes=groups[4], seconds=groups[5])
        # date -= delta
        p = os.path.join(subdir, file)
        new_path = os.path.join(rootdir, file)
        # updateExifDate(p, date)
        shutil.copyfile(p, new_path)
        changeDate(p, date)
        changeDate(new_path, date)
