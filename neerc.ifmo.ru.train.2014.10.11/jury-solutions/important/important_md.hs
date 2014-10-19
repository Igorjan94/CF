{----------------------------------------------------------------}
{- ACM ICPC 2008-2009, NEERC                                    -}
{- Northern Subregional Contest                                 -}
{- St Petersburg, November 1, 2008                              -}
{----------------------------------------------------------------}
{- Problem I. Important Wires                                   -}
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

solve s = "Yes\n" ++ (tautology $ map firstSymbol $ tail $ lines s) ++ "\n"

firstSymbol s = head $ dropWhile (== ' ') s

tautology list = concatMap (: " | ") list ++ "~" ++ [head list]

main = do
  s <- readFile "important.in"
  writeFile "important.out" $ solve s
