getInts :: String -> [Int]
getInts = map read . words

g 0 = 0
g n = (n `mod` 10) + (g $ n `div` 10)

main = do
    x <- getLine
    let [n] = getInts x
    print $ minimum [sum $ take n [a | a <- [1..1000000], g a == k] | k<- [1..50]]
