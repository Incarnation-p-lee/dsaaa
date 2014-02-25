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
RDIR          =report
IDIR          =inc
SDIR          =src
MFLAG         =-x c
CFLAG         =$(MFLAG) -c -g -O3 -Wall -pg $(COVERAGE)
LFLAG         =-pg $(COVERAGE)
EXRLIB        =-lm
ALLDIR        =$(OBJDIR) $(ADIR) $(IDIR) $(SDIR) $(RDIR)


vpath %.o $(OBJDIR)

.phony:link clean run

$(TARGET):$(OBJ)
	$(MAKE) link

-include $(FDPS)
$(FDPS):$(SRC)
	$(CC) $(INC) $(MFLAG) -MM $^ >$@


ifneq ($(ALLDIR), $(wildcard $(ALLDIR)))
	mkdir -vp $(filter-out $(wildcard $(ALLDIR)), $(ALLDIR))
endif


$(OBJ):%.o:%.m
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) $(LFLAG) -o $(TARGET) $^ $(EXRLIB)

run:$(TARGET)
	./$(TARGET)
	$(SHELL) genCoverage.sh

clean:
	$(cleanall)

define cleanall
	-rm -rf $(TARGET) $(OBJDIR)/* $(FDPS)
	-rm -rf $(RDIR)/* *.gcda *.gcno
	-rm -rf $(ADIR)/*
endef
