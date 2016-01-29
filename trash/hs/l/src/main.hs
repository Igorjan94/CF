{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent
import Control.Concurrent.MVar
import Control.Concurrent.Async

import Telegram
import Exchange

main :: IO()
main = do
    rates <- newEmptyMVar
    thread0 <- async $ exchange rates 100000000
    thread1 <- async $ telegram rates 10000000
    (,) <$> wait thread0 <*> wait thread1
    putStrLn "Finished"
