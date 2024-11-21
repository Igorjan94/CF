const format = x => x >= 10 ? `${x}` : `0${x}`;

const hard = [99, 30, 28, 12, 12, 10].reverse();
const bb = [];
const opp = [];
for (let i = 0; i < 8; ++i)
    bb.push(2);
for (let i = 0; i < 27; ++i)
    opp.push(2);
const bytes = [];
for (let j = 0; j < bb.length; ++j)
    bytes.push(0);

function fromDecToN(x, bases) {
    let ans = [];
    for (const base of bases) {
        ans.push(x % base);
        x = x / base >> 0;
    }
    return ans.reverse();
}

function fromNToDec(ans, bases) {
    let x = 0;
    for (let i = 0; i < bases.length; ++i) {
        x = x * bases[bases.length - i - 1] + ans[i];
    }
    return x;
}

export function compress(text) {
    const ss = text.split('\n');
    const a = ss.flatMap(s => {
        const one = (+s[1]) * 10 + (+s[2]);
        const two = (+s[3]) * 10 + (+s[4]);
        const thr = (+s[5]) * 10 + (+s[6]);
        const fou = (+s[7]) * 10 + (+s[8]);
        const fif = (+s[9]) * 10 + (+s[10]);
        const six = (+s[11]) * 10 + (+s[12]);
        const values = [one, six, two, fif, fou, thr].map(x => x - 1);
        const dec = fromNToDec(values, hard);
        return fromDecToN(dec, opp);
    });
    while (a.length % 8 != 0)
        a.push(0);
    const q = [];
    for (let i = 0; i < a.length; i += bb.length) {
        for (let j = 0; j < bb.length; ++j)
            bytes[j] = a[i + j];
        const dec = fromNToDec(bytes, bb);
        q.push(dec);
    }
    return new Uint8Array(q).buffer;
}

export function decompress(b) {
    const buffer = new Uint8Array(b);
    const a = [];
    const q = [];
    for (let i = 0; i < buffer.length; ++i) {
        q.push(...fromDecToN(buffer[i], bb));
    }
    for (let i = 0; i + opp.length <= q.length; i += opp.length) {
        for (let j = 0; j < opp.length; ++j)
            bytes[j] = q[i + j];
        const dec = fromNToDec(bytes, opp);
        const values = fromDecToN(dec, hard).map(x => x + 1).map(x => format(x));
        a.push(`辰${values[0]}${values[2]}${values[5]}${values[4]}${values[3]}${values[1]}`);
    }
    return a.join('\n');
}


const vvv = []
for (let i = 91; i <= 92; ++i) {
    console.log(i);
    for (let j = 1; j <= 28; ++j)
        for (let k = 1; k <= 10; ++k)
            for (let q = 1; q <= 12; ++q)
                for (let w = 1; w <= 12; ++w)
                    for (let e = 1; e <= 30; ++e)
                        vvv.push(`辰${format(i)}${format(j)}${format(k)}${format(q)}${format(w)}${format(e)}`);
}

let text = vvv.join('\n');
if (false) {
    text = '';
    for (let i = 0; i < 32; ++i) {
        text += `辰992810121230`;
        if (i != 31) text += '\n';
    }
}
const buffer = compress(text);
console.log(buffer.byteLength);
const restored_text = decompress(buffer);

if (text !== restored_text) {
  console.log('decompress(compress(x)) != x', text.length, restored_text.length)
}
