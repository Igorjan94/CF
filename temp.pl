#!/usr/bin/env perl
while(<>)
{
    s/ \(.*?\)\t/\t/g;
    print;
}
