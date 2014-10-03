solve [] prev = prev
solve ((a, b):xs) prev = (max y (solve xs y)) where y = prev - a + b

main :: IO()
main = do
    n <- getLine
    contents <- getContents
    let input = map ((\(a:b:_) -> (a, b)) . map (read :: String -> Int) . words) $ lines contents
    print(solve input 0)
