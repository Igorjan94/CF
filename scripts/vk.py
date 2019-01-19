import requests
import random

def vk(method, params):
    if not 'v' in params: params['v'] = '5.92'
    params['access_token'] = open('/home/igorjan/key.vk').readline()[:-1]
    ret = requests.get('https://api.vk.com/method/' + method, params = params).json()
    if 'error' in ret:
        print(ret['error']['error_msg'])
        return ret['error']
    return ret['response']

def getPhoto(url, path, peer_id):
    files = {'photo': open(path, 'rb')}
    attach = requests.post(url, files = files)
    return vk('photos.saveMessagesPhoto', attach.json())[0]

def sendPhoto(paths, peer_id):
    url = vk('photos.getMessagesUploadServer', {'peer_id': peer_id})['upload_url']
    photos = [getPhoto(url, path, peer_id) for path in paths.split(' ')]
    strings = ['photo' + str(photo['owner_id']) + '_' + str(photo['id']) for photo in photos]
    vk('messages.send', {'attachment': ','.join(strings), 'random_id': random.randint(0, 2 ** 31), 'peer_id': peer_id})
