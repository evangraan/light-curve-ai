CC=g++
CFLAGS=-g -c -Wall
AFLAGS=-g
INCLUDES=-I /home/ernstv/build/opencv/release/include -I/usr/local/include/opencv4
LIBS=-lstdc++ -lopencv_imgcodecs -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_features2d -lopencv_flann -lpthread
ARTIFACTS=*.o lcai *.dSym
WORKFORCE=src/workforce
WORKFORCE_SOURCES=$(WORKFORCE)/IWorker.cpp $(WORKFORCE)/SimpleWorker.cpp $(WORKFORCE)/WorkQueue.cpp $(WORKFORCE)/WorkerPool.cpp $(WORKFORCE)/WaitForCompletionFuture.cpp
APPLICATION=src/application
APPLICATION_SOURCES=$(APPLICATION)/Application.cpp
ASPECTS_SOURCES=$(APPLICATION)/Messages.cpp
PROCESSING=src/processing
PROCESSING_SOURCES=$(PROCESSING)/IProcessor.cpp $(PROCESSING)/ChiSquaredProcessor.cpp $(PROCESSING)/Orchestrator.cpp $(PROCESSING)/Images.cpp
EXECUTABLE=lcai
OUTPUT=images/lc/*comparison

default: all

all: workforce aspects application
	$(CC) $(AFLAGS) *.o -o $(EXECUTABLE) $(INCLUDES) $(LIBS)

application: workforce aspects processing $(APPLICATION_SOURCES)
	$(CC) $(CFLAGS) $(APPLICATION_SOURCES) $(INCLUDES) $(LIBS)

workforce: $(WORKFORCE_SOURCES)
	$(CC) $(CFLAGS) $(WORKFORCE_SOURCES) $(INCLUDES) $(LIBS)

aspects: $(ASPECTS_SOURCES)
	$(CC) $(CFLAGS) $(ASPECTS_SOURCES) $(INCLUDES) $(LIBS)
	
processing: $(PROCESSING_SOURCES)
	$(CC) $(CFLAGS) $(PROCESSING_SOURCES) $(INCLUDES) $(LIBS)
clean:
	rm -f $(ARTIFACTS)
	rm -f $(WORKFORCE)/$(ARTIFACTS)
	rm -f $(ASPECTS)/$(ARTIFACTS)
	rm -f $(PROCESSING)/$(ARTIFACTS)
	rm -f $(APPLICATION)/$(ARTIFACTS)
	rm -f $(OUTPUT)
