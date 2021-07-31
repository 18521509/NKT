import os
from os.path import join,isdir
import pandas as pd
import time

#Đường dẫn tới các thư mục gốc
anime = "G:\Shared drives\[miyastr.xyz] Anime - Cartoons\Anime - Cartoons"
anime4k = "G:\Shared drives\[miyastr.xyz] 4K Ultra HD Stuffs\Anime - Cartoons"

movie = 'G:\Shared drives\[miyastr.xyz] Movies\Movies - Phim lẻ'
movie4k = 'G:\Shared drives\[miyastr.xyz] 4K Ultra HD Stuffs\Movies'

movies_collection = "G:\Shared drives\[miyastr.xyz] Movie Collections\Collections - Tuyển tập"

tv_series = 'G:\Shared drives\[miyastr.xyz] TV Series - Shows\TV Series - Phim bộ'
tv_series4k = 'G:\Shared drives\[miyastr.xyz] 4K Ultra HD Stuffs\TV Series - Shows - Sports\TV Series - Phim bộ'



# Đường dẫn tới thư mục chứa file excel, thời gian trễ (phút)
path = 'G:\My Drive\Draw'
delay = 5 


def df_film(path):
    films = sorted(os.listdir(path))
    stt = [f" {x+1} " for x in range(len(films))]
    df = pd.DataFrame({'STT' : stt,'Tên phim': films})
    return df

def savefile(name,path,path4k=None):
    income_sheets = dict()
    for folder in os.listdir(path):
        if isdir(join(path,folder)):
            fold = folder[:31]
            income_sheets[fold] = df_film(join(path,folder))

    if path4k is not None:
        for folder in os.listdir(path):
            if isdir(join(path,folder)):
                fold = folder[:28]
                income_sheets['4K_' + fold] = df_film(join(path,folder))

    writer = pd.ExcelWriter(name+'.xlsx', engine='xlsxwriter')

    for sheet_name in income_sheets.keys():
        income_sheets[sheet_name].to_excel(writer, sheet_name=sheet_name, index=False)
    writer.save()
   
i = 0
while True:
    savefile(join(path,'Movies - Phim Lẻ'),movie,movie4k)
    savefile(join(path,'Movies collection - Tuyển tập'),movies_collection)
    savefile(join(path,'TV Series - Phim dài tập'),tv_series,tv_series4k)
    savefile(join(path,'Anime- Hoạt hình'),anime,anime4k)
    time.sleep(delay*60)