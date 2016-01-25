{-# LANGUAGE OverloadedStrings #-}

module Telegram where

import Control.Monad
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Data.Maybe

import Data.Vector (mapM)
import Data.Text (Text)

import Network

token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"
api = "https://api.telegram.org/bot" 

getUpdates = do
    response <- jsonByURL $ api ++ token ++ "/getUpdates"
    let Just status = response ^? key "ok" . _Bool
    if status 
        then return $ fromJust $ response ^? key "result" . _Array
        else error "Error in telegram"

sendMessage :: Integer -> Maybe String -> IO Bool
sendMessage chatId (Just text) = do
    response <- jsonByURL $ api ++ token ++ "/sendMessage?chat_id=" ++ show chatId ++ "&text=" ++ text
    let Just bool = response ^? key "ok" . _Bool
    return bool
sendMessage chatId Nothing     = return True

kostyl :: Text -> String
kostyl x = init $ tail $ show x

convert :: [String] -> Maybe String
convert (quantity : from : _ : to : xs) = Just (quantity ++ " " ++ from ++ " equals to " ++ quantity ++ " " ++ to)
convert _ = Nothing

markAsRead :: (Integer, Bool) -> IO()
markAsRead (updateId, True) = print $ "markAsRead " ++ show updateId
markAsRead _ = print "fuuuu"

proceedMessage :: Value -> IO (Integer, Bool)
proceedMessage update = do
    let Just id = update ^? key "update_id" . _Integer
    let Just message = update ^? key "message"
    let name = message ^? key "from" . key "first_name" . _String
    let Just chatId = message ^? key "chat" . key "id" . _Integer
    let Just text = message ^? key "text" . _String
    let strings = words $ kostyl text
    let answer = convert strings
    response <- sendMessage chatId answer
    return (id, response)

telegram :: IO()
telegram = forever $ do
    updates <- getUpdates
    print updates
    proceededMessages <- Data.Vector.mapM proceedMessage updates
    print proceededMessages
    proceededMessages <- Data.Vector.mapM markAsRead proceededMessages
    print proceededMessages
    threadDelay 5000000
