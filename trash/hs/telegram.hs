{-# LANGUAGE OverloadedStrings #-}

module Telegram where

import Data.Aeson
import Data.Aeson.Lens
import Control.Lens

import Control.Monad

import GHC.Generics

import Data.Text (Text)
import Data.Map
import Data.Vector (map)
import Data.List

import Control.Monad.Par
import Control.Concurrent.Async
import Control.Concurrent
import Control.Applicative

import Data.Maybe

import Network

main :: IO()
main = forever $ do
    x <- jsonByURL $ "https://api.telegram.org/bot" ++ token ++ "/getUpdates"
    print x
    threadDelay 2000000
