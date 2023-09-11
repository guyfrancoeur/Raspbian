// Code adapted from example by Gert van Loo & Dom from: http://elinux.org/Rpi_Low-level_peripherals#C_2
// use gcc -Wall -o flash_led flash_led.c

#define BCM2708_PERI_BASE        0x20000000
#define GPIO_BASE                (BCM2708_PERI_BASE + 0x200000) /* GPIO controller */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <iostream>
#include <chrono> // std::chrono::microseconds
#include <thread> // std::thread::sleep_for

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
  using namespace std::chrono_literals; //for usage of us, ms

  char z12Da[41] = "1001101111001011111111001101001111001100";
  char z12Db[41] = "1001101111001011111111001101001111000011";
  char z12S[41] =  "1001101111001011111111001101001110101010";
  char z12Ua[41] = "1001101111001011111111001101001111101110";
  char z12Ub[41] = "1001101111001011111111001101001111100001";

//12D s=332,l=692,r=8812 s=332,l=692,r=15160
//12S s=348,l=708,r=8636 s=332,l=696,r=8624 s=336,l=696,r=8984
//12U s=348,l=708,r=8804 s=332,l=692,r=15152
/*
if i == '1':
                GPIO.output(TRANSMIT_PIN, 1)
                time.sleep(short_delay)
                GPIO.output(TRANSMIT_PIN, 0)
                time.sleep(long_delay)
            elif i == '0':
                GPIO.output(TRANSMIT_PIN, 1)
                time.sleep(long_delay)
                GPIO.output(TRANSMIT_PIN, 0)
                time.sleep(short_delay)
*/
  int s=332, l=692, r=8812;
  setup_io();

  INP_GPIO(17); // must use INP_GPIO before we can use OUT_GPIO
  OUT_GPIO(17);

  for (short i=1; i<= 3; ++i) {
    short j=0;
    if (z12Da[j] == '1') {
      GPIO_SET = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(s));
      GPIO_CLR = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(l));

    } else {
      GPIO_SET = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(l));
      GPIO_CLR = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(s));

//      std::this_thread::sleep_for(1000ms); //example 1sec == 1000000us
    }
    ++j;
  }
  for (short i=1; i<= 6; ++i) {
    short j=0;
    if (z12Db[j] == '1') {
      GPIO_SET = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(s));
      GPIO_CLR = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(l));

    } else {
      GPIO_SET = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(l));
      GPIO_CLR = (1 << 17);
      std::this_thread::sleep_for(std::chrono::microseconds(s));
    }
    ++j;
  }

  return 0;

} //end of  main

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
          printf("mmap error %ld\n", (long)gpio_map); //errno also set !
          exit(-1);
    }

    // Always use volatile pointer!
    gpio = (volatile unsigned *)gpio_map;
} // setup_io()
