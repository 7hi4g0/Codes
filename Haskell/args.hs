import System.Environment
import Data.Maybe
import Data.List

maybeRead :: Read a => String -> Maybe a
maybeRead s = case reads s of
				[(x,"")]	-> Just x
				_			-> Nothing

getListFromString :: String -> Maybe [Integer]
getListFromString str = maybeRead $ "[" ++ str ++ "]"

getListFromArgs :: IO [Integer]
getListFromArgs = do
	args <- getArgs
	let argsList = getListFromString $ intercalate ", " args in
		case argsList of
			Just x	-> return x
			Nothing	-> error "Pass only numbers as arguments"

main :: IO ()
main = do
	list <- getListFromArgs
	print $ sum list
