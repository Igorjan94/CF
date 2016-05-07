{-# LANGUAGE OverloadedStrings #-}

import Control.Concurrent
import Control.Concurrent.Async
import Data.Acid
import qualified Data.Set as Set

import Telegram
import Exchange
import Database

main :: IO()
main = do
    acid <- openLocalState (KeyValue Set.empty)
    keys <- query acid AllKeys
    rates <- newEmptyMVar
    thread0 <- async $ exchange rates 100000000
    thread1 <- async $ telegram acid keys rates 10000000
    _ <- (,) <$> wait thread0 <*> wait thread1
    putStrLn "Finished"
    closeAcidState acid
