for i in {1..100}
do
    ./F < input > output &
    ./interactor > input < output
done
