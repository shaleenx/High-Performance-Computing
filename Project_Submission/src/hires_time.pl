#!/usr/bin/perl -w

use Time::HiRes qw( usleep gettimeofday tv_interval );
$usrcmd="";
foreach (@ARGV) {
    $usrcmd=join " ",$usrcmd,$_;
}
chomp($usrcmd);
$usrcmd =~ s/^\s+//; #remove leading spaces
$usrcmd =~ s/\s+$//; #remove trailing spaces

#print "Executing: $usrcmd\n";
$t0 = [gettimeofday];
($seconds, $microseconds) = gettimeofday;

system($usrcmd);

$elapsed = tv_interval ( $t0, [$seconds, $microseconds]);
$elapsed = tv_interval ( $t0, [gettimeofday]);
$elapsed = tv_interval ( $t0 );

#print "Elapsed Time (in secs)=$elapsed\n";
print "$elapsed\n";
