import os
from pathlib import Path
from glob import glob

def statistic(level, path, res,max_lv):
    sum = 0
    for x in os.listdir(path):
        x = os.path.join(path,x)
        if os.path.isdir(x):
            sum += statistic(level+1,x,res,max_lv)
        else:
            sum+= os.stat(x).st_size
    
    if level <= max_lv:
        name = os.path.split(path)[1]
        res.append('\t'*level + f'{sum/(2**30):7.2f}GiB  |' + name)
    return sum
def stat(path,level = 0):
    res = []
    statistic(0,path,res,level)
    res.reverse()
    for x in res:
        print(x)
