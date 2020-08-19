LIBS=-lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_calib3d  -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_video -lopencv_calib3d 


calibration: calibration.cpp
	g++ -o calibration calibration.cpp $(LIBS)

capture: capture.cpp
	g++ -o capture -I/opt/local/include capture.cpp -L/opt/local/lib $(LIBS)

facedetect: facedetect.cpp
	g++ -g -o facedetect -I/opt/local/include -I/opt/local/include/opencv2 facedetect.cpp -L/opt/local/lib $(LIBS)

