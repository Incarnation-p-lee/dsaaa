#!/usr/bin/perl
use strict;
use 5.010;


my $basedir = '.';
my $sdir = './src';
# format: k->v, module name -> included files
my %module_files;

# Work Flow
# build_md_map [build module_files hash table]
# |


&build_md_map($basedir);                     # build hash map %module_files
&update_declare();                           # update all modules

sub build_md_map{
  my $base = shift @_;
  opendir BASE_DIR, $base or 
    die "Failed to open directory [$base].  $!";
  
  foreach(readdir BASE_DIR){
    if(/\w+\.m\b/){
      my $mname = $_;
      open MD_FILE, '<', $mname, or 
        die "Failed to open file [$mname].  $!";

      my $files;
      while(<MD_FILE>){
        chomp;
        if(/#include/){
          if(/"(\w+\.[c|h])"/){
            $files .= ' ' . $1;
          }
        }
      }

      $module_files{$mname} = $files;
      close(MD_FILE);
    }
  }

  closedir(BASE_DIR);
}


sub update_declare{
  my @mod = keys %module_files;
  foreach(@mod){
    &process_module($module_files{$_});
  }
}


sub process_module{
  my $fn = shift @_;
  my @files = split / /, $fn;
  my @head;
  my @source;
  foreach(@files){
    unshift @head, $_ if m/\w+\.h/;
    unshift @source, $_ if m/\w+\.c/;
  }

  my @defines;
  foreach(@source){
    my $fullname = $sdir . '/' . $_;
    open SFILE, '<', $fullname or 
      die "Failed to open file [$fullname].  $!";
  
    while(<SFILE>){
      next if m://:;
      next if m:/\*:;
      next if m:\*/:;
      next if m/[;|{|}]/;
      next if m/^\s+$/;
      my $single;
      while(<SFILE>){
        $single .= $_;
        last if m/\)\s*$/;
        if(/;/){
          $single = undef;
          last;
        }
      }
      say "$single" if $single;
    }

    close(SFILE);
  }
}
