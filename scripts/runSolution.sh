exe=$1
checker=$2
dir=$3

if [ ! "$dir" ]; then
    dir="."
fi

for i in $(seq 1 1000)
do
    if [ ! -f "$dir/$i" ]; then break; fi
    $exe < $dir/$i > $dir/$i.out
    $checker $dir/$i $dir/$i.out $dir/$i.a
    ec=$?
    rm -rf $dir/$i.out
    if [ $ec -eq 1 ]; then break; fi
done
