import { ArgumentParser } from 'argparse'
import initDebug from '../debug-instance'
import { copyFromTo } from '../utils/exif'

const debug = initDebug(__filename)

type T = {
    photos: Array<string>,
}

const run = async ({photos}: T) => {
    const from = photos[0]
    photos.splice(0, 1)
    copyFromTo(from, photos)
}

export const copyExifFromTo = (parser: ArgumentParser) => {
    parser.add_argument('photos', { help: 'Photos to copy exif', nargs: '+', metavar: 'from to' });
    return run
}
