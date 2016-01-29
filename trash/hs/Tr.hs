module Main where

import System.Environment
import System.Exit
import Data.Maybe

type CharSet = String

repl :: [(Char, Char)] -> Char -> Char
repl [] c = c
repl ((fr, to) : xs) c = if c == fr then to else repl xs c

del :: CharSet -> Char -> Maybe Char
del [] c = Just c
del (x:xs) c = if c == x then Nothing else del xs c

tr :: CharSet -> Maybe CharSet -> String -> String
tr from (Just toShort) s = map (repl (zip from (toShort ++ replicate (length from - length toShort) (last toShort)))) s
tr from Nothing s        = map fromJust (filter isJust (map (del from) s))

parse :: [String] -> String -> String
parse ["-d", f] s = tr f Nothing s
parse (f:t:_)   s = tr f (Just t) s
parse (f:_)     _ = "Only one param :("
parse []        _ = "No params :("

main :: IO ()
main = do
    args <- getArgs
    line <- getLine
    putStr $ parse args line
