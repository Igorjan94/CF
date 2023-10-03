import * as piexif from 'piexif-ts'
import fs from 'fs'

export const getExifString = (filename: string) => {
    return fs.readFileSync(filename).toString('binary')
}

export const getExif = (filename: string) => {
    return piexif.load(getExifString(filename))
}

export const dumpExif = (filename: string, exifbytes: string) => {
    const newJpeg = piexif.insert(exifbytes, getExifString(filename))
    fs.writeFileSync(filename, Buffer.from(newJpeg, 'binary'))
}

export const copyFromTo = (from: string, photos: Array<string>) => {
    const exif = piexif.dump(getExif(from))
    for (const to of photos)
        dumpExif(to, exif)
}

