{-# LANGUAGE OverloadedStrings #-}

module Exchange where

import Control.Monad
import Control.Concurrent

import Network

exchange :: IO()
exchange = forever $ do
    print "exchange"
    threadDelay 2000000 
