#LIBS=-lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_calib3d -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_objdetect -lopencv_video -lopencv_calib3d

LIBS=$(shell pkg-config --libs opencv)

TARGETS=stereomatch stereograb calibrate3d rectify3d

all: $(TARGETS)

clean:
	rm -f $(TARGETS) *.o *~

stereograb: stereograb.cpp
	g++ -o stereograb stereograb.cpp $(LIBS)

stereomatch: stereomatch.cpp
	g++ -o stereomatch stereomatch.cpp $(LIBS)


rectify3d: rectify3d.cpp
	g++ -o rectify3d rectify3d.cpp $(LIBS)


calibrate3d: calibrate3d.cpp
	g++ -o calibrate3d calibrate3d.cpp $(LIBS)


