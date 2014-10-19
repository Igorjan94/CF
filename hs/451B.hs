import Data.List.Ordered
import Text.Printf

getInts s = map read $ words s

get :: [Int] -> [Int] -> ([Int], [Int])
get f [x] = (f, [])
get f (a:b:xs) = if (a < b) then get (a:f) (b:xs) else (f, a:b:xs)

got :: [Int] -> [Int] -> ([Int], [Int])
got f [x] = ([x], [])
got f [] = ([], [])
got f (a:b:xs) = if (a > b) then got (a:f) (b:xs) else (a:f, b:xs)
    
main = do
    s <- getLine
    s <- getLine
    let t = getInts s
        y = get [] t
        u = got [] (snd y)
--    print(t);
--    print(y);
--    print(u);
    if isSorted ((reverse $ fst y) ++ (fst u) ++ (snd u))
        then printf "yes\n%d %d\n" (length (fst y) + 1) (length t - (length (snd u)))
        else printf "no\n"
