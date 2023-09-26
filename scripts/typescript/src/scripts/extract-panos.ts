import { ArgumentParser } from 'argparse'
import initDebug from '../debug-instance'
import { copyFromTo, fixPhotoDate } from '../utils/functions'
import { Dirent, copyFileSync, readdirSync, statSync } from 'fs'
import { getType } from 'mime'
import path from 'path'
import { dumpExif } from '../utils/exif'

const debug = initDebug(__filename)

const getCtime = (filename: string) => new Date(statSync(filename).ctime)

const j = (f: Dirent) => path.join(f.path, f.name)

type T = {
    directory: string,
}

const run = async ({directory}: T) => {
    const dirs = readdirSync(directory, { withFileTypes: true }).filter(f => f.isDirectory())
    for (const dir of dirs) {
        console.log(`Processing directory ${dir.name}`)
        const files = readdirSync(j(dir), { withFileTypes: true })
            .filter(f => f.isFile())
            .filter(f => getType(j(f))?.startsWith('image'))
        const panos = files.filter(f => f.name.match(/^\d+\w?\./))
        const images = files.filter(f => !f.name.match(/^\d+\w?\./))
        if (panos.length == 0 || images.length == 0)
            continue
        let first = images[0]!
        for (const image of images) {
            if (getCtime(j(image)) < getCtime(j(first)))
                first = image
        }
        await copyFromTo(j(first), panos.map(j))
        for (const pano of panos) {
            await dumpExif(j(pano), {
                'Exif.Image.Orientation': {
                    value: '1',
                    type: 'Short',
                }
            })
            const to = path.join(directory, [dir.name, pano.name].join('_'))
            await copyFileSync(j(pano), to)
            await fixPhotoDate(j(pano))
            await fixPhotoDate(to)
        }
    }
}

export const extractPanos = (parser: ArgumentParser) => {
    parser.add_argument('directory', { help: 'Directory to extract panos to', type: 'str' });
    return run
}
