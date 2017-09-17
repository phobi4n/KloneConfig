#!/bin/bash

if [ $EUID != 0 ]; then
    echo "This needs to be run as super user."
fi


if [ -x KloneConfig ]; then
    echo "The binary KloneConfig was not found. Execute ./run.sh first."
fi

cp -fv ./KloneConfig  /usr/bin
cp -fv ./huen-icon.svg /usr/share/icons/hicolor/scalable/apps
cp -fv ./KC.desktop /usr/share/applications

echo "Done. Check your menu under settings."
