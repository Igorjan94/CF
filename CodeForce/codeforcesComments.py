import requests
import threading
from time import sleep
from html.parser import HTMLParser
import multiprocessing
from multiprocessing import Manager
import cherrypy_cors
import cherrypy
import json
import sys

manager = Manager()
comments = manager.dict()
users = manager.dict()
blogs = manager.dict()
usersToServer = manager.list()
commentsToServer = manager.list()
blogsToServer = manager.list()
SLEEP_RECENT = 60 * 30
SLEEP_BIG_UPDATE = 3600 * 40
COUNT_COMMENTS_TO_WATCH = 50
MIN_RATING_TO_WATCH = 100
MIN_BLOG_TO_WATCH = 20
path = '/home/igorjan/206round/CodeForce'
port = 2929
host = "192.168.2.6"

# {{{
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
        self.avatar = False
        self.user = ''
        self.blogId = blogId
        self.postRating = False
        self.author = ''
        self.getAuthor = False
        self.blogRating = 0

    def handle_starttag(self, tag, attrs):
        if tag == 'div':
            if attrs == [('class', 'avatar')]:
                self.avatar = True
            if attrs == [('class', 'right-meta')]:
                self.getAuthor = True
        if tag == 'a' and self.avatar:
            (_, self.user) = attrs[0]
            self.avatar = False
        if tag == 'a' and self.getAuthor:
            (_, self.author) = attrs[0]
            blogs[self.blogId] = (self.blogRating, self.author.rsplit('/', 2)[-1])
            self.getAuthor = False
        if tag == 'span':
            if len(attrs) >= 3:
                x, commentId = attrs[0]
                if x == 'commentid':
                    index = 1
                    if len(attrs) == 4:
                        index += 1
                    _, count = attrs[index]
                    name = self.user.rsplit('/', 2)[-1]
                    count = int(count)
                    if abs(count) >= COUNT_COMMENTS_TO_WATCH: # HERE
                        comments[commentId] = (name, int(count), self.blogId)
                    if name in users:
                        users[name] += count
                    else:
                        users[name] = count
            elif len(attrs) >= 2:
                x, title = attrs[0]
                if x == 'title' and title == "Рейтинг текста":
                    self.postRating = True

    def handle_data(self, data):
        if self.postRating:
            self.blogRating = int(data)
            self.postRating = False
# }}}

def proceedArray(x, **kwargs):
    if not 'from' in kwargs:
        fromIndex = 0
    else:
        fromIndex = int(kwargs['from'])
    if not 'count' in kwargs:
        toIndex = fromIndex + 10
    else:
        toIndex = fromIndex + int(kwargs['count'])
    if 'reversed' in kwargs:
        x2 = list(reversed(x))
    else:
        x2 = x
    if 'username' in kwargs:
        x2 = list(filter(lambda x: kwargs['username'] in x['username'], x2))
    length = len(x2)
    toIndex = min(toIndex, length)

    return json.dumps({'length': length, 'data': x2[fromIndex:toIndex]})

class CodeForcesServer(object):

    @cherrypy.expose
    def default(self, *args, **kwargs):
        try:
            x, y = args
            if x == 'js' or x == 'css' or x == 'tpl':
                return open(path + '/resources/' + x + '/' + y, 'r')
            if x == 'fonts':
                return open(path + '/resources/' + x + '/' + y, 'rb')
            return open(path + '/index.html', 'r')
        except:
            return open(path + '/index.html', 'r')

    @cherrypy.expose
    def comments(self, **kwargs):
        global commentsToServer
        return proceedArray(commentsToServer, **kwargs)

    @cherrypy.expose
    def blogs(self, **kwargs):
        global blogsToServer
        return proceedArray(blogsToServer, **kwargs)

    @cherrypy.expose
    def users(self, **kwargs):
        global usersToServer
        return proceedArray(usersToServer, **kwargs)

def updateRecentActions():
    print("updating recent actions")
    url = 'http://codeforces.com/?locale=ru'
    parser = CodeForcesRecentActionsParser()
    data = requests.get(url)
    if data.status_code != 200:
        print("пицоооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооооот")
    else:
        parser.feed(data.text)
    print("updated recent actions")
    return parser.recent

