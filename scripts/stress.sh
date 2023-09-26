shopt -s nullglob
dir='.'

if [[ ! -z "$1" ]]; then
    dir=$1
fi
task="$dir/A"
correct=$2
generator=$3
checker=$4
if [[ -z "$correct" ]]; then
    correct=$task
fi
if [[ -z "$generator" ]]; then
    generator="$dir/generator"
fi
if [[ -z "$checker" ]]; then
    checker="$dir/checker"
fi

for i in $dir/*.cpp; do
    if [[ $i =~ "*" ]]; then
        break
    fi
    echo $i
    clang++ -std=c++17 -DONLINE_JUDGE -include /home/igorjan/206round/bits.h -O2 $i -o $i.exe
done

stop="false"
while [[ "false" = "$stop" ]]; do
    $generator 2>/dev/null > "$task.in"
    $correct 2>/dev/null < "$task.in" > "$task.a"
    for i in $dir/*.cpp.exe; do
        $i 2>/dev/null < $task.in > $i.output
        $checker $task.in $i.output $task.a 2>/dev/null || (cp $task.in $i.failed && rm -rf $i && echo "failed $i")
    done
done
