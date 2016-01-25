{-# LANGUAGE OverloadedStrings #-}

module Exchange where

import Control.Monad
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Data.Maybe

import Network

getConversion :: IO Value
getConversion = do
    response <- jsonByURL "http://api.fixer.io/latest?base=USD"
    let Just conversion = response ^? key "rates"
    return conversion

exchange :: IO()
exchange = forever $ do
    print "exchange"
    threadDelay 200000000