def parseBlog(blogId):
    print("parsing blog", blogId)
    url = 'http://codeforces.com/blog/entry/' + blogId + '?locale=ru'
    parser = CodeForcesBlogParser(blogId)
    response = requests.get(url)
    if len(response.history) == 0 and response.status_code == 200:
        parser.feed(response.text)
    else:
        if response.status_code != 200:
            print(response.status_code, " in ", blogId)
        else:
            print(response.history, " in ", blogId)
    print("parsed blog", blogId)

def dumpFile(x, f):
    qwer = open(path + '/' + f + '.json', 'w')
    qwer.write(json.dumps(x))
    qwer.close()


def updateBlogsFromRecentActions():
    while True:
        print("update blogs thread")
        global recentBlogs
        global pool
        global commentsToServer
        global usersToServer
        global blogsToServer
        pool.map(parseBlog, recentBlogs)
        recentBlogs = set()

        commentsToServer = []
        for u, (x, y, z) in comments.items():
            commentsToServer.append({'count': y, 'username': x, 'commentId': u, 'postId' : z})
        commentsToServer = list(reversed(sorted(commentsToServer, key=lambda x: x["count"])))
        i = 0;
        for comment in commentsToServer:
            i += 1
            comment['id'] = i


        usersToServer = []
        for name, count in users.items():
            if abs(int(count)) > MIN_RATING_TO_WATCH: # HERE
                usersToServer.append({'username': name, 'count': count})
        usersToServer = list(reversed(sorted(usersToServer, key=lambda x: x["count"])))
        i = 0;
        for comment in usersToServer:
            i += 1
            comment['id'] = i


        blogsToServer = []
        for blogId, (count, name) in blogs.items():
            if abs(int(count)) > MIN_BLOG_TO_WATCH: # HERE
                blogsToServer.append({'username': name, 'count': count, 'postId': blogId})
        blogsToServer = list(reversed(sorted(blogsToServer, key=lambda x: x["count"])))
        i = 0;
        for comment in blogsToServer:
            i += 1
            comment['id'] = i


        print("updated blogs thread")
        dumpFile(commentsToServer, 'comments')
        dumpFile(usersToServer, 'users')
        dumpFile(blogsToServer, 'blogs')
        print("saved into comments.json blogs thread")
        sleep(SLEEP_BIG_UPDATE)


def recentActionsThread():
    while True:
        print("recent blogs thread")
        sleep(SLEEP_RECENT)
        global recentBlogs
        recentBlogs = recentBlogs.union(updateRecentActions())

def main():
    global recentBlogs
    global pool
    global commentsToServer
    global usersToServer
    pool = multiprocessing.Pool()

    # recentBlogs = json.loads(open('comments.json', 'r').read())
    recentBlogs = set()
    try:
        qwer = open(path + '/comments.json', 'r')
        wert = qwer.readline()
        commentsToServer = json.loads(wert)
        for comment in commentsToServer:
            comments[comment['commentId']] = (comment['username'], comment['count'], comment['postId'])
        qwer.close()
    except:
        print(42)
        # recentBlogs = set(map(str, range(1, 25000)))
        recentBlogs = recentBlogs.union(updateRecentActions())

    try:
        qwer = open(path + '/blogs.json', 'r')
        wert = qwer.readline()
        blogsToServer = json.loads(wert)
        for blog in blogsToServer:
            blogs[blog['postId']] = (blog['count'], blog['username'])
    except:
        print("ok")

    try:
        qwer = open(path + '/users.json', 'r')
        wert = qwer.readline()
        usersToServer = json.loads(wert)
        for user in usersToServer:
            users[user['username']] = user['count']
    except:
        print("ok")
    download1 = threading.Thread(target=updateBlogsFromRecentActions)
    download2 = threading.Thread(target=recentActionsThread)
    download1.start()
    download2.start()

    conf = {
        '/': {
            'tools.sessions.on': True,
            'cors.expose.on': True,
        },
        '/generator': {
            'request.dispatch': cherrypy.dispatch.MethodDispatcher(),
            'tools.response_headers.on': True,
            'tools.response_headers.headers': [('Content-Type', 'text/plain')],
        },
    }
    cherrypy_cors.install()
    webapp = CodeForcesServer()
    cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"
    cherrypy.config.update({'server.socket_port': port, 'server.socket_host': host})
    cherrypy.quickstart(webapp, '/', conf)
    download1.join()
    download2.join()


if __name__ == "__main__":
    main()
