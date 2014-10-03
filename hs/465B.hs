pre ('0':xs) = pre xs
pre (' ':xs) = pre xs
pre xs = xs

solve [] = 0
solve (' ':xs) = solve xs
solve ['0'] = 0
solve ('0':' ':'0':xs) = solve ('0':xs)
solve ('0':' ':'1':xs) = 1 + solve ('1':xs)
solve ('1':xs) = 1 + solve xs

main = do
    n <- getLine
    n <- getLine
    print(solve(pre n))
