getInts s = map read $ words s

solve :: [Int] -> Int
solve xs = get ([-1000000007]++xs++[1000000007]) 0

get :: [Int] -> Int -> Int
get [x] _ = -1
get (a:b:xs) counter = if a > b then counter else get (b:xs) counter + 1
    
main = do
    s <- getLine
    s <- getLine
    print(solve(getInts s))
--    contents <- getContents
--    let input = map ((\(a:b:_) -> (a, b)) . map (read :: String -> Int) . words) $ lines contents
