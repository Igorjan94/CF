getInts :: String -> [Int]
getInts = map read . words

f True = 1
f False = 0

main = do
    s <- getLine
    let [n, t, c] = getInts s
    s <- getLine
    let xs = getInts s
        y = foldl (\ (a, b) (x, y) -> (a - f (y > t) + f (x > t), b + f (a == 0))) (count, 0) xz
            where count = (length(filter(>t) (take c xs))) 
                  xz = (zip (drop c xs) xs)
    print(snd y + f (fst y == 0))
