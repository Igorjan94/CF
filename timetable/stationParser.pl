#!/usr/bin/env perl
while(<>)
{
    s/^.*?\[\{//g;
    s/\}\].*//g;
    s/\"stid\"\:\"//g;
    s/\-spb.*?\"\,\"stnm\":\".*?\"\,\"stnm_short\"\:\"/ /g;
    s/\",\"selected\"\:false//g;
    s/\}\,\s*\{/\n/g;
    print;
}
