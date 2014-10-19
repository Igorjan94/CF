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
{- Author                Georgiy Korneev                        -}
{----------------------------------------------------------------}
 
module Main where
import List
import Monad

main = do
    [s1, s2, t1, t2] <- (liftM words . readFile) "enchanted.in"
    let result = sort (s1 `zip` reverse s2) == sort (t1 `zip` reverse t2)
    writeFile "enchanted.out" (if result then "Yes" else "No")
