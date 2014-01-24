#!/usr/bin/perl
use 5.010;
use strict;

my $base_dir = ".";
my $keyword;

&option_check();
&get_all_reference($base_dir);
#&single_file_reference($testfile);
#&write_source_file($testfile);

sub get_all_reference{
  my $dir = shift @_;
  opendir START_DIR, $dir or
    die "Failed to open directory.\n  $!";

  foreach(readdir START_DIR){
    next if(/^\.\.?|\.git/);
    my $fullname = $dir . "/" . $_;
    if(-d $fullname){
      &get_all_reference($fullname);
    }else{
        if(/\w\.[c|h|m]$/a){
        &single_file_reference($fullname);
      }
    }
  }
  closedir(START_DIR);
}

sub single_file_reference{
  my $line = 0;
  my $filename = shift @_;
  my $print_once = undef;

  open SOURCE_FILE, '<', $filename or
    die "Failed to open source file: [$filename].\n  $!";

  
  while(<SOURCE_FILE>){
    $line++;
    if(/([^\w]|^)$keyword([^\w])/){
      if(!$print_once){
        say "at file:[$filename]";
        $print_once = "done";
      }
      printf "%4d+ %s", $line, $_;
    }
  }

  close(SOURCE_FILE);
}

sub option_check{
  $keyword = shift @ARGV;

  if($keyword eq ""){
    die "\nusage \"perl rf_rename.plx [keyword].\"\n\n";
  }

  say "Find All Reference: [$keyword].";
}

1;
