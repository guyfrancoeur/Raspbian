#!/bin/bash
cd
wget http://www.airspayce.com/mikem/bcm2835/bcm2835-1.73.tar.gz
tar xvfz bcm2835-1.73.tar.gz
cd bcm2835-1.73
./configure
make
sudo make install
cd
rm bcm2835-1.73.tar.gz
rm -fr bcm2835-1.73
