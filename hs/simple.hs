qs [] = []
qs (x:xs) = (qs (filter(<=x) xs)) ++ [x] ++ (qs (filter(>x) xs))


main :: IO()
main = do
    let y = take 100 [a * b | a<-[2, 3..5], b <- [2, 3..5]]
    print(y)
    print(qs y)
