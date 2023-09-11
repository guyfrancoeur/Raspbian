
cc1100_rx: cc1100_rx.cpp cc1100_raspi.o
	g++ -O3 -Wall -o $@ $^ -lwiringPi

cc1100_tx: cc1100_tx.cpp cc1100_raspi.o
	g++ -O3 -Wall -o $@ $^ -lwiringPi

cc1100_raspi.o : cc1100_raspi.cpp
	g++ -c $^ -o $@
