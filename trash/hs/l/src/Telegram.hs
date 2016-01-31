{-# LANGUAGE OverloadedStrings #-}
{-# LANGUAGE ScopedTypeVariables #-}

module Telegram where

import Control.Monad
import Control.Monad.State.Strict
import Control.Concurrent

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Data.Maybe

import Data.Vector (mapM, Vector, filter, map, fromList, toList)
import Data.Text (Text, pack)
import Data.Char (toUpper)
import Text.Printf

import Network
import Database
import Data.Acid

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
    let x = getWithUsd conversion (Prelude.map toUpper src)
    let y = getWithUsd conversion (Prelude.map toUpper dest)
    let quantity = read q :: Double
    case x of 
        Nothing -> return Nothing
        Just base -> case y of
            Nothing -> return Nothing
            Just value -> return $ Just (q ++ " " ++ src ++ " equals to " ++ printf "%.2f" (quantity * value / base) ++ " " ++ dest)
getExchange _ _ = return Nothing 


convert :: MVar Value -> [String] -> IO (Maybe String)
convert rates list@(_ : _ : _ : _ : _) = do
    conversion <- readMVar rates
    getExchange conversion list
convert _ _ = return Nothing


markAsRead :: AcidState Database.KeyValue -> (Key, Bool) -> IO (Maybe Key)
markAsRead acid (updateId, True) = do
    update acid (InsertKey updateId)
    return $ Just updateId
markAsRead _ (_, False) = return Nothing


proceedMessage :: MVar Value -> Value -> Vector Integer -> IO (Integer, Bool)
proceedMessage rates updateOfMessage ids = do
    let Just updateId = updateOfMessage ^? key "update_id" . _Integer
    print $ "proceeding message with id " ++ show updateId
    if updateId `elem` ids
        then return (updateId, False)
        else do
            let Just message = updateOfMessage ^? key "message"
            let Just chatId = message ^? key "chat" . key "id" . _Integer
            let Just text = message ^? key "text" . _String
            let strings = words $ kostyl text
            answer <- convert rates strings
            response <- sendMessage chatId answer
            return (updateId, response)


telegram :: forall a. AcidState Database.KeyValue -> [Key] -> MVar Value -> Int -> IO (a, [Key])
telegram acid start rates delay = runStateT (forever go) start
    where go = do 
                updates <- lift getUpdates
                prev <- get
                let ids = Data.Vector.fromList prev
                proceededMessages <- lift $ Data.Vector.mapM (\x -> proceedMessage rates x ids) updates
                messagesMarkAsRead <- lift $ Data.Vector.mapM (markAsRead acid) proceededMessages
                let newProceededMessages = Data.Vector.map fromJust $ Data.Vector.filter isJust messagesMarkAsRead
                modify (const $ prev ++ toList newProceededMessages)
                lift (threadDelay delay)
            
