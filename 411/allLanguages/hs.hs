import Data.Char
check s = if length s >= 5 then ((not . null) $ filter (isUpper) s) && ((not . null) $ filter (isLower) s) && ((not . null) $ filter (isDigit) s) else False
main:: IO ()
main = do
    line <- getLine
    if check(line) then
        putStrLn "Correct" else 
        putStrLn "Too weak"
