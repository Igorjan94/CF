import Data.List
import Control.Monad (replicateM)
import System.IO

getInts :: String -> [Int]
getInts = map read . words

f [] = ""
f (x:y) = show x ++ " " ++ f y

g x = reverse $ sort $ zip (getInts x) [1 ..] 
h x = reverse $ foldl (\ (x:xs) (a, _) -> ((toInteger a + x):x:xs)) [0] x

readInt :: String -> Int
readInt = read

readLines n f = withFile f ReadMode $ replicateM n . hGetLine

main = do
    (x:y:z:_) <- readLines 3 "buffcraft.in"
    let [boom, k, _, cp] = getInts x
    let d = g y
    let p = g z
    let a = take (k + 1) $ h d 
    let b = take (k + 1) $ h p
    let r = take (k + 1) $ reverse $ b ++ (take (k - cp) $ repeat $ last b)
    let c = maximum $ zipWith3 (\ a b i -> ((toInteger boom + a) * (toInteger 100 + b), i)) a r [0..]
    let i = snd c
    let j = min (k - (snd c)) cp
    writeFile "buffcraft.out" $ show i ++ " " ++ show j ++ "\r" ++ (f $ take i (snd $ unzip d)) ++ "\r" ++ (f $ take j (snd $ unzip p)) ++ "\r"
