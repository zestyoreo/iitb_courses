import os
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('--path1')
parser.add_argument('--path2')
parser.add_argument('--output')
args = parser.parse_args()

win_websites = []
winpath = args.path1
fil = open(winpath,'r')
for each in fil:
    x = each.split('https://')[1]
    x = x.split('\n')[0]
    x = x.split('www.')[1]
    win_websites.append(x)
    l = each.split('/')
    if '\n' in l[2]:
        website = l[2].split('\n')[0]
    else:
        website = l[2]        
    print(website)

uidpath = args.path2
fil2 = open(uidpath,'r')
win_count = 0
winners = []
for each in fil2:
    l = each.split('||')
    user_name, ip_address, url = l[0], l[2], l[3].split('\n')[0]
    complete_url = 'a'
    if 'https://www.' in url:
        complete_url = url
    elif 'www.' in url:
        complete_url = "https://"+url
    else:
        complete_url = "https://www."+url
    for i in win_websites:
        if i in url:
            print("user_name - ",user_name," : Winner - Lucky draw!!! - ",url)
            win_count += 1
            winners.append([user_name,ip_address,complete_url])
            break

print(win_count)

output_path = args.output+"winner.txt"
file = open(output_path,'w')
for wi in winners:
    data = wi[0]+"||"+wi[1]+"||"+wi[2]+"\n"
    file.write(data)
file.close()