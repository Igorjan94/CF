<>;
while (<>) {
    if (/^e$|^(e?s)?(Yes)*(Ye?)?$/) {
        print "YES\n";
    } else {
        print "NO\n";
    }
}
