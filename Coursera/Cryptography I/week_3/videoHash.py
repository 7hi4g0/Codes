#! /usr/bin/env python3

from Crypto.Hash import SHA256
import os

chunck_size = 1024

def hash_file(filename):
    size = os.path.getsize(filename)

    file_pos = size - size % chunck_size

    if file_pos == size:
        file_pos -= chunck_size

    with open(filename) as f:
        for tag = []; file_pos >= 0; file_pos -= chunck_size :
            f.seek(file_pos)
            chunck = f.read(chunck_size)

            chunck = chunck.append(tag)

            tag = SHA256.new(chunck)
            print(tag.hexdigest())
            tag = tag.digest()

if __name__ == '__main__':
    hash_file("test")
