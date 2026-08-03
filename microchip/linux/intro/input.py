#!/usr/bin/env python
from mpio import Input
input = Input("event0")
while True:
	
        print (input.read())

