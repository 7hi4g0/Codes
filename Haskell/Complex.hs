data Complex a = Complex a a
	deriving (Eq, Ord, Show)

instance Floating a => Num (Complex a) where
	(Complex aR aI) + (Complex bR bI) = Complex (aR + bR) (aI + bI)
	(Complex aR aI) - (Complex bR bI) = Complex (aR - bR) (aI - bI)
	(Complex aR aI) * (Complex bR bI) = Complex (aR * bR - aI * bI) (aI * bR + aR * bI)
	abs (Complex r i) = Complex (sqrt (r ** 2 + i ** 2)) 0
	signum c@(Complex r i) = let (Complex absolute _) = abs c in
								Complex (r / absolute) (i / absolute)
	fromInteger int = Complex (fromInteger int) 0
