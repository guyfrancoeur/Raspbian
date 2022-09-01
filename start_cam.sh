#!/bin/bash

#http://192.168.1.186:8080/?action=stream


cd ~/mjpg-streamer-master/mjpg-streamer-experimental
./mjpg_streamer -i "./input_raspicam.so -fps 15 -x 1280 -y 720" -o output_http.so
