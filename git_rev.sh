#!/bin/sh

if [ `command -v git` ]; then
    git rev-parse --short HEAD 
else
    echo unknown
fi
