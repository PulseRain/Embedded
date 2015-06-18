import os
import sys


if (len(sys.argv) < 2):
        print "not enough parameters"
        os._exit(1)


content = open(sys.argv[1]).readlines()

index = 0
for line in content :
    if (index % 2):
        print line,
        print prev,
    
    prev = line
    index = index + 1
    