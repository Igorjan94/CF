<?php
$line = trim(fgets(STDIN));
$a = 0;
$a = $a + preg_match('/.{5,}/', $line, $matches, PREG_OFFSET_CAPTURE);
$a = $a + preg_match('/[a-z]/', $line, $matches, PREG_OFFSET_CAPTURE);
$a = $a + preg_match('/[A-Z]/', $line, $matches, PREG_OFFSET_CAPTURE);
$a = $a + preg_match('/[0-9]/', $line, $matches, PREG_OFFSET_CAPTURE);
if ($a == 4)
    print 'Correct';
else
    print 'Too weak';
?>
