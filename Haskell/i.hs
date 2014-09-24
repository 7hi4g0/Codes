data I a = I a
	deriving (Eq, Ord, Show)

instance Num a => Num (I a) where
	(I first) + (I second) = I $ first + second
	(I first) - (I second) = I $ first - second
	(I first) * (I second) = I $ first * second
	abs (I first) = I $ abs first
	signum (I first) = I $ signum first
	fromInteger int = I $ fromInteger int
