splitEvery :: Int -> [a] -> [[a]]
splitEvery _ [] = []
splitEvery n list = first : (splitEvery n rest)
	where
		(first, rest) = splitAt n list

comparePills :: (Num a, Ord a) => [a] -> [a] -> Ordering
comparePills group1 group2 =
	let
		sum1 = sum group1
		sum2 = sum group2
	in
		compare sum1 sum2

findPill :: (Num a, Ord a) => [a] -> a
findPill pills = 
	let 
		[group1, group2, group3] = splitEvery 4 pills
	in 
		case comparePills group1 group2 of
			EQ ->
				case comparePills (take 3 group1) (take 3 group3) of
					EQ -> group3!!3 
					LT -> 
						case compare (group3!!0) (group3!!1) of
							EQ -> group3!!2
							LT -> group3!!1
							GT -> group3!!0
					GT -> 
						case compare (group3!!0) (group3!!1) of
							EQ -> group3!!2
							LT -> group3!!0
							GT -> group3!!1
			LT ->
				case comparePills (take 3 group1) (take 3 group2) of
					EQ ->
						case compare (group1!!3) (group2!!3) of
							EQ -> 
							LT ->
							GT ->
					LT ->
					GT ->
			GT -> group1!!0 
