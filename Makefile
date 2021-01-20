OBJS    = KosaRaju.o
SOURCE  = KosaRaju.cpp
HEADER  =
OUT     = Kosaraju
CC       = g++
FLAGS    = -g -c -Wall
LFLAGS   =

all: $(OBJS)
        $(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

KosaRaju.o: KosaRaju.cpp
        $(CC) $(FLAGS) KosaRaju.cpp


clean:
        rm -f $(OBJS) $(OUT)
