LIBS=-lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_calib3d -lopencv_video

all: skel homography1 homography2 

skel: skel.cpp
	g++ -g -Wall -o skel skel.cpp $(LIBS)

homography1: homography1.cpp
	g++ -g -Wall -o homography1 homography1.cpp $(LIBS)

homography2: homography2.cpp
	g++ -g -Wall -o homography2 homography2.cpp $(LIBS)

