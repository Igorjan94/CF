{-# LANGUAGE OverloadedStrings #-}

module Telegram where

import Control.Monad
import Control.Concurrent
import Control.Concurrent.MVar 

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Data.Maybe

import Data.Vector (mapM, Vector)
import Data.Text (Text, pack)
import Text.Printf

import Network
import Exchange

token :: String
token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"

api :: String
api = "https://api.telegram.org/bot" 


getUpdates :: IO (Data.Vector.Vector Value)
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
sendMessage _ Nothing = return True


kostyl :: Text -> String
kostyl x = init $ tail $ show x


getWithUsd :: Value -> String -> Maybe Double
getWithUsd _ "USD" = Just 1
getWithUsd conversion value = conversion ^? key (pack value) . _Double


getExchange :: Value -> [String] -> IO (Maybe String)
getExchange conversion (q : src : _ : dest : _) = do
    let x = getWithUsd conversion src
    let y = getWithUsd conversion dest
    let quantity = read q :: Double
    case x of 
        Nothing -> return Nothing
        Just base -> case y of
            Nothing -> return Nothing
            Just value -> return $ Just (q ++ " " ++ src ++ " equals dest " ++ printf "%.2f" (quantity * value / base) ++ " " ++ dest)


convert :: MVar Value -> [String] -> IO (Maybe String)
{-convert rates list@(q : src : _ : dest : date : _) = do-}
    {-print "withDate"-}
    {-print list-}
    {-c <- getConversionByDate date-}
    {-case c of-}
        {-Nothing -> return Nothing-}
        {-Just conversion -> getExchange conversion list-}
convert rates list@(q : src : _ : dest : _) = do
    print list
    conversion <- readMVar rates
    answer <- getExchange conversion list
    return answer
convert _ _ = return Nothing


markAsRead :: (Integer, Bool) -> IO ()
markAsRead (updateId, True) = print $ "markedAsRead " ++ show updateId
markAsRead (updateId, False) = print $ "message is not delivered: " ++ show updateId


proceedMessage :: MVar Value -> Value -> IO (Integer, Bool)
proceedMessage rates update = do
    let Just updateId = update ^? key "update_id" . _Integer
    let Just message = update ^? key "message"
    let Just chatId = message ^? key "chat" . key "id" . _Integer
    let Just text = message ^? key "text" . _String
    let strings = words $ kostyl text
    answer <- convert rates strings
    response <- sendMessage chatId answer
    return (updateId, response)


telegram :: MVar Value -> Int -> IO()
telegram rates delay = forever $ do
    updates <- getUpdates
    proceededMessages <- Data.Vector.mapM (\x -> proceedMessage rates x) updates
    _ <- Data.Vector.mapM markAsRead proceededMessages
    print proceededMessages
    threadDelay delay
