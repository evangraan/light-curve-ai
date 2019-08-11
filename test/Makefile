CC=g++
CFLAGS=-g -c -Wall
AFLAGS=-g
INCLUDES=-I /home/ernstv/build/opencv/release/include -I/usr/local/include/opencv4 -I /home/ernstv/build/opencv/projects/Test0001/test
LIBS=-lstdc++ -lopencv_imgcodecs -lopencv_highgui -lopencv_core -lopencv_imgproc -lopencv_features2d -lopencv_flann -lgtest -lpthread
ARTIFACTS=*.o runTests *.dSym
SOURCES=../src
TEST_APPLICATION=application
TEST_APPLICATION_SOURCES=$(TEST_APPLICATION)/TestApplication.cpp
TEST_FIXTURES=fixtures
TEST_FIXTURES_SOURCES=$(TEST_FIXTURES)/ImagesFixture.cpp
TEST_PROCESSING=processing
TEST_PROCESSING_SOURCES=$(TEST_PROCESSING)/ImageTests.cpp $(SOURCES)/processing/Images.cpp
EXECUTABLE=runTests

default: test

all: test

test: fixtures processing application
	$(CC) $(AFLAGS) *.o -o $(EXECUTABLE) $(INCLUDES) $(LIBS)

application: $(TEST_APPLICATION_SOURCES)
	$(CC) $(CFLAGS) $(TEST_APPLICATION_SOURCES) $(INCLUDES) $(LIBS)

fixtures: $(TEST_FIXTURES_SOURCES)
	$(CC) $(CFLAGS) $(TEST_FIXTURES_SOURCES) $(INCLUDES) $(LIBS)

processing: $(TEST_PROCESSING_SOURCES)
	$(CC) $(CFLAGS) $(TEST_PROCESSING_SOURCES) $(INCLUDES) $(LIBS)
	
clean:
	rm -f $(ARTIFACTS)
	rm -f $(FIXTURES)/$(ARTIFACTS)
	rm -f $(PROCESSING)/$(ARTIFACTS)
	rm -f $(APPLICATION)/$(ARTIFACTS)

.PHONY: all test clean application fixtures processing