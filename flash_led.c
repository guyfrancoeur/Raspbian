// Code adapted from example by Gert van Loo & Dom from: http://elinux.org/Rpi_Low-level_peripherals#C_2
// use gcc -Wall -o flash_led flash_led.c
// flashes (blinks) LED on Raspberry PI 3 GPIO7

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#define PAGE_SIZE (4*1024)
#define BLOCK_SIZE (4*1024)

int  mem_fd;
void *gpio_map;

// I/O access
volatile unsigned *gpio;

// GPIO setup macros. Always use INP_GPIO(x) before using OUT_GPIO(x) or SET_GPIO_ALT(x,y)
#define INP_GPIO(g) *(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))
#define OUT_GPIO(g) *(gpio+((g)/10)) |=  (1<<(((g)%10)*3))
#define SET_GPIO_ALT(g,a) *(gpio+(((g)/10))) |= (((a)<=3?(a)+4:(a)==4?3:2)<<(((g)%10)*3))

#define GPIO_SET *(gpio+7)  // sets   bits which are 1 ignores bits which are 0
#define GPIO_CLR *(gpio+10) // clears bits which are 1 ignores bits which are 0

void setup_io();

int main(int argc, char **argv)
{
    int g,rep;

    // Set up gpi pointer for direct register access
    setup_io();

    // set GPIO pin 7 as output
    INP_GPIO(7); // must use INP_GPIO before we can use OUT_GPIO
    OUT_GPIO(7);

    // flash LED on and off 10 times
    for (rep = 0; rep < 10; rep++) {
        GPIO_SET = (1 << 7);
        sleep(1);
        GPIO_CLR = (1 << 7);
        sleep(1);
    }

  return 0;

} // main

//
// Set up a memory regions to access GPIO
//
void setup_io()
{
    /* open /dev/mem */
    if ((mem_fd = open("/dev/mem", O_RDWR|O_SYNC) ) < 0) {
        printf("can't open /dev/mem \n");
        exit(-1);
    }

    /* mmap GPIO */
    gpio_map = mmap(
          NULL,                 //Any adddress in our space will do
          BLOCK_SIZE,           //Map length
          PROT_READ|PROT_WRITE, // Enable reading & writting to mapped memory
          MAP_SHARED,           //Shared with other processes
          mem_fd,               //File to map
          GPIO_BASE             //Offset to GPIO peripheral
    );

    close(mem_fd); //No need to keep mem_fd open after mmap

    if (gpio_map == MAP_FAILED) {
          printf("mmap error %d\n", (int)gpio_map); //errno also set !
          exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;
} // setup_io()
