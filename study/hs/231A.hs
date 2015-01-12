solve [] = 0
solve ((a, b, c):xs) = if a + b + c > 1 then y + 1 else y where y = solve xs

main :: IO()
main = do
    n <- getLine
    contents <- getContents
    let input = map ((\(a:b:c:_) -> (a, b, c)) . map (read :: String -> Int) . words) $ lines contents
    print(solve input)
