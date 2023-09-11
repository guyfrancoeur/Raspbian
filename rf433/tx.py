import time
import sys
import RPi.GPIO as GPIO


#zCCDa3 : z12Da3Db6, z12Sa3,z12Ua3Ub6

z28bit = '1001101111001011111111001101'
z4bit = [0:'1111',1:'1110',2:'1101',12:'0011',13:'0010']
z8bit = ['Da':'11001100','Db':'11000011','Sa':'10101010','Ua':'11101110','Ub':'11100001']

z12Da = '1001101111001011111111001101001111001100' #3
z12Db = '1001101111001011111111001101001111000011' #6
z12S =  '1001101111001011111111001101001110101010' #3
z12Ua = '1001101111001011111111001101001111101110' #3
z12Ub = '1001101111001011111111001101001111100001' #6
#12D s=332,l=692,r=8812 s=332,l=692,r=15160
#12S s=348,l=708,r=8636 s=332,l=696,r=8624 s=336,l=696,r=8984
#12U s=348,l=708,r=8804 s=332,l=692,r=15152

short_delay = 0.000300
long_delay = 0.000660
extended_delay = 0.008000

NUM_ATTEMPTS = 1
TRANSMIT_PIN = 17

def transmit_code(code):
    '''Transmit a chosen code string using the GPIO transmitter'''
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(TRANSMIT_PIN, GPIO.OUT)
    for t in range(NUM_ATTEMPTS):
        for i in code:
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
            else:
                continue
        GPIO.output(TRANSMIT_PIN, 0)
        time.sleep(extended_delay)
    GPIO.cleanup()

if __name__ == '__main__':
    for argument in sys.argv[1:]:
        exec('transmit_code(' + str(argument) + ')')
