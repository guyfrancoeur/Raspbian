blink: blink.c
	gcc -o blink blink.c -l bcm2835

tsl2561: tsl2561.c
	gcc -O2 -o tsl2561 tsl2561.c

flash_led: flash_led.c
	gcc -Wall -std=c17 -o $@ $^

simplescan: simplescan.c
	gcc -Wall -std=c17 -o simplescan simplescan.c -lbluetooth

clean:
	rm -f prog simplescan blink

.PHONY: clean
