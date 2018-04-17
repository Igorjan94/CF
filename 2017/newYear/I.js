var count = Number(readline());
var a = {};
var minutes = 0;
var hours = 12;

function good(h, m) {
    var s = "" + h + "" + (m >= 10 ? m : ("0" + m));
    var d = s[0] - s[1];
    for (var j = 1; j < s.length - 1; ++j)
        if (s[j] - s[j + 1] != d)
            return 0;
//    print(s, h, m)
    return 1;
}

var i = 0;
for (; i === 0 || minutes !== 0 || hours !== 12; ++i) {
    a[i] = i === 0 ? 0 : a[i - 1] + good(hours, minutes);
    
    minutes++;
    if (minutes == 60) {
        minutes = 0;
        hours++;
    }
    if (hours == 13)
        hours = 1;
}

var ans = a[i - 1] * (count >= i ? Math.floor(count / i) : 0) + a[count % i];
print(ans);
