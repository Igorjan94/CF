#!/usr/bin/env python3

from library import *

def vk(method, **kwargs):
    params = dotdict(kwargs)
    if not 'v' in params: params.v = '5.92'
    params.access_token = json.loads('\n'.join(open('/home/igorjan/.config/vk200/vk.json').readlines())).vk.access_token
    ret = requests.get('https://api.vk.com/method/' + method, params = params).json()
    if 'error' in ret:
        print(ret.error.error_msg)
        return ret.error
    return ret.response

def unlimitedVk(method, field, max_count, verbose = False, **kwargs):
    kwargs['count'] = max_count
    offset = 0
    res = []
    while True:
        if verbose:
            print(f'Getting {method}, offset {offset}')
        kwargs['offset'] = offset
        temp = vk(method, **kwargs)
        if not field in temp:
            time.sleep(2)
            continue
        temp = temp[field]
        if not temp: break

        res += temp
        offset += max_count
        time.sleep(1 / 3)
    return res

def getPhoto(url, path, peer_id):
    files = {'photo': open(path, 'rb')}
    attach = requests.post(url, files = files)
    return vk('photos.saveMessagesPhoto', attach.json())[0]

def sendPhoto(paths, peer_id):
    url = vk('photos.getMessagesUploadServer', {'peer_id': peer_id})['upload_url']
    photos = [getPhoto(url, path, peer_id) for path in paths.split(' ')]
    strings = ['photo' + str(photo['owner_id']) + '_' + str(photo['id']) for photo in photos]
    vk('messages.send', {'attachment': ','.join(strings), 'random_id': random.randint(0, 2 ** 31), 'peer_id': peer_id})


def getFriends():
    return unlimitedVk('friends.get', 'items', 5000, fields = 'nickname')

def getFriendsDict():
    return dict(map(lambda user: (str(user.id), user.first_name + ' ' + user.last_name), getFriends()))

@completion.command()
@click.argument('peer_ids', required=True, type=click_completion.DocumentedChoice(getFriendsDict()), nargs=-1)
def histogramMessagesByDate(peer_ids):
    from datetime import datetime
    import matplotlib.pyplot as plt
    import matplotlib.dates as mdates

    friends = getFriendsDict()
    MAX_COUNT = 200
    DATE_FORMAT = '%d-%m-%y'

    dates = []
    legend = []
    days = 0
    for peer_id in peer_ids:
        curr = list(map(lambda message: message.date, unlimitedVk('messages.getHistory', 'items', MAX_COUNT, peer_id = peer_id)))
        temp = (curr[0] - curr[-1]) // (24 * 60 * 60)
        days = max(days, temp)
        dates.append(curr)
        legend.append(f'{friends[peer_id]}, {temp} days long, {len(curr)} messages')

    fig, ax = plt.subplots(1, 1)
    ax.hist(list(map(mdates.epoch2num, dates)), bins=days, stacked=True)
    ax.legend(legend)
    # ax.xaxis.set_major_locator(mdates.YearLocator())
    ax.xaxis.set_major_formatter(mdates.DateFormatter(DATE_FORMAT))
    plt.show()

if __name__ == "__main__":
    completion()
