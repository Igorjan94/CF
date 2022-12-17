from vk import vk

chats = vk('messages.getChat', chat_ids = ','.join(map(str, range(1, 82))))
names = []
for chat in chats:
    if set([53321, 3167759, 3586834]) == set(chat.users):
        names.append(chat['title'])
print('Всего чатов: {}, чатов с Антоном: {}'.format(len(chats), len(names)))
print('\n'.join(names))
