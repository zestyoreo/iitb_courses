import os

with open('instances.txt') as f:
    lines_raw = f.readlines()
    lines = [x.strip().split() for x in lines_raw]
    n = 1
    for x in lines:
        os.system('sox ../corpus/data/wav/{}/{}.wav wave{}.wav trim {} {}'.format(x[0][:15],x[0],str(n),x[2],x[3]))
        n += 1