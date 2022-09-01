flash_led: flash_led.c
        gcc -Wall -std=c17 -o $@ $^

simplescan: simplescan.c
        gcc -Wall -std=c17 -o simplescan simplescan.c -lbluetooth

clean:
        rm -f prog simplescan

.PHONY: clean
