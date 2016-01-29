{-# LANGUAGE DeriveGeneric #-}
{-# LANGUAGE OverloadedStrings #-}

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Control.Monad

import GHC.Generics

import Network.HTTP.Conduit (simpleHttp)

import Data.Text (Text)
import Data.Map
import Data.Vector (map)
import Data.List

import Control.Monad.Par
import Control.Concurrent.Async
import Control.Concurrent
import Control.Applicative

import Data.Maybe

data Conversion = Conversion { 
    base  :: !Text, 
    date  :: !Text, 
    rates :: Map String Double
} deriving (Show, Generic)

instance FromJSON Conversion
instance ToJSON   Conversion

-- Read the JSON data from the URL of a conversion, decoding it
getConversion :: String -> IO (Maybe Conversion)
getConversion base = fmap decode $ simpleHttp $ "http://api.fixer.io/latest?base=" ++ base

convert :: String -> IO (Maybe (Map String Double))
convert base = fmap rates <$> getConversion base

loop :: IO()
loop = forever $ do
    print "loop"
    let q = 500
    let from = "RUB"
    let to = "USD"
    mr <- convert from
    case mr of
        Nothing -> putStrLn "There was an error reading the JSON data."
        Just r  -> putStrLn $ show q ++ " " ++ from ++ " == " ++ show (q * (r ! to)) ++ " " ++ to
    threadDelay 2000000





{-getMessage :: String -> IO (Maybe Value)-}
getMessage token = simpleHttp $ "https://api.telegram.org/bot" ++ token ++ "/getUpdates"

sendMessage token chatId text = simpleHttp $ "https://api.telegram.org/bot" ++ token ++ "/sendMessage?chat_id=" ++ chatId ++ "&text=" ++ text

proceedMessage :: Value -> IO (Maybe Value)
proceedMessage message = do
    let token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"
    let Just name   = message ^? key "message" . key "from" . key "first_name" . _String
    let Just chatId = message ^? key "message" . key "chat" . key "id"         . _Integer
    let Just text   = message ^? key "message" . key "text" . _String
    {-putStrLn $ "message from " ++ (show name) ++ " in chat " ++ (show chatId) ++ " : " ++ (show text)-}
    answer <- sendMessage token (show chatId) (show text)
    x <- decode answer :: Maybe Value
    return x

messages = forever $ do
    print "messages"
    let token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"
    content <- getMessage token
    let mr = decode content :: Maybe Value
    case mr of
        Nothing -> error "There was an error reading the JSON data."
        Just messages -> Data.Vector.map proceedMessage (fromJust $ messages ^? key "result" . _Array)
            
    threadDelay 2000000

main :: IO()
main = do
    thread0 <- async messages
    thread1 <- async loop
    (,) <$> wait thread0 <*> wait thread1
    putStrLn "Finished"
