{----------------------------------------------------------------}
{- ACM ICPC 2008-2009, NEERC                                    -}
{- Northern Subregional Contest                                 -}
{- St Petersburg, November 1, 2008                              -}
{----------------------------------------------------------------}
{- Problem E. Enchanted Mirror                                  -}
{-                                                              -}
{- Original idea         Andrew Lopatin                         -}
{- Problem statement     Andrew Lopatin                         -}
{- Testset               Andrew Lopatin                         -}
{----------------------------------------------------------------}
{- Solution                                                     -}
{-                                                              -}
{- Author                Mikhail Dorkin                         -}
{----------------------------------------------------------------}
 
module Main where

import List

solve (s1:s2:t1:t2:[]) = (pairs s1 s2) == (pairs t1 t2)

pairs a b = sort $ zip a $ reverse b

main = do
  s <- readFile "enchanted.in"
  writeFile "enchanted.out" $ if (solve $ lines s) then "Yes\n" else "No\n"
