
(async () => {
    $('.gs-gallery__image__info').css('bottom', '52px');
    let photos = [];
    let filter = $('.gs-gallery__filter__active');
    let order = filter[0].children[0].innerText.toLowerCase();
    photos.push(...(await angular.element(filter).controller().metaData.PagesManager.api.photos.save({action: 'get_photos_public'}, {get_achievements: true, get_liked: true, get_likes: true, get_member: true, get_votes: true, limit: 80, member_id: angular.element(filter).controller().$rootScope.el_id, order, sort: 'desc', start: 0, type: 'photos', search: $('#input-0')[0].value})).items);
    photos.map(photo => {
        let j = $(`a[ng-href="/photo/${photo.id}"]`);
        if (j && j.length) j = j[0].parentNode;
        if (j) j = j.parentNode;
        if (j) j = j.children;
        if (j && j.length) j = j[1];
        if (j && j.children && j.children.length >= 2) {
            j.appendChild(j.children[1].cloneNode(true));
            let child = j.lastChild.children[1];
            if (child)
                child.innerText = (photo.votes / photo.views).toFixed(1);
        }
    });
    const get = a => +a.children[1].lastChild.innerText;
    const list = $('.gs-gallery__grid')[0];
    list.children[0].remove();
    list.parentElement.insertBefore(list.cloneNode(), list.parentElement.firstChild);
    Array.prototype.slice.call(list.children).slice(0, 70)
        .sort((a, b) => get(a) - get(b))
        .map(x => list.parentNode.firstChild.appendChild(x.children[2]));
        .map(x => {
            x.chilren[2].insertBefore(x.children[1], x.children[2].firstChild);
            list.parentNode.firstChild.appendChild(x.children[2]);
        });
})();


