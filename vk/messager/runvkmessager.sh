#!/usr/bin/env zsh
mv messager.temp messager.data 2>/dev/null
for i in {1..1000}
do
    ./messager
    rm -rf messager.data
    mv messager.temp messager.data 2>/dev/null
done
