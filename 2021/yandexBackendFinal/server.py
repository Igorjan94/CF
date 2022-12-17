#!/usr/bin/python3
import http.server as hs
import json
import sys
import urllib.parse

class RecordType:
    Folder = 'Folder'
    Record = 'Record'


class Record:
    def __init__(self, record_type, name):
        assert record_type in [RecordType.Folder, RecordType.Record]
        self.type = record_type
        self.name = name
        self.size = 1

    def to_dict(self):
        return {'type': self.type, 'name': self.name, 'size': self.size}


class Tree:
    def __init__(self, nodes_count):
        # Из индекса вершины в:
        self.graph: List[List[int]] = [[] for _ in range(nodes_count)]  # В индекс ребёнка
        self.record: List[Record] = [Record(RecordType.Folder, '') for _ in range(nodes_count)]  # В данные
        self.path: List[str] = ['' for _ in range(nodes_count)]  # В путь
        self.depth: List[int] = [1 for _ in range(nodes_count)]  # В глубину

        self.record[0] = Record(RecordType.Folder, '')
        self.current_ind: int = 1
        self.path_ind: Dict[str, int] = {'/': 0}  # Из пути переходит в индекс вершины

    def add_edge(self, parent_path, child, child_type):
        parent_ind = self.path_ind[parent_path]
        self.graph[parent_ind].append(self.current_ind)
        self.record[self.current_ind] = Record(child_type, child)

        parent_folder = self.path[parent_ind]
        self.path[self.current_ind] = parent_folder + '/' + child
        self.path_ind[self.path[self.current_ind]] = self.current_ind

        self.current_ind += 1

    def calculate_sizes(self):
        for node in range(len(self.graph)):
            self.record[node].size = len(self.graph[node])
            for child_node in self.graph[node]:
                self.depth[child_node] = self.depth[node] + 1

    def validate_path(self, path):
        return path in self.path_ind

    def ls(self, node_ind):
        return [self.record[ind] for ind in self.graph[node_ind]]


class Listing:
    def __init__(self, records):
        self.records = records

    def to_dict(self):
        return [record.to_dict() for record in self.records]


class LsBatchResponse:
    def __init__(self, listings):
        self.listings = listings

    def to_dict(self):
        return {'listings': [listing.to_dict() for listing in self.listings]}

def is_valid_ls_batch_request(json_str):
    try:
        json_request = json.loads(json_str)
        if not isinstance(json_request, dict):
            return False
        if 'paths' not in json_request.keys():
            return False
        paths = json_request['paths']
        if not isinstance(paths, list):
            return False
        for path in paths:
            if not isinstance(path, str):
                return False
    except (TypeError, json.JSONDecodeError):
        return False
    return True


def read_input(file_input):
    """
    n max_batch_size
    parent_ind name type <- (n - 1) times
    """
    login = file_input.readline().strip()
    n, max_batch_size = map(int, file_input.readline().split())

    tree = Tree(n)
    for _ in range(n - 1):
        path = file_input.readline().strip()

        child_type = RecordType.Record
        if path[-1] == '/':
            child_type = RecordType.Folder
            path = path[:-1]

        path_tokens = path.split('/')
        parent_path, child_name = '/'.join(path_tokens[:-1]), path_tokens[-1]
        if parent_path == '':
            parent_path = '/'

        tree.add_edge(parent_path, child_name, child_type)
    tree.calculate_sizes()

    return login, max_batch_size, tree

OK = 200
WRONG_REQUEST = 400
BATCH_SIZE_TOO_BIG = 429

class State:
    def __init__(self, login, max_batch_size, tree):
        self.start = False
        self.queries_left = 0
        self.login = login
        self.max_batch_size = max_batch_size
        self.tree = tree

class ServerHTTPHandler(hs.BaseHTTPRequestHandler):
    path_start_session = '/start/session?'
    path_ls_batch = '/ls/batch'

    def send_answer(self, code, content):
        self.send_response(code)
        self.end_headers()
        self.wfile.write(content.encode('utf-8'))

    def start_session(self, query):
        try:
            params = urllib.parse.parse_qs(query)
        except:
            self.send_answer(WRONG_REQUEST, 'Invalid login')
            return
        if params is None:
            self.send_answer(WRONG_REQUEST, 'Invalid login')
            return
        login = params.get('login', [])
        if len(login) != 1 or login[0] != self.state.login:
            self.send_answer(WRONG_REQUEST, 'Invalid login')
            return
        if self.state.queries_left == 0:
            self.send_answer(BATCH_SIZE_TOO_BIG, 'Amount of queries is exceeded')
            return
        self.state.queries_left -= 1
        self.state.start = True
        self.send_answer(OK, json.dumps({'max_batch_size': self.state.max_batch_size}))

    def ls_batch(self):
        if self.state.queries_left == 0:
            self.send_answer(BATCH_SIZE_TOO_BIG, 'Amount of queries is exceeded')
            return
        self.state.queries_left -= 1

        if not self.state.start:
            self.send_answer(WRONG_REQUEST, 'Session is not started')
            return
        try:
            length = int(self.headers['content-length'])
        except:
            self.send_answer(WRONG_REQUEST, 'Invalid content length')
        request = self.rfile.read(length)
        if not is_valid_ls_batch_request(request):
            self.send_answer(WRONG_REQUEST, '/ls/batch request is invalid')
            return

        batch = json.loads(request)['paths']

        total_size = 0
        ind_to_process = []
        for path in batch:
            if self.state.tree.validate_path(path):
                ind_to_process.append(self.state.tree.path_ind[path])
                total_size += self.state.tree.record[ind_to_process[-1]].size
            else:
                self.send_answer(WRONG_REQUEST, 'One of paths in batch is invalid')
                return
        if total_size > self.state.max_batch_size:
            self.send_answer(BATCH_SIZE_TOO_BIG, 'Size of a batch is bigger than max_batch_size')
            return

        self.send_answer(OK, json.dumps(LsBatchResponse([
            Listing([self.state.tree.record[ind] for ind in self.state.tree.graph[parent_ind]])
            for parent_ind in ind_to_process
        ]).to_dict()))

    def do_GET(self):
        if self.path.startswith(self.path_start_session):
            self.start_session(self.path[len(self.path_start_session):])
        else:
            self.send_error(404)

    def do_POST(self):
        if self.path == self.path_ls_batch or self.path.startswith(self.path_ls_batch + "?"):
            self.ls_batch()
        else:
            self.send_error(404)


def run(argv):
    login, max_batch_size, tree = read_input(open(argv[1])) # input
    state = State(login, max_batch_size, tree)
    state.queries_left = 1 + max(1, max(
        tree.depth[i] if tree.record[i].size > 0 else 0
        for i in range(len(tree.graph))))
    ServerHTTPHandler.state = state

    server = hs.HTTPServer(('127.0.0.1', 7777), ServerHTTPHandler)
    server.serve_forever()


if __name__ == '__main__':
    run(sys.argv)
