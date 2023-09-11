from RPi import GPIO
import time, argparse

parser = argparse.ArgumentParser(description='send RF433 signal')
parser.add_argument('-f', dest='fn', type=str, default='down.txt', help='')
args = parser.parse_args()

prg=""
wait = {'x': 510, '-': 817, '_':0, 'W': 8750, 'w':4850}
with open(args.fn) as f:
    content = f.read().splitlines()
for line in content:
    prg+='W'+line+'w'

print(prg)

GPIO.setmode(GPIO.BCM)
GPIO.setup(17, GPIO.OUT)

for i,c in enumerate(prg):
    # set pin 17 high for 250 microseconds
    GPIO.output(17, GPIO.HIGH if (i&1) else GPIO.LOW)
    time.sleep((wait[c])/100000.0)

# Clean up GPIO
GPIO.setup(17, GPIO.IN)
GPIO.cleanup()
