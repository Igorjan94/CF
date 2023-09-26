import { ArgumentParser } from 'argparse'
import initDebug from '../debug-instance'
import { fixPhotoDate } from '../utils/functions'

const debug = initDebug(__filename)

type T = {
    photos: Array<string>,
    timezone?: number,
}

const run = async ({photos, timezone}: T) => {
    for (const photo of photos)
        await fixPhotoDate(photo, timezone)
}

export const fixDate = (parser: ArgumentParser) => {
    parser.add_argument('photos', { help: 'Photos to fix date', nargs: '+' });
    parser.add_argument('-t', '--timezone', { help: 'Timezone shift', type: 'int', default: 0 })
    return run
}
