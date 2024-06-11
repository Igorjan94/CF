import { promisify } from 'util'
import { exec as callbackExec } from 'child_process'

export const exec = promisify(callbackExec)

export type ExifKey = string
export type ExifRecord = {
    type: string,
    value: string,
}

export type Exif = Record<ExifKey, ExifRecord>

export const getExif = async (filename: string): Promise<Exif> => {
    const {stdout, stderr} = await exec(`exiv2 -p e "${filename}"`)
    const ret: Exif = {}
    for (const line of stdout.split('\n').filter(Boolean)) {
        const [key, type, len, ...value] = line.split(/\s+/)
        if (!key || !type) continue
        ret[key] = {
            type,
            value: value.join(' ').trimEnd(),
        }
    }
    return ret
}

export const dumpExif = async (filename: string, exif: Exif) => {
    const command = Object.entries(exif).map(([key, {value, type}]) => `-M"set ${key} ${type} ${value || "''"}"`).join(' ')
    await exec(`exiv2 -v ${command} ${filename}`)
}

export const fixVideoDate = async (filename: string, date?: Date) => {
    console.log(`Fixing video date to ${date?.toISOString()}`)
    await exec(`ffmpeg -i "${filename}" -metadata creation_time="${date?.toISOString()}" -codec copy "copy-${filename}"`)
    await exec(`mv "copy-${filename}" "${filename}"`)
}

