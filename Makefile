# This is the Makefile for GCC compiler. Only you need to update outest.
.SUFFIXES:
.SUFFIXES: .o .a .so .c .h .s .cm
SHELL         =/bin/bash
CC            =gcc

SRC           =main.m chapter_1.m evaluation.m utilize.m \
               chapter_2.m chapter_3.m

COVERAGE      =-fprofile-arcs -ftest-coverage
OBJ           =$(patsubst %.m, %.o, $(SRC))
INCH          =./inc
INCS          =./src
INC           =-I$(INCH) -I$(INCS)
TARGET        =dsaaa.out
FDPS          =fdependent
OBJDIR        =obj
ADIR          =archive
IDIR          =inc
SDIR          =src
MFLAG         =-x c
CFLAG         =$(MFLAG) -c -g -Wall -pg $(COVERAGE)
LFLAG         =-pg $(COVERAGE)
EXRLIB        =-lm

vpath %.o $(OBJDIR)

.phony:link clean run

$(TARGET):$(OBJ)
	$(MAKE) link

-include $(FDPS)
$(FDPS):$(SRC)
	$(CC) $(INC) $(MFLAG) -MM $^ >$@

ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir $(OBJDIR)
endif

ifneq ($(ADIR), $(wildcard $(ADIR)))
	mkdir $(ADIR)
endif

ifneq ($(IDIR), $(wildcard $(IDIR)))
	mkdir $(IDIR)
endif

ifneq ($(SDIR), $(wildcard $(SDIR)))
	mkdir $(SDIR)
endif

$(OBJ):%.o:%.m
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) $(LFLAG) -o $(TARGET) $^ $(EXRLIB)

run:$(TARGET)
	./$(TARGET)
	sh genCoverage.sh

clean:
	-rm -rf $(TARGET) $(OBJDIR)/* $(FDPS)
	-rm -rf report *.gcda *.gcno
	-rm -rf $(ADIR)/*
