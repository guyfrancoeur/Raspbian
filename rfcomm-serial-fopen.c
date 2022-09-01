// rfcomm-serial-fopen
// compilation :
//  gcc -Wall -o rfcomm-serial-fopen rfcomm-serial-fopen.c -lbluetooth

#include <stdio.h>

int main(int argc, char **argv)
{
    char message[9];
    int i;
    FILE * robot = fopen("/dev/rfcomm0", "w");

    // send a message
    int duration, frequency;
    message[0]=113; // set speaker
    duration = 2000; // 2000 milleseconds = 2 seconds
    message[1]= duration >> 8;  // high-order 8 bits
    message[2]= duration % 256;  // low-order 8 bits
    frequency = 880; // A above middle C
    message[3]= frequency >> 8; // high-order 8 bits
    message[4]= frequency % 256;// low-order 8 bits
    message[5]= -1 ; // end of data set
    message[6]= 0;   // not used
    message[7]= 0;   // not used
    message[8]= 0;   // not used
    for (i = 0; i < 9; i++)
      fputc(message[i], robot);

    message[0]=113; // set speaker
    duration = 3000; // 3000 milleseconds = 3 seconds
    message[1]= duration >> 8;  // high-order 8 bits
    message[2]= duration % 256;  // low-order 8 bits
    frequency = 440; // A near middle C
    message[3]= frequency >> 8; // high-order 8 bits
    message[4]= frequency % 256;// low-order 8 bits
    message[5]= -1 ; // end of data set
    message[6]= 0;   // not used
    message[7]= 0;   // not used
    message[8]= 0;   // not used
    for (i = 0; i < 9; i++)
      fputc(message[i], robot);

    fclose(robot);
    return 0;
}
