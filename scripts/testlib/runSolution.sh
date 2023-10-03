exe=$1
checker=$2
dir=$3

if [ ! "$dir" ]; then
    dir="."
fi

for i in $(seq 1 1000)
do
    cur=$dir/$i
    if [ ! -f "$cur" ]; then 
        if [ ! -f "$dir/0$i" ]; then 
            if [ ! -f "$dir/00$i" ]; then 
                break;
            fi
            cur="$dir/00$i"
        else
            cur="$dir/0$i"
        fi
    fi
    echo "Test $cur"
    $exe < $cur > $cur.out
    $checker $cur $cur.out $cur.a
    ec=$?
    rm -rf $cur.out
    #if [ $ec -eq 1 ]; then break; fi
done
