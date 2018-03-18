task=$1
submit=[A-Za-z]+[$task].cpp

for i in *.cpp; do
    if [[ $i =~ $submit ]]; then
        echo $i
        clang++ -std=c++17 -O2 $i -o $i.exe
    fi
done

while [ 1 -ge 0 ]; do
    ./${task}generator > "$task.in"
    for i in *.cpp; do
        if [[ $i =~ $submit ]]; then
            ./$i.exe < $task.in > $i.output
            ./${task}check $task.in $i.output || cp $task.in $i.failed
        fi
    done
done
