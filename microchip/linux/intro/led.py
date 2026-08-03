#!/usr/bin/env python
import argparse
from mpio import LED

arg = argparse.ArgumentParser()
arg.add_argument("--off", action="store_true", default=False, help = "Turn off LED")
args = arg.parse_args()
if args.off == True:
        print ("Turning off LED")
        b = LED("blue", False)
else:
        print ("Turning on Blue LED")
        b = LED("blue", True)
