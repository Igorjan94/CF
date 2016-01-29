import Telegram
import Exchange

main :: IO()
main = do
    thread0 <- async messages
    thread1 <- async loop
    (,) <$> wait thread0 <*> wait thread1
    putStrLn "Finished"
