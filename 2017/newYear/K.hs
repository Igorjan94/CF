import Text.Printf

main = do
    x <- getIntArray
    calc (fromIntegral (x !! 0)) (fromIntegral (x !! 1)) (fromIntegral (x !! 2))
    
calc a b h = printf "%.11f %.11f" (get1 a b h) (get2 a b h)
    
get1 :: Double -> Double -> Double -> Double
get1 a b h = 2 * b * sqrt(h * h + (a / 2) * (a / 2))

get2 :: Double -> Double -> Double -> Double
get2 a b h = a * sqrt(h * h + (b / 2) * (b / 2)) + b * sqrt(h * h + (a / 2) * (a / 2))

getIntArray :: IO [Int]
getIntArray = getLine >>= (return . fmap read . words)
