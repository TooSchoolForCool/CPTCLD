#
# 'make depend' uses makedepend to automatically generate dependencies 
#               (dependencies are added to end of Makefile)
# 'make'        build executable file $(TARGET)
# 'make clean'  removes all .o and executable files
# 'make run'	build executalbe file $(TARGET) and run it ./$(TARGET)
#

# define MAKE
MAKE = make

# define the C compiler to use
CC = g++

# define thr remove command
RM = rm

# define object files directory
OBJS_DIR = obj

# define dependent object files directory
DEPEND_OBJS_DIR = src/obj

# define any compile-time flags
CFLAGS = -Wall -g -std=c++11

# define any directories containing header files other than /usr/include
# eg: INCLUDES = -I/home/newhall/include  -I../include
# 
INCLUDES = -I./include

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
#	eg: LFLAGS = -L/home/newhall/lib  -L../lib
# 
LFLAGS = 

# define any libraries to link into executable:
#   if I want to link in libraries (libx.so or libx.a) I use the -llibname 
#   option, something like (this will link in libmylib.so and libm.so:
#	eg: LIBS = -lmylib -lm
#
LIBS =

# define the C source files
SRCS = main.cpp \

# define the C object files 
#
# This uses Suffix Replacement within a macro:
#   $(name:string1=string2)
#         For each word in 'name' replace 'string1' with 'string2'
# Below we are replacing the suffix .c of all words in the macro SRCS
# with the .o suffix
#
OBJS = $(SRCS:%.cpp=$(OBJS_DIR)/%.o)

# define dependent object files
DEPEND_OBJS = $(DEPEND_OBJS_DIR)/scheduler.o \
			  $(DEPEND_OBJS_DIR)/scheduler_null.o \
			  $(DEPEND_OBJS_DIR)/tester.o

# define the executable file 
TARGET = launch

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean run

all: $(TARGET)
	@echo $(TARGET) has been succesfully compiled

$(TARGET): $(OBJS)
	$(MAKE) -C src
	@$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(DEPEND_OBJS) $(LFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#
$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

run: $(TARGET)
	./$(TARGET)

clean:
	$(RM) -f $(OBJS_DIR)/*.o $(TARGET)
	$(RM) -r $(OBJS_DIR)
	$(MAKE) -C src clean

depend: $(SRCS)
	makedepend $(INCLUDES) $^
	$(MAKE) -C src depend

# DO NOT DELETE THIS LINE -- make depend needs it
main.o: ./include/tester.h ./include/allocation.h ./include/pattern.h
main.o: ./include/request.h ./include/scheduler.h ./include/scheduler_null.h
