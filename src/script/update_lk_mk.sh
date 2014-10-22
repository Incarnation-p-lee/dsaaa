#!/bin/sh

objdir=obj_out
mkfile=$objdir/Makefile
srcdir=src
objfile=`ls $objdir/*.o`
echo $objfile
echo \
"include ../$srcdir/base.Makefile

\$(TARGET):$objfile
	\$(CC) \$(LFLAG) -o \$@ \$^ \$(EXRLIB)" > $mkfile

