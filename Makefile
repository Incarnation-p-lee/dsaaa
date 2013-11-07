# This is the Makefile for GCC compiler. Only you need to update outest.
.SUFFIXES:
.SUFFIXES: .o .a .so .c .h .s
SHELL         =/bin/sh
CC            =gcc
SRC           =main.c chapter_1.c evaluation.c utilize.c

OBJ           =$(patsubst %.c, %.o, $(SRC))
INCH          =./inc
INCS          =./src
INC           =-I$(INCH) -I$(INCS)
TARGET        =dsaaa.out
FDPS          =fdependent
OBJDIR        =obj
CFLAG         =-c -ggdb -Wall -Werror
EXRLIB        =-lm

vpath %.o $(OBJDIR)

.phony:link clean

$(TARGET):$(OBJ)
	$(MAKE) link

-include $(FDPS)

$(FDPS):$(SRC)
	$(CC) $(INC) -MM $^ >$@

ifneq ($(OBJDIR), $(wildcard $(OBJDIR)))
	mkdir $(OBJDIR)
endif


$(OBJ):%.o:%.c
	$(CC) $(INC) $(CFLAG) -o $@ $<
	mv $@ $(OBJDIR)

link:$(OBJ)
	$(CC) $(INC) -o $(TARGET) $^ $(EXRLIB)


clean:
	-rm -rf $(TARGET) $(OBJDIR)/* $(FDPS)
