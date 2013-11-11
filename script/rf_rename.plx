#!/usr/bin/perl
use 5.010;
use strict;

my $base_dir = ".";
my @all_files;
my @lines;
my $raw_word;
my $dst_word;

&option_check();
&get_all_files($base_dir);
#&read_source_file($testfile);
#&write_source_file($testfile);

sub get_all_files{
  my $dir = shift @_;
  say "=>Progressing directory " . "[$dir]" . ".";
  opendir START_DIR, $dir or
    die "Failed to open directory.\n  $!";

  foreach(readdir START_DIR){
    next if(/^\.\.?|\.git/);
    my $fullname = $dir . "/" . $_;
    if(-d $fullname){
		  &get_all_files($fullname);
		}else{
			if(/\w\.[c|h]m?$/a){
        say "Operating on $_";
        &read_source_file($fullname);
        &write_source_file($fullname);
        @lines = undef;
			}
		}
	}
  closedir(START_DIR);
}

sub write_source_file{
  my $filename = shift @_;

  open OUPUT_FILE, '>', $filename or
    die "Failed to open source file: [$filename].\n  $!";
  
  foreach(@lines){
    print OUPUT_FILE $_;
  }

  close(OUPUT_FILE);
}

sub read_source_file{
  my $filename = shift @_;

  open SOURCE_FILE, '<', $filename or
    die "Failed to open source file: [$filename].\n  $!";
  
  while(<SOURCE_FILE>){
    s/$raw_word/$dst_word/g;
    push @lines, $_;
  }

  close(SOURCE_FILE);
}


sub option_check{
  $raw_word = shift @ARGV;
  $dst_word = shift @ARGV;

  if(($raw_word eq "") && ($dst_word eq "")){
    die "\nusage perl refactor_rename.plx dest source.\n";
  }

  say "Refactorring->Rename: [$raw_word] => [$dst_word].";
}
