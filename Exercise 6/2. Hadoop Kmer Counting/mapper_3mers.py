

import sys

for line in sys.stdin:

    line = line.strip()

    for i in range(0, len(line) -2):
        key = line[i] + line[i+1] + line[i+2]
        print ('%s\t%s' % (key, 1))

    

    