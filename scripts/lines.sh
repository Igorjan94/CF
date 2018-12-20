mask='*.lua'
a=0
for i in $mask; do
    b=$(cat "$i" | nl | tail -1 | awk '{print $1;}')
    echo $a $b $i
    a=$(python -c "print ($a + $b)")
done
echo $a
