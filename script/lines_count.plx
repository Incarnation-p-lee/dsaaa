#!/usr/bin/perl
use 5.010;
use strict;

my $total;
my $header_num;
my $source_num;
my $inc_path = "./inc/";
my $src_path = "./src/";

say "\n      Source Files Directories Line Numbers      \n";

$header_num = &get_lines($inc_path);
$source_num = &get_lines($src_path);
$total = $header_num + $source_num;
printf "header : %6d\n", $header_num;
printf "source : %6d\n", $source_num;
printf "total  : %6d\n", $total;

sub get_lines{
  my $dir = shift @_;
  chomp $dir;
  opendir INC_DIR, $dir or
    die "Faild to open include directory.\n $!";

  $total = 0;
  foreach(readdir INC_DIR){
    next if (/^\.\.?\w*/);
    my $fname = $dir . $_;
    $total += &get_file_lines($fname);
  }
  $total;
}

sub get_file_lines{
  my $fname = shift @_;
  chomp $fname;
  open SOURCEFILE, '<', $fname or
    die "Failed to open source file.\n $!"; 
  my $num = 0;
  $num++ while(<SOURCEFILE>);
  printf "++ %20s: %6d.\n", $fname, $num;
  $num;
}


