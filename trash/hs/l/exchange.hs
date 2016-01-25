{-# LANGUAGE OverloadedStrings #-}

module Exchange where

import Control.Monad
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Text.Regex.Posix
import Text.Regex.Base
import Data.Maybe

import Network

{-getConversionByDate :: String -> IO (Maybe Value)-}
{-getConversionByDate date = do-}
    {-matches <- date =~~ "[0-9]{4}-[0-9]{2}-[0-9]{2}" :: IO Bool-}
    {-if (not matches) -}
        {-then return Nothing-}
        {-else do-}
            {-response <- jsonByURL $ "http://api.fixer.io/" ++ date ++ "?base=USD"-}
            {-print response-}
            {-let error = response ^? key "error"-}
            {-case error of-}
                {-Nothing -> return Nothing-}
                {-Just x -> return $ response ^? key "rates"-}

getConversion :: MVar Value -> IO Value
getConversion rates = do
    response <- jsonByURL "http://api.fixer.io/latest?base=USD"
    let Just conversion = response ^? key "rates"
    tryPutMVar rates conversion
    return conversion

exchange :: MVar Value -> Int -> IO()
exchange rates delay = forever $ do
    getConversion rates
    threadDelay delay
