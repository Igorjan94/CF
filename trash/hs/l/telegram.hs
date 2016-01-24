{-# LANGUAGE OverloadedStrings #-}

module Telegram where

import Control.Monad
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Data.Maybe

import Network

token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"

getUpdates :: IO Value
getUpdates = do
    response <- jsonByURL $ "https://api.telegram.org/bot" ++ token ++ "/getUpdates"
    let Just status = response ^? key "ok" . _Bool
    if status 
        then return $ fromJust $ response ^? key "result"
        else error "Error in telegram"

telegram :: IO()
telegram = forever $ do
    x <- getUpdates 
    print x
    threadDelay 2000000
