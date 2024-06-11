import { ArgumentParser } from 'argparse'
import initDebug from '../debug-instance'
import {  shiftPhotoDate } from '../utils/functions'

const debug = initDebug(__filename)

type T = {
    photos: Array<string>,
    change: string,
    fallback: string,
}

const run = async ({photos, change, fallback}: T) => {
    const changeDate = new Date(change)
    const fallbackDate = new Date(fallback)
    const diff = changeDate.getTime() - fallbackDate.getTime()
    for (const photo of photos)
        await shiftPhotoDate(photo, diff)
}

export const shiftDate = (parser: ArgumentParser) => {
    parser.add_argument('photos', { help: 'Photos to fix date', nargs: '+' });
    parser.add_argument('-c', '--change', { help: 'Accumulator change date', type: 'str' })
    parser.add_argument('-f', '--fallback', { help: 'Fallback date', type: 'str' })

    return run
}
