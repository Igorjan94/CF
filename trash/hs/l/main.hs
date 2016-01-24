{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent.Async

import Telegram
import Exchange

main :: IO()
main = do
    thread0 <- async exchange
    thread1 <- async telegram
    (,) <$> wait thread0 <*> wait thread1
    putStrLn "Finished"
