# Decode the two ciphertexts from the Instructors Box below, 
# or the C1, C2 variables - which are the same
#
# We highly recommend that you run your decoding code in the 
# programming language of your choice outside of the 
# this environment, as this system does not provide enough 
# computational resources to successfully decode
#
# After decoding the two ciphertexts, 
# replace the plaintext1 and plaintext2 variables below
# with the decoded ciphertexts

# C1 and C2 are messages in english, 
# encoded using string_to_bits, with 7bit ASCII
# and then XOR'd with a secret key
#
# In pseudo-code:
# C1 = XOR(string_to_bits(plaintext1), secret_key)
# C2 = XOR(string_to_bits(plaintext2), secret_key)

C1 = "1010110010011110011111101110011001101100111010001111011101101011101000110010011000000101001110111010010111100100111101001010000011000001010001001001010000000010101001000011100100010011011011011011010111010011000101010111111110010011010111001001010101110001111101010000001011110100000000010010111001111010110000001101010010110101100010011111111011101101001011111001101111101111000100100001000111101111011011001011110011000100011111100001000101111000011101110101110010010100010111101111110011011011001101110111011101100110010100010001100011001010100110001000111100011011001000010101100001110011000000001110001011101111010100101110101000100100010111011000001111001110000011111111111110010111111000011011001010010011100011100001011001101110110001011101011101111110100001111011011000110001011111111101110110101101101001011110110010111101000111011001111"

C2 = "1011110110100110000001101000010111001000110010000110110001101001111101010000101000110100111010000010011001100100111001101010001001010001000011011001010100001100111011010011111100100101000001001001011001110010010100101011111010001110010010101111110001100010100001110000110001111111001000100001001010100011100100001101010101111000100001111101111110111001000101111111101011001010000100100000001011001001010000101001110101110100001111100001011101100100011000110111110001000100010111110110111010010010011101011111111001011011001010010110100100011001010110110001001000100011011001110111010010010010110100110100000111100001111101111010011000100100110011111011001010101000100000011111010010110111001100011100001111100100110010010001111010111011110110001000111101010110101001110111001110111010011111111010100111000100111001011000111101111101100111011001111"

#####
# CHANGE THESE VARIABLES

plaintext1 = "decoded message"
plaintext2 = "the other decoded message"

# END
#############

#############
# Below is some code that might be useful
#

import codecs

START = 0
WORDS = 101
BITS = ('0', '1')
ASCII_BITS = 7

def display_bits(b):
    """converts list of {0, 1}* to string"""
    return ''.join([BITS[e] for e in b])

def seq_to_bits(seq):
    return [0 if b == '0' else 1 for b in seq]

def pad_bits(bits, pad):
    """pads seq with leading 0s up to length pad"""
    assert len(bits) <= pad
    return [0] * (pad - len(bits)) + bits
        
def convert_to_bits(n):
    """converts an integer `n` to bit array"""
    result = []
    if n == 0:
        return [0]
    while n > 0:
        result = [(n % 2)] + result
        n = n / 2
    return result

def string_to_bits(s):
    def chr_to_bit(c):
        return pad_bits(convert_to_bits(ord(c)), ASCII_BITS)
    return [b for group in 
            map(chr_to_bit, s)
            for b in group]

def bits_to_char(b):
    assert len(b) == ASCII_BITS
    value = 0
    for e in b:
        value = (value * 2) + e
    return chr(value)

def list_to_string(p):
    return ''.join(p)

def bits_to_string(b):
    return ''.join([bits_to_char(b[i:i + ASCII_BITS]) 
                    for i in range(0, len(b), ASCII_BITS)])

def diff():
	diff = []
	tam = min(len(C1), len(C2))
	for i in range(0, tam):
		diff.append(str(ord(C1[i]) ^ ord(C2[i])))
	return diff

def diff_bits(L1, L2):
	tam = min(len(L1), len(L2))
	diff = []
	for i in range(tam):
		diff.append(L1[i] ^ L2[i])
	return diff

def try_word_list():
	f = open('mostCommonWords', 'r')
	for word in [w[:-1] for w in f.readlines()[START:WORDS]]:
		try_words(word)
	f.close()

def try_words(word):
	w = ' ' + word + ' '
	possible = try_word(w)
	if possible:
		print w
		for i, w in possible.iteritems():
			print i, w
	w = ' ' + word.capitalize() + ' '
	possible = try_word(w)
	if possible:
		print w
		for i, w in possible.iteritems():
			print i, w

def try_word(word):
	tamMax = max(len(C1), len(C2))
	tam = tamMax - len(word)
	possible = {}
	for i in range(0, tam):
		newWord = try_word_pos(word, i)
		if newWord != '':
			possible[i] = newWord
	return possible

def replace(M1, word, pos):
	return M1[:pos] + word + M1[pos + len(word):]

def try_word_pos(word, pos):
	offset = 0
	newWord = ''
	for c in word:
		newChar = chr(ord(C1[pos + offset]) ^ ord(c) ^ ord(C2[pos + offset]))
		if (newChar < 'a' or newChar > 'z') and (newChar < 'A' or newChar > 'Z') and newChar != ' ':
			newWord = ''
			break
		offset += 1
		newWord += newChar
	if not are_english(newWord):
		newWord = ''
	return newWord

M1 = ''
M2 = ''
for i in range(len(C1) // 7):
	M1 += '?'
	M2 += '?'
C1 = bits_to_string(seq_to_bits(C1))
C2 = bits_to_string(seq_to_bits(C2))

english_f = codecs.open('/usr/share/dict/american-english', 'r', 'ISO-8859-1')
english_words = [word[:-1] for word in english_f.readlines()]
english_f.close()

def are_english(words):
	for word in words.split():
		if not is_english(word):
			return False
	return True

def is_english(word):
	for w in english_words:
		word.lower()
		w.lower()
		if word in w:
			return True
	return False

def possible_words(word):
	result = []
	for w in english_words:
		word.lower()
		w.lower()
		if word in w:
			result.append(w)
	return result

def update(word, pos):
	global M1
	global M2
	newWord = ''
	offset = 0
	M1 = replace(M1, word, pos)
	for c in word:
		newWord += chr(ord(C1[pos + offset]) ^ ord(c) ^ ord(C2[pos + offset]))
		offset += 1
	M2 = replace(M2, newWord, pos)
	print M1
	print M2

def test_possibles(word, addSpaces = True):
	if addSpaces:
		word = ' ' + word + ' '
	parts = try_word(word)
	possibles = {}
	for pos, word in parts.iteritems():
		for w in word.split():
			for p in possible_words(w):
				if not (word.index(w) != 0 and p.index(w) != 0):
					newPos = pos - p.index(w)
					newWord = try_word_pos(p, newPos)
					if newWord != '':
						possibles[newPos] = p
	return possibles

if __name__ == '__main__':
	try_word_list()
