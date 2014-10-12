#!/usr/bin/perl
use strict;
use 5.010;

my $sdir = "./src";
my $idir = "./inc";
my $extra;
my $desuffix = '.m';
my $response;

# all *.m files include $extra u specificed.
my @modules;

&getall_modules();
&clean_extern();


sub getall_modules{
  my $base = shift @_;
  $base = '.' if $base == undef;

  opendir BASE_DIR, $base or
    die "Failed to open directory.\n   $!";

  foreach(readdir BASE_DIR){
    next if(/^\.\..*/);
    my $fname = $base . '/' . $_;
    if(/\w+\.m$/){
      unshift @modules, $fname;
    }
  }

  closedir(BASE_DIR);
}


sub list_to_scalar{
  my $result = shift @_;
  foreach(@_){
    $result .= (' ' . $_);
  }
  $result;
}


my @hfiles;
my @afiles;
# update these two list for each module
sub clean_extern{
  foreach(@modules){
    open MFILE, '<', $_ or
      die "Failed to open file [$_].  $!";

    while(<MFILE>){
      chomp;
      if(/#include\s/){
         unshift @hfiles, $idir . '/' . $1 if /\s+"(\w+\.h)"/;
         unshift @afiles, $idir . '/' . $1 if /\s+"(\w+\.h)"/;
         unshift @afiles, $sdir . '/' . $1 if /\s+"(\w+\.c)"/;
      }
    }
    close(MFILE);
    &search_symbol();
    @hfiles = ();
    @afiles = ();
  }
}


sub search_symbol{
  for my $fpname(@hfiles){
    open HEADFILE, '<', $fpname or
      die "Failed to open file [$fpname].  $!";

    say "\nOperating on $fpname...";

    my $raw;
    my $symbol;
    my $line = 0;
    while(<HEADFILE>){
      chomp;
      $line++;
      if(/extern\s+/){
        $raw = $_;
        unless(/;/){
          while(<HEADFILE>){
            $line++;
            chomp;
            next if /^\s*$/;
            $raw .= ' ' . $_;
            last if /;/;
          }
        }

        # Now full declarnation got
        $symbol = $1 if $raw =~ /(\w+)\(/;
        $symbol = $1 if $raw =~ /(\w+)\[/;
        $symbol = $1 if $raw =~ /(\w+)\s*;/;
        
        unless(&is_reference($symbol)){
          $symbol = &macro_referred($symbol);
          ($symbol and &is_reference($symbol)) or 
            say " ... Not Found:$line:$fpname.";
        }
      }
    } 

    close(HEADFILE);
  }
}


sub is_reference{
  my $symbol = shift @_;
  my $reference = undef;

  printf "%-30s", $symbol;

  SYMBOL:
  foreach my $n (0 .. $#afiles){
    my $fpname = $afiles[$n];
    open SOURCEFILE, '<', $fpname or
      die "Failed to open file [$fpname].  $!";

    my $commit = undef;
    
    while(<SOURCEFILE>){
      chomp;
      next if /\/\//;
      next if $commit eq "y";
      if(/\/\*/){
        $commit = "y";
        next unless /\*\//;
      }
      if(/\*\//){
        $commit = undef;
        next;
      }
      
      if(/$symbol/){
        $reference = 'refered';
        say " ... $reference.";
        last SYMBOL;
      }
    }
    close(SOURCEFILE);
  }
  
  $reference;
}


sub macro_referred{
  my $symbol = shift @_;
  my $marco = undef;
  my $macro_fname = './inc/defs.h';
  
  open MAC_FILE, '<', $macro_fname or
    die "Failed to open marco file.  $!";
   
  while(<MAC_FILE>){
    chomp;
    if(/$symbol/){
      my $raw = $_;
      if(/\\/){
        while(<MAC_FILE>){
          $raw .=  ' ' . $_;
          last unless /\\$/;
        }
      }
      # Whole marco got
      $marco = $1 if $raw =~ /#define\s+(\w+)/;
    }
  }

  close MAC_FILE;
  print "\n" if $marco;
  return $marco;
}
