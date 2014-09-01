if [ $# -eq 1 ]
then a=$1
fi

if [ $# -eq 0 ]
then a="echo"
fi
find . -executable -type f ! -wholename './perl/*' ! -wholename './*pl' ! -wholename '*git*' ! -wholename './*.py' ! -wholename './*perl' ! -wholename './cleaner' ! -wholename './*.java' ! -wholename './*.sh' ! -wholename '*TDGame*' | xargs $a
find . -wholename './*.o' | xargs $a
find . -wholename './*.class' | xargs $a
