#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <stdlib.h>

using namespace std;
using namespace cv;

int dev[] = { 0, 1 };   /* refers to /dev/videox */
char suf[] = { 'L', 'R' };

int main(int, char** argv)
{
  for (int i= 0; i < 2; i++)
    {
      char fname[256];
      VideoCapture cap;

      if (!cap.open(dev[i]))
	{
	  cout << "Ne peut pas ouvrir /dev/video" << dev[i] << "\n";
	  return 1;
	}

      Mat frame;
      cap >> frame;
      sprintf(fname, "%s-%c.png", argv[1], suf[i]);
      imwrite(fname, frame);
    }
  
  return 0;
}
