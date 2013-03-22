def leaps(last):
	leap = 0
	d400 = 0
	d100 = 0
	d4 = 0
	for year in range(1,last + 1):
		if year % 400 == 0:
			leap += 1
		elif year % 4 == 0 and year % 100 != 0:
			leap += 1
		if year % 400 == 0:
			d400 += 1
			d100 += 1
			d4 += 1
		elif year % 100 == 0:
			d100 += 1
			d4 += 1
		elif year % 4 == 0:
			d4 += 1
	print leap, d400, d100, d4
	print year // 400, year // 100, year // 4

