#!/bin/bash

g++ -lwiringPi cc1100_rx.cpp cc1100_raspi.cpp -o cc1100_rx

g++ -lwiringPi cc1100_tx.cpp cc1100_raspi.cpp -o cc1100_tx
