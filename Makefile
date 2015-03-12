CC=g++
CFLAGS=-g -Wall -std=c++11

SRCS=\
main.cpp\
Circle.cpp\
FastDetector.cpp

OBJS=$(SRCS:.cpp=.o)
DEPS=$(SRCS:.cpp=.d)

INCS=-I. `pkg-config --cflags opencv`
LIBS=`pkg-config --libs opencv`

RM=rm -rf

fastdetector: $(OBJS)
	$(CC) $(OBJS) -o $@ $(CFLAGS) $(INCS) $(LIBS)

%.o: %.cpp
	$(CC) $< -o $@ $(CFLAGS) -c $(INCS) -MP -MMD

clean:
	$(RM) fastdetector $(OBJS) $(DEPS)

-include $(DEPS)
