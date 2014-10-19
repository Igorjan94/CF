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
{- Author                Georgiy Korneev                        -}
{----------------------------------------------------------------}
 
module Main where
import Data.List;

solve = (++) "Yes\n" . concat . intersperse "<=>" . map (part . head . (dropWhile (' ' ==)))
part var = "(" ++ var : "<=>" ++ var : ")"

main = readFile "important.in" >>= writeFile "important.out" . solve . tail . lines
