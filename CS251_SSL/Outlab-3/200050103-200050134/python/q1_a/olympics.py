import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--path')
args = parser.parse_args()

count_medal = {}

def update(f):
    fil = open(os.path.join(mypath,f),'r')
    for each in fil:
        l = each.split('-')
        gold = int(l[1])
        silver = int(l[2])
        bronze = int(l[3].split('\n')[0])
        if l[0] in count_medal.keys():
            count_medal[l[0]][0] += gold
            count_medal[l[0]][1] += silver
            count_medal[l[0]][2] += bronze
        else:
            count_medal[l[0]] = [gold, silver, bronze]

def special_sort():
    s = dict(sorted(count_medal.items(),key = lambda kv:(100-int(kv[1][0]),kv[0])))
    print(s)
mypath = args.path
for f in os.listdir(mypath):
    update(f) 
special_sort()
