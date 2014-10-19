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
{- Author                Georgiy Korneev                        -}
{----------------------------------------------------------------}
 
module Main where

holes 0 = "1"
holes 1 = "0"
holes n = take (n `mod` 2) "4" ++ take (n `div` 2) (cycle "8")

main = readFile "holes.in" >>= writeFile "holes.out" . (++ "\n") . holes . read
