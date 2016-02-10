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
usersToServer = manager.list()
commentsToServer = manager.list()
SLEEP_RECENT = 60 * 30
SLEEP_BIG_UPDATE = 3600 * 40
COUNT_COMMENTS_TO_WATCH = 100
MIN_RATING_TO_WATCH = 1000

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
        if tag == 'span' and len(attrs) >= 3:
            x, commentId = attrs[0]
            if x == 'commentid':
                index = 1
                if len(attrs) == 4:
                    index += 1
                _, count = attrs[index]
                name = self.user.rsplit('/', index)[-1]
                count = int(count)
                if abs(count) >= COUNT_COMMENTS_TO_WATCH: # HERE
                    comments[commentId] = (name, int(count), self.blogId)
                if name in users:
                    users[name] += count
                else:
                    users[name] = count
# }}}

class CodeForcesServer(object):

    @cherrypy.expose
    def default(self, *args, **kwargs):
        return open('index.html', 'r')

    @cherrypy.expose
    def comments(self, **kwargs):
        if not 'from' in kwargs:
            fromIndex = 0
        else:
            fromIndex = int(kwargs['from'])
        if not 'count' in kwargs:
            toIndex = fromIndex + 10
        else:
            toIndex = fromIndex + int(kwargs['count'])
        global commentsToServer
        if 'reversed' in kwargs:
            commentsToServer2 = list(reversed(commentsToServer))
        else:
            commentsToServer2 = commentsToServer
        if 'username' in kwargs:
            commentsToServer2 = list(filter(lambda x: kwargs['username'] in x['username'], commentsToServer2))
        length = len(commentsToServer2)
        toIndex = min(toIndex, length)

        return json.dumps({'length': length, 'data': commentsToServer2[fromIndex:toIndex]})

    @cherrypy.expose
    def users(self, **kwargs):
        if not 'from' in kwargs:
            fromIndex = 0
        else:
            fromIndex = int(kwargs['from'])
        if not 'count' in kwargs:
            toIndex = fromIndex + 10
        else:
            toIndex = fromIndex + int(kwargs['count'])

        global usersToServer
        if 'reversed' in kwargs:
            usersToServer2 = list(reversed(usersToServer))
        else:
            usersToServer2 = usersToServer
        if 'username' in kwargs:
            usersToServer2 = list(filter(lambda x: kwargs['username'] in x['username'], usersToServer2))
        length = len(usersToServer2)
        toIndex = min(toIndex, length)
        return json.dumps({'length': length, 'data': usersToServer2[fromIndex:toIndex]})

def updateRecentActions():
    print("updating recent actions")
    url = 'http://codeforces.com'
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
    url = 'http://codeforces.com/blog/entry/' + blogId
    parser = CodeForcesBlogParser(blogId)
    responce = requests.get(url)
    if responce.status_code == 200:
        parser.feed(responce.text)
    else:
        print(responce.status_code, " in ", blogId)
    print("parsed blog", blogId)

def updateBlogsFromRecentActions():
    while True:
        print("update blogs thread")
        global recentBlogs
        global pool
        global commentsToServer
        global usersToServer
        pool.map(parseBlog, recentBlogs)
        recentBlogs = set()

        commentsToServer = []
        for u, (x, y, z) in comments.items():
            commentsToServer.append({'count': y, 'username': x, 'commentId': u, 'postId' : z})
        commentsToServer = sorted(commentsToServer, key=lambda x: x["count"])

        usersToServer = []
        for name, count in users.items():
            if abs(int(count)) > MIN_RATING_TO_WATCH: # HERE
                usersToServer.append({'username': name, 'count': count})
        usersToServer = sorted(usersToServer, key=lambda x: x["count"])
        print("updated blogs thread")
        qwer = open('comments.json', 'w')
        qwer.write(json.dumps(commentsToServer))
        qwer.close()
        print("saved into comments.json blogs thread")
        sleep(SLEEP_BIG_UPDATE)


def recentActionsThread():
    while True:
        print("recent blogs thread")
        sleep(SLEEP_RECENT)
        global recentBlogs
        recentBlogs = recentBlogs.union(updateRecentActions())

def application(environ, start_response):
    #download1.join()
    #download2.join()
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
    cherrypy.response.headers["Access-Control-Allow-Origin"] = "*"
#    cherrypy.config.update({'server.socket_port': 2929, 'server.socket_host': '192.168.2.6'})
    cherrypy.tree.mount(CodeForcesServer(), '/', conf)
#    download1.join()
#    download2.join()
    return cherrypy.tree(environ, start_response)

print("++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++")
pool = multiprocessing.Pool()
recentBlogs = set()
try:
    qwer = open('comments.json', 'r')
    wert = qwer.readline()
    commentsToServer = json.loads(wert)
    for comment in commentsToServer:
        comments[comment['commentId']] = (comment['username'], comment['count'], comment['postId'])
    qwer.close()
except:
    # recentBlogs = set(map(str, range(1, 24)))
    recentBlogs = recentBlogs.union(updateRecentActions())
print(recentBlogs)
download1 = threading.Thread(target=updateBlogsFromRecentActions)
download2 = threading.Thread(target=recentActionsThread)
download1.daemon = True
download2.daemon = True
download1.start()
download2.start()

#if __name__ == "__main__":
#    main()
