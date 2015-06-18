import os
import sys


if (len(sys.argv) < 2):
        print "not enough parameters"
        os._exit(1)


content = open(sys.argv[1]).readlines()

index = 0
for line in content :
    print "    CONSOLE_PRINT(\"", line.rstrip(), "\\n\");"
    