name="MyStrategy"

if [ ! -f $name.cpp ]
then
    echo Unable to find $name.cpp > compilation.log
    exit 1
fi

rm -f $name

files=""

for i in *.cpp
do
    files="$files $i"
done

for i in model/*.cpp
do
    files="$files $i"
done

for i in csimplesocket/*.cpp
do
    files="$files $i"
done

g++ -std=c++11 -I/home/igorjan/206round/staff -static -fno-optimize-sibling-calls -fno-strict-aliasing -DONLINE_JUDGE -D_LINUX -lm -s -x c++ -O2 -Wall -Wno-unknown-pragmas -Ddebug=1 -Dvis=1 -o $name $files 2>compilation.log

cd runner
./local-runner.sh &
cd ..
sleep 5
./MyStrategy &
