getInts s = map read $ words s

solve :: Int -> Int -> Int -> Int
solve a b c = if (max b (2 * a) >= c) then -1 else max b (2 * a)
    
main = do
    s <- getLine
    a <- getLine
    b <- getLine
    print(solve (minimum $ getInts a) (maximum $ getInts a) (minimum $ getInts b))
--    contents <- getContents
--    let input = map ((\(a:b:_) -> (a, b)) . map (read :: String -> Int) . words) $ lines contents
