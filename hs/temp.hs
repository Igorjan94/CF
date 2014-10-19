getInts s = map read $ words s

n = 1000

main = do
    let x = [a * b | a <- [2, 3..n], b <- [2, 3..n `div` 2], a * b <= n]
        y = [r | r <- [2, 3..n], not (r `elem` x)]
--        z = take 10 [(t, t+2) | t <- [2, 3..], (t `elem` y) && ((t + 2) `elem` y)]
--    print(x)
    print y
