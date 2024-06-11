let x = []
const items = document.getElementsByClassName('datatable')[1].getElementsByTagName('tr')
for (let i = 0; i < items.length; ++i) {
    const tr = items[i]
    if (!tr.getAttribute('data-contestid')) continue;
    const elem = tr.getElementsByClassName('contestParticipantCountLinkMargin')[0]
    x.push(+elem.text.substr(2))
}
x.sort((a, b) => a - b)
console.log(x)
