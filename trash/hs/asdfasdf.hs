{-# LANGUAGE DeriveGeneric #-}
{-# LANGUAGE OverloadedStrings #-}
import Control.Monad
import Control.Monad.State.Strict
main = runStateT (forever go) []
  where go = do line <- lift getLine
                modify (\x -> line)
                state <- get
                lift (print state)
