getInts = map read . words

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' _ value [] = value
foldl' f value (x:xs) = foldl' f (f value x) xs

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ value [] = value
foldr' f value (x:xs) = f x (foldr' f value xs)

main = do
    n <- getLine
    let x = getInts n
    print $ foldr' (*) 1 x
