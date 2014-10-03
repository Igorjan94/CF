solve xs = if length (filter (`elem` ['H', 'Q', '9']) xs) > 0 then "YES" else "NO"

main = do
    s <- getLine
    putStr(solve s)
