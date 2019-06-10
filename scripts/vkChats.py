from vk import vk

chats = vk('messages.getChat', {'chat_ids': ','.join(map(str, range(1, 73)))})
names = []
for chat in chats:
    if 53321 in chat['users']:
        names.append(chat['title'])
print('Всего чатов: {}, чатов с Антоном: {}'.format(len(chats), len(names)))
print('\n'.join(names))
