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

# define dependent source files directory
DEPEND_SRCS_DIR = src

# define any compile-time flags
CFLAGS = -Wall -std=c++11

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
SRCS = $(wildcard *.cpp)

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
DEPEND_SRCS := $(wildcard $(DEPEND_SRCS_DIR)/*.cpp)

# define dependent object files
DEPEND_OBJS = $(DEPEND_SRCS:src/%.cpp=$(DEPEND_OBJS_DIR)/%.o)

# define the executable file 
TARGET = launch

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#

.PHONY: depend clean run

all: $(TARGET)
	
$(TARGET): $(OBJS) $(DEPEND_SRCS)
	$(MAKE) -C $(DEPEND_SRCS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(TARGET) $(OBJS) $(DEPEND_OBJS) $(LFLAGS) $(LIBS)
	@echo [INFO]: $(TARGET) has been succesfully compiled

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
#
$(OBJS_DIR)/%.o: %.cpp
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

runn: $(TARGET)
	./$(TARGET) < normal-user.txt > normal-user-charge.txt
	@cat normal-user-charge.txt
	@python3 plot.py < normal-user-charge.txt

rund: $(TARGET)
	./$(TARGET) < dump-cheater.txt > dump-cheater-charge.txt
	cat dump-cheater-charge.txt
	@python3 plot.py < dump-cheater-charge.txt

runs: $(TARGET)
	./$(TARGET) < smart-cheater.txt > smart-cheater-charge.txt
	cat smart-cheater-charge.txt
	python3 plot.py < smart-cheater-charge.txt

clean:
	$(RM) -f $(OBJS_DIR)/*.o $(TARGET)
	$(RM) -r $(OBJS_DIR)
	$(MAKE) -C src clean

depend: $(SRCS)
	makedepend $(INCLUDES) $^
	$(MAKE) -C src depend

# DO NOT DELETE THIS LINE -- make depend needs it

main.o: ./include/eNodeB.h ./include/request.h ./include/normalUser.h
main.o: ./include/userAgent.h
