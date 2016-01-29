{-# LANGUAGE OverloadedStrings #-}

import Data.Aeson             ((.:), (.:?), decode, FromJSON(..), Value(..))
import Control.Applicative    ((<$>), (<*>))
import Data.Time.Format       (parseTime)
import Data.Time.Clock        (UTCTime)
import System.Locale          (defaultTimeLocale)
import Control.Monad          (liftM)
import qualified Data.HashMap.Strict as HM
import qualified Data.ByteString.Lazy.Char8 as BS
import Network.HTTP.Conduit (simpleHttp)
import Control.Monad.IO.Class  (liftIO)

getRHLines :: IO BS.ByteString -> Value
getRHLines json =
  case HM.lookup "lines" hm of
    Just n -> n
    Nothing -> error "Y U NO HAS NUMBER?"
  where (Just (Object hm)) = decode json :: Maybe Value

token = "130250270:AAFeKP-ZbsdRxc4g5QtkbFYmrF5POgOaurw"


main :: IO()
main = print $ getRHLines $ liftIO $ simpleHttp $ "https://api.telegram.org/bot" ++ token ++ "/getUpdates"
{-"{ \"contents\": \"(begin)\", \"date\": \"2012-01-04T01:44:22.964Z\", \"fork\": null, \"language\": \"Clojure\", \"lines\": 1, \"paste-id\": \"1\", \"private\": false, \"random-id\": \"f1fc1181fb294950ca4df7008\", \"url\": \"https://www.refheap.com/paste/1\", \"user\": \"raynes\" }"-}
