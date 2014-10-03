import Data.Char
solve :: [Char] -> [Char]
solve (x:xs) = if length (filter (`elem` ['A'..'Z']) xs) == (length xs) then [if x >= 'a' then toUpper x else toLower x] ++ map toLower xs else [x]++xs

main :: IO()
main = do
    s <- getLine
    putStr(solve s)
