$t = <STDIN>;

for ($test = 0; $test < $t; $test++) {
	$line = <STDIN>;
	@s = split(/:| /, $line);
    $t1 = $s[0] * 60 * 60 + $s[1] * 60 + $s[2];
	$t2 = $s[3] * 60 * 60 + $s[4] * 60 + $s[5];

	if ($t1 >= $t2) {
		$t2 += 24 * 60 * 60;
	}
    $t1 += $s[6] * 60;
    if ($t1 <= $t2) {
		print "Perfect\n";
	} else {
		if ($t1 <= $t2 + 60 * 60) {
			print "Test\n";
		} else { 
			print "Fail\n";
		}
	}
}


