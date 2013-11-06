#!/bin/sh
binarydir="./"
reportdir="./report"
outputdir="/output"
rawdatafile="coverage.info"
basedir="./"
binary="dsaaa.out"
reportname="report.tar.gz"

if [ ! -x "$reportdir" ];then
  mkdir "$reportdir"
fi

if [ -f "*.gcda" ];then
  mv *.gcda "$reportdir"
fi
if [ -f "*.gcno" ];then
  mv *.gcno "$reportdir"
fi

lcov --capture --directory "$reportdir" --base-directory "$basedir" --output-file "$rawdatafile" --test-name "$binary"

if [ -x "$reportdir$ouputdir" ];then
  rm -rf "$reportdir$outputdir"
fi

genhtml --output-directory "$reportdir$outputdir" --title "DSAAA" --show-details --legend "$rawdatafile"
tar -zcvf "$reportname" "$reportdir$outputdir"
