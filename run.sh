#!/bin/bash

if [ -x KloneConfig ]; then
    exec ./KloneConfig
fi

qmake
make
exec ./KloneConfig
