#!/bin/sh

cd `dirname "$0"`;
cd ..;

sudo rm config.h;
sudo make clean install;

killall dwm;
