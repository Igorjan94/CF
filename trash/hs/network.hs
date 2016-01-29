{-# LANGUAGE OverloadedStrings #-}

module Network where

import Data.Aeson
import Control.Monad
import Network.HTTP.Conduit (simpleHttp)
import Data.Maybe

token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"

jsonByURL :: String -> IO Value
jsonByURL url = do
    response <- liftM decode (simpleHttp url)
    case response of
        Nothing -> error "error in parsing jsons"
        Just x -> return x
