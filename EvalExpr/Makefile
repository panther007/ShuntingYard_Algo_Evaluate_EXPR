#Project Name
PRJ_NAME = EvalExpr

#Target Name of the prj
TARGET = EvalExpr

#Objects of project
OBJS = \
  EvalExpr.o

#Source files
SRC = \
  EvalExpr.hpp\
  EvalExpr.cpp

.PHONY: clean debug pack clang

CC = g++
CPPFLAGS = -g -Wall -std=c++11
LDFLAGS= 

%.o: %.cpp %.hpp
	$(CC) $(CPPFLAGS) $(LDFLAGS) -c $< -o $@

#build the prj
$(TARGET):  $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(OBJS) -o $@

#build the debug enabled object
debug: CPPFLAGS = -g -Wall -std=c++11 -DDEBUG
debug: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS_D) $(LDFLAGS) $< -o $(TARGET)

#build the using clang++
clang: CC = clang++
clang: $(OBJS)
	$(CC) $(CFLAGS) $(CPPFLAGS_D) $(LDFLAGS) $< -o $(TARGET)

#clean the objects
clean:
	rm -rf $(OBJS) $(TARGET) $(PRJ_NAME).tar.gz *~

#To pack the project files
pack: $(SRC)
	tar cvf - $(SRC) README Makefile | gzip > $(PRJ_NAME).tar.gz

