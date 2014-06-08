from bs4 import BeautifulSoup
from urllib.request import urlopen
import re
import sys

directory = sys.argv[1]
fro = sys.argv[2]
to = sys.argv[3]

def parse(url):
	html_doc = urlopen(url).read()
	soup = BeautifulSoup(html_doc)

	for entry in soup:
		lines = re.split('\n', str(entry))
		temp = 0
		for line in lines:
			if line.find('<title>') != -1:
				line = re.sub(r'^.*?<title>Расписание электричек (.*?)\..*', r'\1', line)
				line = re.sub(r'\s', '', line)
				sys.stdout = open(directory + '/' + line + '.txt', 'w+')
				continue
			line = re.sub(r'<a href=".*?">(.*?)</a>', r'\1', line)
			line = re.sub(r'^\s+(.*?)\s+</td>', r'\1', line)
			line = re.sub(r'$nbsp;', r' ', line)
			line = re.sub(r'<span class="miniNbsp">', r'', line)
			line = re.sub(r'</span>', r'', line)
			line = re.sub(r'^\s+(\d+.*?(м|ч).*?)', r'\1', line)
			line = re.sub(r'^[#a-zA-Z-<_\s$(.{}/].*', r' ', line)
			line = re.sub(r'^\s+', r'', line)
			if not line.startswith(' ') and not line.startswith('	') and not line == '':
				if temp == 0:
					cur = '		' + line
				else:
					cur = cur + '		' + line
				temp = temp + 1
			if temp == 6:
				temp = 0
				print(cur)
url = 'http://www.tutu.ru/spb/rasp.php?st1=' + fro + '&st2=' + to + '&print=yes'
parse(url)