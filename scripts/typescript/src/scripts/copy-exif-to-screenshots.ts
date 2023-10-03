import { ArgumentParser } from 'argparse'
import initDebug from '../debug-instance'
import { copyFromTo } from '../utils/exif'

const debug = initDebug(__filename)

type T = {
    photos: Array<string>,
}

const run = async ({photos}: T) => {
    const m: Record<string, Array<string>> = {}
    for (const f of photos) {
        if (!f.endsWith('_screenshot.jpg')) continue
        const [dir, fn] = f.rsplit('/', 1)
        if (!fn) continue
        const st = fn.split('_', 3).splice(0, 3).join('_')
        if (st.length != 19) continue //should be IMG_20230901_075731 string
        const can: Array<string> = []
        for (const from of photos)
            if (from != f && !from.endsWith('_screenshot.jpg') && from.startsWith(dir + '/' + st))
                can.push(from)
        if (can.length == 0)
            console.log(`Origin of ${f} is not found`)
        else if (can.length >= 2)
            console.log(`Multiple origins of ${f} found: ${can.join(', ')}`)
        else {
            const found = can[0]
            m[found] ??= []
            m[found].push(f)
        }
    }
    for (const [k, v] of Object.entries(m)) {
        console.log(`Copying exif from ${k} to:\n - ${v.join('\n - ')}`)
        copyFromTo(k, v)
    }
}

export const copyExifToScreenshots = (parser: ArgumentParser) => {
    parser.add_argument('photos', { help: 'Photos with screenshots and exported files of insta360', nargs: '+' });
    return run
}
