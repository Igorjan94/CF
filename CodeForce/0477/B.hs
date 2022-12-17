import Text.Printf

readItns :: String -> [Int]
readItns = map read . words

solve :: Int -> Int -> IO()
solve 0 k = printf "%d %d %d %d\n" (k) (2 * k) (3 * k) (5 * k)
solve n k = do
    printf "%d %d %d %d\n" ((6 * n + 1) * k) ((6 * n + 2) * k) ((6 * n + 3) * k) ((6 * n + 5) * k)
    solve (n - 1) k

main :: IO()
main = do
    n <- getLine
    let [a, b] = readItns n
    printf "%d\n" $ (6 * (a - 1) + 5) * b
    solve (a - 1) b
