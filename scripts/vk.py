import requests
import random
import json

class dotdict(dict):
    __getattr__ = dict.get
    __setattr__ = dict.__setitem__
    __delattr__ = dict.__delitem__
    def __init__(self, *args, **kwargs):
        super(dotdict, self).__init__(*args, **kwargs)
        for d in args:
            if isinstance(d, dict):
                for key, value in d.items():
                    if isinstance(value, dict):
                        value = dotdict(value)
                    elif isinstance(value, list) and value and isinstance(value[0], dict):
                        value = list(map(dotdict, value))
                    self[key] = value

        if kwargs:
            for k, v in kwargs.items():
                self[k] = v

def decorateFunction(original):
    def decorated(*args, **kwargs): return dotdict(original(*args, **kwargs))
    return decorated

json.loads = decorateFunction(json.loads)
requests.Response.json = decorateFunction(requests.Response.json)

def vk(method, params):
    if not isinstance(params, dotdict): params = dotdict(params)
    if not 'v' in params: params.v = '5.92'
    params.access_token = json.loads('\n'.join(open('/home/igorjan/.config/vk200/vk.json').readlines())).vk.access_token
    ret = requests.get('https://api.vk.com/method/' + method, params = params).json()
    if 'error' in ret:
        print(ret.error.error_msg)
        return ret.error
    return ret.response

def getPhoto(url, path, peer_id):
    files = {'photo': open(path, 'rb')}
    attach = requests.post(url, files = files)
    return vk('photos.saveMessagesPhoto', attach.json())[0]

def sendPhoto(paths, peer_id):
    url = vk('photos.getMessagesUploadServer', {'peer_id': peer_id})['upload_url']
    photos = [getPhoto(url, path, peer_id) for path in paths.split(' ')]
    strings = ['photo' + str(photo['owner_id']) + '_' + str(photo['id']) for photo in photos]
    vk('messages.send', {'attachment': ','.join(strings), 'random_id': random.randint(0, 2 ** 31), 'peer_id': peer_id})
