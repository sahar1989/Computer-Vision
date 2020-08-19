
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

int main(int, char** argv)
{

       Mat leftRGB = imread(argv[1],1);
       Mat rightRGB = imread(argv[2],1);
       Mat left;
       Mat right;
       cvtColor(leftRGB, left, CV_BGR2GRAY);
       cvtColor(rightRGB, right, CV_BGR2GRAY);
       Mat resLeft, resRight;
       // add your code here
 	StereoBM sbm;
	sbm.state->SADWindowSize = 9;
	sbm.state->numberOfDisparities = 112;
	sbm.state->preFilterSize = 5;
	sbm.state->preFilterCap = 61;
	sbm.state->minDisparity = -39;
	sbm.state->textureThreshold = 507;
	sbm.state->uniquenessRatio = 0;
	sbm.state->speckleWindowSize = 0;
	sbm.state->speckleRange = 8;
	sbm.state->disp12MaxDiff = 1;

	sbm(left, right, resLeft);
	normalize(resLeft, resRight, 0, 255, CV_MINMAX, CV_8U);

	StereoSGBM sgbm;
	sgbm.SADWindowSize = 5;
	sgbm.numberOfDisparities = 192;
	sgbm.preFilterCap = 4;
	sgbm.minDisparity = -64;
	sgbm.uniquenessRatio = 1;
	sgbm.speckleWindowSize = 150;
	sgbm.speckleRange = 2;
	sgbm.disp12MaxDiff = 10;
	sgbm.fullDP = false;
	sgbm.P1 = 600;
	sgbm.P2 = 2400;

	sgbm(left, right, resLeft);
	normalize(resLeft, resRight, 0, 255, CV_MINMAX, CV_8U);

	imshow("match Left1 " , resLeft);
	imshow("match Right1 ", resRight);
	imwrite("resLeftF2.png", resLeft);
	imwrite("resRightF2.png", resRight);
        cvWaitKey(0);
 
       return 0;
}
