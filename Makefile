CC=g++
CFLAGS=-g -c -Wall
AFLAGS=-g
INCLUDES=-I /home/ernstv/build/opencv/release/include -I/usr/local/include/opencv4
LIBS=-lstdc++ -lopencv_imgcodecs -lopencv_highgui -lopencv_core -lopencv_imgproc -lpthread
ARTIFACTS=*.o lcai *.dSym
WORKFORCE=src/workforce
WORKFORCE_SOURCES=$(WORKFORCE)/IWorker.cpp $(WORKFORCE)/SimpleWorker.cpp $(WORKFORCE)/WorkQueue.cpp $(WORKFORCE)/WorkerPool.cpp $(WORKFORCE)/WaitForCompletionFuture.cpp

default: all

all: workforce aspects main
	$(CC) $(AFLAGS) *.o -o lcai $(INCLUDES) $(LIBS)

main: workforce aspects Test0001.cpp
	$(CC) $(CFLAGS) Test0001.cpp $(INCLUDES) $(LIBS)

workforce: $(WORKFORCE_SOURCES)
	$(CC) $(CFLAGS) $(WORKFORCE_SOURCES) $(INCLUDES) $(LIBS)

aspects: Messages.cpp Images.cpp
	$(CC) $(CFLAGS) Messages.cpp Images.cpp $(INCLUDES) $(LIBS)
	
clean:
	rm -f $(ARTIFACTS)
	rm -f src/workforce/$(ARTIFACTS)
