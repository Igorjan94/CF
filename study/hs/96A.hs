solve :: [Char] -> [Char]
solve ('0' : '0' : '0' : '0' : '0' : '0' : '0' : xy) = "YES"
solve ('1' : '1' : '1' : '1' : '1' : '1' : '1' : xy) = "YES"
solve ('0' : '0' : xs) = solve ('0':xs)
solve ('1' : '0' : xs) = solve ('0':xs)
solve ('0' : '1' : xs) = solve ('1':xs)
solve ('1' : '1' : xs) = solve ('1':xs)
solve _ = "NO"

main :: IO()
main = do
    s <- getLine
--    contents <- getContents
--    let input = map ((\(a:b:_) -> (a, b)) . map (read :: String -> Int) . words) $ lines contents
    putStr(solve s)
