let sx = 353;
let sy = 347;
let r = 21;
let mnx = 145 + r;
let mxx = 565 - r;
let svg = (...path) => `${sx} ${sy} ${path.join(' ')}`;

let xmlns = 'http://www.w3.org/2000/svg';
let boxWidth = 600;
let boxHeight = 400;

let svgElem = document.createElementNS(xmlns, 'svg');
svgElem.setAttributeNS(null, 'width', boxWidth);
svgElem.setAttributeNS(null, 'height', boxHeight);
svgElem.style['z-index'] = '10000 !important';
svgElem.style['position'] = 'absolute';
svgElem.style['pointer-events'] = 'none';

let g = document.createElementNS(xmlns, 'polyline');
g.setAttributeNS(null, 'points', svg(0, 0))
g.setAttributeNS(null, 'style', 'fill:none;stroke:red;stroke-width:1')
svgElem.appendChild(g);

let el = document.getElementById('game').childNodes[5].childNodes[0]

el.insertBefore(svgElem, el.firstChild);

let eventListener = el => e => {
    let x = e.clientX - 55;
    let y = e.clientY - 255;
    if (y >= 320) return;
    let temp = [];
    if (x == sx)
        temp = [x, 0];
    else {
        let m = x > sx ? mxx : mnx;
        let getB = m => (m * (sy - y) + sx * y - sy * x) / (sx - x);
        let b = getB(m);
        let neb = getB(m == mxx ? mnx : mxx);
        let dy = neb - b;
        while (temp.length < 20) {
            temp = temp.concat(m, b);
            if (b < 0) break;
            m = m == mxx ? mnx : mxx;
            b -= dy;
        }
    }
    el.setAttributeNS(null, 'points', svg(...temp))
};

window.addEventListener('mousemove', eventListener(g), false)
