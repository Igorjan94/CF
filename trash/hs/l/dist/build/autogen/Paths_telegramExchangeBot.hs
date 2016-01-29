module Paths_telegramExchangeBot (
    version,
    getBinDir, getLibDir, getDataDir, getLibexecDir,
    getDataFileName, getSysconfDir
  ) where

import qualified Control.Exception as Exception
import Data.Version (Version(..))
import System.Environment (getEnv)
import Prelude

catchIO :: IO a -> (Exception.IOException -> IO a) -> IO a
catchIO = Exception.catch

version :: Version
version = Version [0,1,0,0] []
bindir, libdir, datadir, libexecdir, sysconfdir :: FilePath

bindir     = "/home/igorjan/.cabal/bin"
libdir     = "/home/igorjan/.cabal/lib/x86_64-linux-ghc-7.10.2/telegramExchangeBot-0.1.0.0-E2JpoJK2GRH3qMzrEoGfnM"
datadir    = "/home/igorjan/.cabal/share/x86_64-linux-ghc-7.10.2/telegramExchangeBot-0.1.0.0"
libexecdir = "/home/igorjan/.cabal/libexec"
sysconfdir = "/home/igorjan/.cabal/etc"

getBinDir, getLibDir, getDataDir, getLibexecDir, getSysconfDir :: IO FilePath
getBinDir = catchIO (getEnv "telegramExchangeBot_bindir") (\_ -> return bindir)
getLibDir = catchIO (getEnv "telegramExchangeBot_libdir") (\_ -> return libdir)
getDataDir = catchIO (getEnv "telegramExchangeBot_datadir") (\_ -> return datadir)
getLibexecDir = catchIO (getEnv "telegramExchangeBot_libexecdir") (\_ -> return libexecdir)
getSysconfDir = catchIO (getEnv "telegramExchangeBot_sysconfdir") (\_ -> return sysconfdir)

getDataFileName :: FilePath -> IO FilePath
getDataFileName name = do
  dir <- getDataDir
  return (dir ++ "/" ++ name)
