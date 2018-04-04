exe=$1
checker=$2

for i in $(seq 1 1000)
do
    if [ ! -f "./$i" ]; then break; fi
    $exe < $i > $i.out
    $checker $i $i.out $i.a
    ec=$?
    rm -rf $i.out
    if [ $ec -eq 1 ]; then break; fi
done
