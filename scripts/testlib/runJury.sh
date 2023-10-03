exe=$1
dir=$2

if [ ! "$dir" ]; then
    dir="."
fi


for i in $(seq 1 1000)
do
    if [ ! -f "$dir/$i" ]; then break; fi
    $exe < $dir/$i > $dir/$i.a
    echo $i
done
