#!/bin/sh

debug=0
code_coverage=0

for argv in "$@"
do
  echo $argv
  case $argv in
    "DEBUG=1")
    debug=1
    echo "A"
    ;;
    "DEBUG=0")
    debug=0
    echo "B"
    ;;
    "CODE_COVERAGE=1")
    code_coverage=1
    echo "C"
    ;;
    "CODE_COVERAGE=0")
    code_coverage=0
    echo "D"
    ;;
  esac
done

objdir=obj_out

if [ -d $objdir ]
then
  rm -rfv $objdir
fi

mkdir -vp $objdir
mkdir -vp $objdir/out/

function compile_obj() {
  cd $1 > /dev/null
  make
  cd - > /dev/null
  mv -v $1*.o $objdir
}

# compiling .o files for all subdir
for dir in `ls -d src/*/`
do
  case $dir in
    "src/script/")
    continue
  ;;
    "src/inc/")
    continue
  ;;
  esac

  compile_obj $dir
done

# compiling main.o
compile_obj "src/"

# generate makefile for obj_out
sh src/script/update_lk_mk.sh
# link to elf
cd $objdir > /dev/null
make
cd - > /dev/null
