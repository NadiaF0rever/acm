#!/usr/bin/python
import random

s = lambda: random.randint(1, 6)
line = lambda: "%d %d %d %d %d" % (s(), s(), s(), s(), s())

def block():
    for i in xrange(0, 13):
        print "%s" % line();


for i in xrange(0, 20):
    block()
