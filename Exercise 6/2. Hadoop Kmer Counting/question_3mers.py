from operator import itemgetter
import sys

corpus = []

def takeSecond(elem):
    return elem[1]

for line in sys.stdin:
    
    line = line.strip()


    word, count = line.split('\t', 1)

   
    try:
        count = int(count)
    except ValueError:
        continue

    p = (word, count)

    corpus.append(p)

    corpus.sort(key = takeSecond, reverse=True)

for i in range(0, 10):
    if(i >= len(corpus)):
        break
    element = corpus[i]
    print ('%s\t%s' % (element[0], element[1]))





   
    

