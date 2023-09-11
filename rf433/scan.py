from RPi import GPIO
import time, argparse
from collections import defaultdict
import sys

parser = argparse.ArgumentParser(description='Analyze RF signal for Nexa codes')
parser.add_argument('-g', dest='gpio', type=int, default=27, help='GPIO pin (Default: 27)')
parser.add_argument('-s', dest='secs', type=int, default=3, help='Seconds to record (Default: 3)')
parser.add_argument('--raw', dest='raw', action='store_true', default=False, help='Output raw samples')
args = parser.parse_args()

times = []

GPIO.setmode(GPIO.BCM)
GPIO.setup(args.gpio, GPIO.IN)
GPIO.add_event_detect(args.gpio, GPIO.BOTH, callback=lambda ch: times.append(time.perf_counter_ns()//1000))

time.sleep(args.secs)
GPIO.remove_event_detect(args.gpio)
GPIO.cleanup()

# Calculate difference between consecutive times
diff = [b-a for a,b in zip(times, times[1:])]

if args.raw: # Print a raw dump
    for d in diff: print(d, end='\n' if d>5e3 else ' ')
    exit(1)

# Three timing buckets
buckets = list(zip([250,1250,2500], 'x-_'))

lengths = defaultdict(list)
seq = []
for d in diff:
    if d < .7 * buckets[0][0] or d > 1.3 * buckets[-1][0]: # New
        print(f'{d} us ' if d < 1000 else f'\n{d/1000:.2f} ms\n', end='', file=sys.stderr)
        if len(seq) > 10:
            print(file=sys.stderr)
            for k in lengths:
                ls = sorted(lengths[k])
                print(f'{k}: avg {sum(ls) / len(ls):.2f} median {ls[len(ls)//2]}', file=sys.stderr)
            print(''.join(seq))
        seq = []
        lengths = defaultdict(list)
    else:
        b = min((abs(d-a), c) for a,c in buckets)[1]
        seq.append(b) # add to letter sequence
        lengths[b].append(d) # save exact length
