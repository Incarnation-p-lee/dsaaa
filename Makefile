# This is the Makefile for GCC compiler. Only you need to update outest.
.SUFFIXES:
.SUFFIXES: .o .a .so .c .h .s .cm
SRC_RAW       :=main.m chapter_1.m evaluation.m utilize.m \
               chapter_2.m chapter_3.m data_structure.m


SRC           :=$(sort $(SRC_RAW))
SHELL         =/bin/bash
CC            =gcc
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
CFLAG         =$(MFLAG) -c -g -Wall -pg $(COVERAGE)
LFLAG         =-pg $(COVERAGE)
EXRLIB        =-lm
ALLDIR        =$(OBJDIR) $(ADIR) $(IDIR) $(SDIR) $(RDIR)


vpath %.o $(OBJDIR)

.phony:link clean run show

$(TARGET):$(OBJ)
	$(MAKE) link


ifeq "$(MAKECMDGOALS)"  ""
-include $(FDPS)
$(FDPS):$(SRC)
	$(CC) $(INC) $(MFLAG) -MM $^ >$@
endif


ifneq ($(ALLDIR), $(wildcard $(ALLDIR)))
	@echo "Directory dependency:[" $(ALLDIR) "]"
	mkdir -vp $(filter-out $(wildcard $(ALLDIR)), $(ALLDIR))
endif


$(OBJ):%.o:%.m
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) $(LFLAG) -o $(TARGET) $^ $(EXRLIB)
	@echo $(shell date)
	rm $(FDPS)

run:$(TARGET)
	./$(TARGET)
	$(SHELL) genCoverage.sh

clean:
	$(cleanall)

show:
	$(call symbol, $(OBJDIR)/main.o)
	$(call dylink, $(TARGET))

define cleanall
	-rm -rf $(TARGET) $(OBJDIR)/*
	-rm -rf $(RDIR)/* *.gcda *.gcno
	-rm -rf $(ADIR)/*
endef

define symbol
	nm -alp $1
endef

define dylink
	ldd $1
endef
