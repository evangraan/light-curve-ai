default: all

all: clean Images.cpp Messages.cpp Test0001.cpp
	g++ -std=c++11 -ggdb `pkg-config --cflags --libs opencv4` -o Test0001 Test0001.cpp Images.cpp Messages.cpp -I /Users/ernstv/OpenCV/projects/Test00001 -I /Users/ernstv/OpenCV/opencv-4.0.0/build/include/opencv4 -I /Users/ernstv/OpenCV/opencv-4.0.0/modules/core/include -I /Users/ernstv/OpenCV/opencv-4.0.0/modules/imgcodecs/include -I /Users/ernstv/OpenCV/opencv-4.0.0/modules/highgui/include -I /Users/ernstv/OpenCV/opencv-4.0.0/modules/imgproc/include
	
clean:
	rm -rf build