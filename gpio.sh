#!/bin/bash

echo 2 > /sys/class/gpio/export
echo out > /sys/class/gpio/gpio2/direction
for i in 1..10
do
echo 1 > /sys/class/gpio/gpio2/value
echo 0 > /sys/class/gpio/gpio2/value
sleep 1
echo 1 > /sys/class/gpio/gpio2/value
echo 0 > /sys/class/gpio/gpio2/value
sleep 1
done
sleep 1
echo 2 > /sys/class/gpio/unexport
