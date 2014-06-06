#!/usr/bin/python
import random

chars = ('[', '[', ']', ']', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p')

def generate_char():
	index = int(random.random() * len(chars))
	return chars[index]

LINE = 100000
WORD_LEN = 30

for i in xrange(0, LINE):
	line = []
	for j in xrange(0, WORD_LEN):
		line.append(generate_char())

	print "".join(line)
