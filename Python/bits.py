def convert_to_bits(num, pad):
	result = []
	while num > 0:
		if num % 2 == 0:
			result = [0] + result
		else:
			result = [1] + result
		num = num // 2
	while len(result) < pad:
		result = [0] + result
	return result

def string_to_bits(string):
	result = []
	for c in string:
		result = result + convert_to_bits(ord(c), 7)
	return result

def display_bits(bits):
	result = ''
	for b in bits:
		result = result + str(b)
	return result

def bits(num):
	return display_bits(convert_to_bits(num, 7))

