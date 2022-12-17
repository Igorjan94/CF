$_=<>;
while (<>) {
    while (/[aeioyu]{2}/) {
        s/([aeioyu])[aeioyu]/$1/;
    };
    print;
}
