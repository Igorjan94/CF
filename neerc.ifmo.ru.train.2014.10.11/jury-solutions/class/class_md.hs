{----------------------------------------------------------------}
{- ACM ICPC 2008-2009, NEERC                                    -}
{- Northern Subregional Contest                                 -}
{- St Petersburg, November 1, 2008                              -}
{----------------------------------------------------------------}
{- Problem C. Class                                             -}
{-                                                              -}
{- Original idea         Georgiy Korneev                        -}
{- Problem statement     Georgiy Korneev                        -}
{- Testset               Georgiy Korneev                        -}
{----------------------------------------------------------------}
{- Solution                                                     -}
{-                                                              -}
{- Author                Mikhail Dorkin                         -}
{----------------------------------------------------------------}
 
module Main where

solve (n:r:c:[]) =
  let ans = min (min r c) ((n + 1) `div` 2) in
  show ans ++ "\n" ++ (concatMap (++ "\n") $ solve' True ans (n - 2 * ans + 1) r c)

solve' first ans spare 0 c = []
solve' first ans spare r c =
  let amust = if first then ans else if (ans <= 0) then 0 else 1 in
  let take = min spare (c - amust) in
  (row (amust + take) c) : solve' False (ans - 1) (spare - take) (r - 1) c

row t total = (take t $ repeat '#') ++ (take (total - t) $ repeat '.')

parse :: [Char] -> [Int]
parse s = map read $ words s

main = do
  s <- readFile "class.in"
  writeFile "class.out" $ solve $ parse s
  print $ solve $ parse s
