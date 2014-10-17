from Crypto.Cipher import AES

def bytesXor(a, b, strict=True):
    if len(a) == len(b):
        values = zip(a, b)
    elif strict:
        raise Exception('Different block sizes')
    elif len(a) < len(b):
        values = zip(a, b[:len(a)])
    else:
        values = zip(a[:len(b)], b)

    return bytes([x ^ y for (x, y) in values])

def decryptCBC(key, cipher):
    plain = b''
    cipher = [cipher[i: i + 16] for i in range(0, len(cipher), 16)]

    last = cipher[0]

    blockFn = AES.new(key)

    for block in cipher[1:]:
        plain += bytesXor(blockFn.decrypt(block), last)
        last = block

    return plain.decode("utf-8")

def decryptCTR(key, cipher):
    plain = b''
    cipher = [cipher[i:i + 16] for i in range(0, len(cipher), 16)]

    ctr = int.from_bytes(cipher[0], 'big')

    blockFn = AES.new(key)

    for block in cipher[1:]:
        plain += bytesXor(blockFn.encrypt(ctr.to_bytes(16, 'big')), block, False)
        ctr += 1

    return plain.decode("utf-8")
