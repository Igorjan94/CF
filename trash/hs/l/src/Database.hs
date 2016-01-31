{-# LANGUAGE DeriveDataTypeable #-}
{-# LANGUAGE TemplateHaskell    #-}
{-# LANGUAGE TypeFamilies       #-}
module Database where

import Data.Acid
import Control.Monad.Reader
import Control.Monad.State
import Data.SafeCopy
import Data.Typeable
import qualified Data.Set as Set

type Key = Integer

data KeyValue = KeyValue !(Set.Set Key) deriving (Typeable)

insertKey :: Key -> Update KeyValue ()
insertKey key = do 
    KeyValue m <- get
    put (KeyValue (Set.insert key m))

allKeys :: Query KeyValue [Key]
allKeys = do 
    KeyValue m <- ask
    return $ Set.toList m

$(deriveSafeCopy 0 'base ''KeyValue)
$(makeAcidic ''KeyValue ['insertKey, 'allKeys])
