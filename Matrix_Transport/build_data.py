#!/usr/bin/python

import random


elem_left = 1000
matrix_row = 10000
matrix_col = 10000

elem_sample = []
for i in xrange(-1000, 1000):
	elem_sample.append(str(i))

elem_index = []
for i in xrange(0, matrix_col):
	elem_index.append(i)


def print_elem(num, index = None, elem = None):
	if num == 0:
		print "0\n"
	else:
		index = [str(i) for i in index]
		print "%d %s" %(num, " ".join(index))
		print "%s" % " ".join(elem)


print "%d %d" % (matrix_row, matrix_col)
for i in xrange(0, matrix_col):
	if elem_left == 0:
		print_elem(0)
	else:
		count = random.randint(0, 79)
		i = random.sample(elem_index, count)
		i.sort()
		e = random.sample(elem_sample, count)
		elem_left -= count
		print_elem(count, i, e)
		if elem_left < 0:
			elem_left = 0
