{----------------------------------------------------------------}
{- ACM ICPC 2008-2009, NEERC                                    -}
{- Northern Subregional Contest                                 -}
{- St Petersburg, November 1, 2008                              -}
{----------------------------------------------------------------}
{- Problem H. Holes                                             -}
{-                                                              -}
{- Original idea         Jury                                   -}
{- Problem statement     Dmitry Shtukenberg                     -}
{- Testset               Dmitry Shtukenberg                     -}
{----------------------------------------------------------------}
{- Solution                                                     -}
{-                                                              -}
{- Author                Mikhail Dorkin                         -}
{----------------------------------------------------------------}
 
module Main where

solve 0 = "1"
solve 1 = "0"
solve n | odd n  = "4" ++ solve (n - 1)
        | even n = take (div n 2) (cycle "8")

main = do
  s <- readFile "holes.in"
  writeFile "holes.out" $ (solve $ read s) ++ "\n"
