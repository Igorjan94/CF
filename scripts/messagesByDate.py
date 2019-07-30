from datetime import datetime
import time
import matplotlib.pyplot as plt
import matplotlib.dates as mdates

import vk

peer_id = 53321
MAX_COUNT = 200
DATE_FORMAT = '%d-%m-%y'

dates = []
offset = 0
while True:
    print(offset)
    messages = vk.vk('messages.getHistory', vk.dotdict(offset = offset, peer_id = peer_id, count = MAX_COUNT))
    if not 'items' in messages:
        time.sleep(2)
        continue
    else:
        messages = messages['items']
    if not messages: break
    for message in messages:
        dates.append(message.date)

    offset += MAX_COUNT
    time.sleep(0.3)

mpl_data = mdates.epoch2num(dates)
fig, ax = plt.subplots(1, 1)
ax.hist(mpl_data, bins=(dates[0] - dates[-1]) // (24 * 60 * 60), color='lightblue')
# ax.xaxis.set_major_locator(mdates.YearLocator())
ax.xaxis.set_major_formatter(mdates.DateFormatter(DATE_FORMAT))
plt.show()
