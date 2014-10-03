import Data.Char
solve xs = if length (filter isUpper xs) > length (filter isLower xs) then map toUpper xs else map toLower xs

main = do
    s <- getLine
    putStr(solve s)
