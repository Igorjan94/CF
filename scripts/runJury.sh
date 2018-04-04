exe=$1

for i in $(seq 1 1000)
do
    if [ ! -f "./$i" ]; then break; fi
    $exe < $i > $i.a
    echo $i
done
