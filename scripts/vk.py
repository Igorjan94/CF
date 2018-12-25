import requests

def vk(method, params):
    if not 'v' in params: params['v'] = '5.92'
    params['access_token'] = open('/home/igorjan/key.vk').readline()[:-1]
    ret = requests.get('https://api.vk.com/method/' + method, params = params).json()
    if 'error' in ret:
        print(ret['error']['error_msg'])
        return ret['error']
    return ret['response']
