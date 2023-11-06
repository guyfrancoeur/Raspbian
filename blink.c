// blink.c
//
// Example program for bcm2835 library
// Blinks a pin on an off
//
// After installing bcm2835, you can build this
// with something like:
// gcc -o blink blink.c -l bcm2835
// ./blink
//
// Or you can test it before installing with:
// gcc -o blink -I ../../src ../../src/bcm2835.c blink.c
// ./blink
//
// Original Author: Mike McCauley --> New Author : Guy Francoeur
// Copyright (C) 2011 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $

#include <bcm2835.h>
#include <stdio.h>
#define PIN RPI_GPIO_P1_26

int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
//    bcm2835_set_debug(1);  //Use for testing

    if (!bcm2835_init())
      return 1;

    // Set the pin to be an output
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);

    while (1)
    {
        bcm2835_gpio_write(PIN, HIGH);  // Turn it on
        bcm2835_delay(500);  // wait a bit
        bcm2835_gpio_write(PIN, LOW);  // turn it off
        bcm2835_delay(1000);  // wait a bit more
    }
    bcm2835_close();
    return 0;
}
