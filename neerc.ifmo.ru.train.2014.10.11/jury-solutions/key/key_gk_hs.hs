{----------------------------------------------------------------}
{- ACM ICPC 2008-2009, NEERC                                    -}
{- Northern Subregional Contest                                 -}
{- St Petersburg, November 1, 2008                              -}
{----------------------------------------------------------------}
{- Problem K. Key to Success                                    -}
{-                                                              -}
{- Original idea         Andrew Stankevich                      -}
{- Problem statement     Andrew Stankevich                      -}
{- Testset               Andrew Stankevich                      -}
{----------------------------------------------------------------}
{- Solution                                                     -}
{-                                                              -}
{- Author                Georgiy Korneev                        -}
{----------------------------------------------------------------}
 
module Main where
import Data.List;

solve [[_, m], as] = reverse $ snd $ snd $ iterate f (1, (sort as, [])) !! fromInteger m
solve _ = error ""

f (bound, ([], result)) = (bound * 2, ([], bound : result))
f (bound, (a:as, result))
    | a <= bound = f (bound + a, (as, result))
    | otherwise  = (bound * 2, (a : as, bound : result))

main = readFile "key.in" >>= writeFile "key.out" . unwords . map show . solve . map (map read . words) . lines
