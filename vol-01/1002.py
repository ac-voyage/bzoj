#!/usr/bin/env python
# python 2
n = int(raw_input())

if 1 == n:
    print 1
    exit()
if 2 == n:
    print 5
    exit()

a, b = 1, 5
n -= 2
while n > 0:
    a, b = b, 3 * b - a + 2
    n -= 1
print b
