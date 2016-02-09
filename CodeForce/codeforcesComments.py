import requests
import threading
from time import sleep
from html.parser import HTMLParser
import multiprocessing
from multiprocessing import Manager


manager = Manager()
comments = manager.dict()
users = manager.dict()


class CodeForcesRecentActionsParser(HTMLParser):

    def __init__(self):
        HTMLParser.__init__(self)
        self.recentActions = False
        self.li = False
        self.recent = set()

    def handle_starttag(self, tag, attrs):
        if tag == 'div':
            if attrs == [('class', 'recent-actions')]:
                self.recentActions = True
        elif tag == 'li':
            self.li = True
        elif tag == 'a' and self.recentActions and self.li and len(attrs) == 1:
            (x, y) = attrs[0]
            self.recent.add(y.rsplit('/', 2)[-1])

    def handle_endtag(self, tag):
        if tag == 'div' and self.recentActions and not self.li:
            self.recentActions = False
        if tag == 'li' and self.recentActions:
            self.li = False

class CodeForcesBlogParser(HTMLParser):

    def __init__(self, blogId):
        HTMLParser.__init__(self)
        self.comments = {}
        self.avatar = False
        self.user = ''
        self.blogId = blogId

    def handle_starttag(self, tag, attrs):
        if tag == 'div':
            if attrs == [('class', 'avatar')]:
                self.avatar = True
        if tag == 'a' and self.avatar:
            (_, self.user) = attrs[0]
            self.avatar = False
        if tag == 'span' and len(attrs) == 3:
            x, commentId = attrs[0]
            if x == 'commentid':
                _, count = attrs[1]
                # global comments
                # global users
                name = self.user.rsplit('/', 2)[-1]
                count = int(count)
                if abs(count) > 50:
                    comments[commentId] = (name, int(count), self.blogId)
                if name in users:
                    users[name] += count
                else:
                    users[name] = count

def updateRecentActions():
    url = 'http://codeforces.com'
    parser = CodeForcesRecentActionsParser()
    parser.feed(requests.get(url).text)
    return parser.recent

def parseBlog(blogId):
    print("parsing", blogId)
    url = 'http://codeforces.com/blog/entry/' + blogId
    parser = CodeForcesBlogParser(blogId)
    responce = requests.get(url)
    if responce.status_code == 200:
        parser.feed(responce.text)

def updateBlogsFromRecentActions():
    i = 0
    while i < 2:
        sleep(2)
        i += 1
        global recentBlogs
        global pool
        pool.map(parseBlog, recentBlogs)
        recentBlogs = set()

def recentActionsThread():
    i = 0
    while i < 1:
        i += 1
        global recentBlogs
        recentBlogs = recentBlogs.union(updateRecentActions())
        print("recentBlogs", recentBlogs)
        sleep(5)

def main():
    global recentBlogs
    global pool
    pool = multiprocessing.Pool()
    # parseBlog('15540')
    recentBlogs = set()
    download1 = threading.Thread(target=updateBlogsFromRecentActions)
    download2 = threading.Thread(target=recentActionsThread)
    download1.start()
    download2.start()
    download1.join()
    download2.join()
    extr = []
    for u, (x, y, z) in comments.items():
        extr.append((y, x, u, z))
    print(sorted(extr, key=lambda x: x[0]))

    extr = []
    for name, count in users.items():
        extr.append((name, count))
    print(list(reversed(sorted(extr, key=lambda x: x[1]))))

if __name__ == "__main__":
    main()
