{-# LANGUAGE OverloadedStrings #-}

module Exchange where

import Control.Monad
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Network

-- Loads conversions from site
getConversion :: MVar Value -> IO Value
getConversion rates = do
    response <- jsonByURL "http://api.fixer.io/latest?base=USD"
    let Just conversion = response ^? key "rates"
    _ <- tryPutMVar rates conversion
    return conversion

-- Starts forever
exchange :: MVar Value -> Int -> IO()
exchange rates delay = forever $ do
    _ <- getConversion rates
    threadDelay delay
