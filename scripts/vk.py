#!/usr/bin/env python3

from library import *

def vk(method, **kwargs):
    params = dotdict(kwargs)
    if not 'v' in params: params.v = '5.92'
    params.access_token = json.loads('\n'.join(open('/home/igorjan/.config/vk200/vk.json').readlines())).vk.access_token
    ret = requests.get('https://api.vk.com/method/' + method, params = params).json()
    if 'error' in ret:
        print(f'Error in {method}: {ret.error.error_msg}', kwargs)
        return ret.error
    return ret.response

def unlimitedVk(method, field, max_count, verbose = False, **kwargs):
    def getter(**kwargs):
        return vk(method, **kwargs);
    return unlimited(getter, field, max_count, verbose = verbose, **kwargs)

def getPhoto(url, path, peer_id):
    files = {'photo': open(path, 'rb')}
    attach = requests.post(url, files = files)
    return vk('photos.saveMessagesPhoto', attach.json())[0]

def sendPhoto(paths, peer_id):
    url = vk('photos.getMessagesUploadServer', {'peer_id': peer_id})['upload_url']
    photos = [getPhoto(url, path, peer_id) for path in paths.split(' ')]
    strings = ['photo' + str(photo['owner_id']) + '_' + str(photo['id']) for photo in photos]
    vk('messages.send', {'attachment': ','.join(strings), 'random_id': random.randint(0, 2 ** 31), 'peer_id': peer_id})

def getMe():
    return vk('users.get')[0]

def getFriends():
    return unlimitedVk('friends.get', 'items', 5000, fields = 'nickname') + [getMe()]

def getChats():
    return list(filter(lambda conversation: conversation.conversation.peer.type == 'chat', unlimitedVk('messages.getConversations', 'items', 200)))

def getFriendsDict():
    return dict(map(lambda user: (str(user.id), user.first_name + ' ' + user.last_name), getFriends()))

def getChatsDict():
    return dict(map(lambda chat: (str(chat.conversation.peer.id), chat.conversation.chat_settings.title), getChats()))

def getConversations():
    return {**getChatsDict(), **getFriendsDict()}

@completion.command()
# @click.argument('peer_ids', required=True, type=click_completion.DocumentedChoice(getConversations()), nargs=-1)
@click.option('-s', '--stacked', is_flag=True, help='Stacked mode', default=True)
@click.option('-d', '--separated', is_flag=True, help='Stat for one dialog', default=False)
def histogramMessagesByDate(peer_ids, stacked, separated):
    from datetime import datetime
    import matplotlib.pyplot as plt
    import matplotlib.dates as mdates

    friends = getConversations()
    MAX_COUNT = 200
    DATE_FORMAT = '%d-%m-%y'

    users = {}
    legend = []
    days = []
    dates = []

    def getDate(message):
        return message.date

    def add(curr, peer_id):
        if not peer_id in friends: return
        temp = (curr[0] - curr[-1]) // (24 * 60 * 60)
        days.append(temp)
        dates.append(curr)
        legend.append(f'{friends[peer_id]}, {temp} days long, {len(curr)} messages')

    for peer_id in peer_ids:
        curr = unlimitedVk('messages.getHistory', 'items', MAX_COUNT, True, peer_id = peer_id)
        for message in curr:
            peer_id = str(message.from_id if separated else peer_ids[0])
            if not peer_id in users:
                users[peer_id] = []
            users[peer_id].append(getDate(message))

    for peer_id, curr in users.items():
        add(curr, peer_id)

    fig, ax = plt.subplots(1, 1)
    ax.hist(list(map(mdates.epoch2num, dates)), bins=max(days), stacked=stacked)
    ax.legend(legend)
    ax.xaxis.set_major_formatter(mdates.DateFormatter(DATE_FORMAT))
    plt.xlabel('Date')
    plt.ylabel('Count of messages')
    plt.show()

if __name__ == "__main__":
    completion()
