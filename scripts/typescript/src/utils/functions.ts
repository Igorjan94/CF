import fs, { utimesSync } from 'fs'
import { Exif, ExifRecord, dumpExif, exec, getExif } from './exif'
import { getType } from 'mime'

const dateKeys = [
    'Exif.Image.DateTime',
    'Exif.Photo.DateTimeOriginal',
    'Exif.Photo.DateTimeDigitized',
] as const

const setCreationDate = (filename: string, date?: Date) => {
    if (!date) return
    console.log(`Setting date ${date} for ${filename}`)
    const t = date.getTime() / 1000
    utimesSync(filename, t, t)
}

const getCreatedDateFromExif = async (filename: string): Promise<string | undefined> => {
    const type = getType(filename)
    if (type?.startsWith('image')) {
        const exif = await getExif(filename)
        for (const key of dateKeys) {
            const date = exif[key]?.value
            // https://www.awaresystems.be/imaging/tiff/tifftags/privateifd/exif/datetimeoriginal.html
            // The format is "YYYY:MM:DD HH:MM:SS". Convert it to normal format
            if (date && /^\d\d\d\d:\d\d:\d\d \d\d:\d\d:\d\d$/.test(date))
                return date.replace(':', '-').replace(':', '-') + '.000 +0000'
        }
    } else if (type?.startsWith('video')) {
        const { stdout } = await exec(`ffmpeg -i ${filename} 2>&1 | grep creation_time | head -1`)
        return stdout.pysplit(': ', 1)?.[1]?.trim()
    }
    return undefined
}

const guessDateFromFilename = (filename: string): string | undefined => {
    const name = filename.rsplit('/', 1)[1]
    if (!name) return undefined
    const m = name.match(/^(IMG_|PANO_|PICT_|VID_|LRV_)?(20\d{2})-?(\d{2})-?(\d{2})[_ ](\d{2}):?(\d{2}):?(\d{2})/)
    if (m) return `${m[2]}-${m[3]}-${m[4]} ${m[5]}:${m[6]}:${m[7]}`

    return undefined
}

const getDate = async (filename: string): Promise<Date | undefined> => {
    let dateString = await getCreatedDateFromExif(filename)
    if (dateString) {
        console.log(`Date from exif: ${dateString}`)
    }
    if (!dateString) {
        dateString = guessDateFromFilename(filename)
        if (dateString) {
            console.log(`Date from filename: ${dateString}`)
        }
    }
    if (!dateString) return
    return new Date(dateString)
}

const updateDateInExif = async (filename: string, date?: Date) => {
    if (!date) return
    if (!getType(filename)?.startsWith('image')) return
    const exif: Exif = {}
    const dateString = date.toISOString().replace('T', ' ').substring(0, 19).replace(/-/g, ':')
    for (const key of dateKeys) {
        exif[key] = {
            type: 'Ascii',
            value: dateString,
        }
    }
    await dumpExif(filename, exif)
}

export const copyFromTo = async (from: string, photos: Array<string>) => {
    const exif = await getExif(from)
    for (const to of photos) {
        await dumpExif(to, exif)
        await fixPhotoDate(to)
    }
}

export const fixPhotoDate = async (filename: string, timezone?: number) => {
    console.log(`Fixing date for ${filename}`)
    const date = await getDate(filename)
    if (timezone && date) {
        date.setHours(date.getHours() + timezone)
    }
    await updateDateInExif(filename, date)
    setCreationDate(filename, date)
}
