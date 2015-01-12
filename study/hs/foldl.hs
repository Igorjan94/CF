getInts :: String -> [Int]
getInts = map read . words

foldl' :: (a -> b -> a) -> a -> [b] -> a
foldl' _ value [] = value
foldl' f value (x:xs) = foldl' f (f value x) xs

foldr' :: (a -> b -> b) -> b -> [a] -> b
foldr' _ value [] = value
foldr' f value (x:xs) = f x (foldr' f value xs)

data Tree a = Branch a (Tree a) (Tree a) | Node a 

sam :: [Int] -> Tree Int
sam [x] = Node x
sam [] = Node (-1)
sam (x:xs) = Branch x (sam(filter (<x) xs)) (sam(filter (>x) xs))

find :: Tree Int -> Int -> Int
find (Node x) y = if (x == y) then 1 else 0
find (Branch v x y) value = if value == v then 1 else if value > v then (find y value) else (find x value)

dfs :: Tree a -> [a]
dfs (Node x) = [x]
dfs (Branch v x y) = (dfs x) ++ [v] ++ (dfs y)

main = do
    n <- getLine
    let x = getInts n
    print(filter (>=0) (dfs(sam x)))
--    b <- getline
--    let t = getInts b
    print(find (sam x) 1)
--    print $ foldr' (*) 1 x
--    print $ 1 `f` 2
