#!/usr/bin/env node
import 'saas-globals'

const {version} = require('../package.json')

import argparse, { ArgumentParser } from 'argparse'

const parser = new ArgumentParser({
    description: 'Igorjan94 scripts',
})

parser.add_argument('-v', '--version', { action: 'version', version })
const subparsers = parser.add_subparsers()

import { copyExifFromTo } from './scripts/copy-exif-from-to'
import { copyExifToScreenshots } from './scripts/copy-exif-to-screenshots'
import { fixDate } from './scripts/fix-date'
import { extractPanos } from './scripts/extract-panos'
import { shiftDate } from './scripts/shift-date'

const available = [
    copyExifFromTo,
    copyExifToScreenshots,
    fixDate,
    shiftDate,
    extractPanos,
] as const

for (const script of available) {
    const name = script.name
    const subparser = subparsers.add_parser(name)
    const run = script(subparser)
    subparser.set_defaults({run})
}

const args = parser.parse_args()
if ('run' in args) {
    args.run(args).catch(e => {
        console.error(e)
    })
} else {
    console.warn('No command selected, exit')
}
