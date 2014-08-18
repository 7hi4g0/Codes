#! /usr/bin/env python3

import os
import sys
import math
from Crypto.Hash import SHA256

chunck_size = 1024

def videoHash(filename):
    file_size = os.path.getsize(filename)

    chuncks = math.ceil(file_size / chunck_size)

    with open(filename, mode = 'rb') as f:
        tags = []
        tag = bytes()
        for file_pos in range(chunck_size * (chuncks - 1), -chunck_size, -chunck_size):
            f.seek(file_pos)

            chunck = f.read(chunck_size)
            chunck += tag

            tag = SHA256.new(chunck)
            tags.append(tag.hexdigest())
            tag = tag.digest()

    return tags

def usage():
    print("""
    USAGE:
    videoHash filename
    """)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        usage()
    else:
        tags = videoHash(sys.argv[1])
        print(tags[-1])

