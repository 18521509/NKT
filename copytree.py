from shutil import copy2 as copy, rmtree
from os.path import basename
from os.path import join,isfile, isdir, exists
from os import makedirs,listdir,remove
from glob import glob

def delete(path):
    if isdir(path):
        rmtree(path)
    else:
        remove(path)

def _copytree(src,dst, replace = True, create_sub_folder = False):
    if isdir(src):
        copytree(src,dst,replace,create_sub_folder)
    else:
        copy(src,dst)


def copytree(src,dst, replace = False, create_sub_folder = False):
    """
    src: source directory
    dst: destination directory
    replace (default: False): Replace exists file, folder
    create_sub_folder (default: False): create sub folder in dst
    """
    
    if create_sub_folder:
        name = basename(src)
        dst = join(dst,name)

    if not exists(dst):
        makedirs(dst)

    for name in listdir(src):
        sub_src = join(src,name)
        sub_dst = join(dst,name)
        if exists(sub_dst):
            if not replace:
                if isdir(sub_src):
                    copytree( src = sub_src,dst = sub_dst,replace = replace ,create_sub_folder = False )
                else:
                    continue
            else:
                delete(sub_dst)
        elif isdir(sub_src):
            makedirs(sub_dst)

        if isdir(sub_src):
            copytree( src = sub_src,dst = sub_dst,replace = replace ,create_sub_folder = False )
            
        else:
            copy(sub_src,dst)

        

