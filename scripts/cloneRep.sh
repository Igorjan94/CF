#!/usr/bin/env bash

if [ -z "$1" ]; then
    echo "Rep isn't set";
    exit 1;
fi

surname=$(findSurname.py "$1")

git clone "$1" "$surname" && cd "$surname" && buildHere.sh
