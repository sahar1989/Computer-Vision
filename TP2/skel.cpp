/**
 * @function cornerHarris_Demo.cpp
 * @brief Demo code for detecting corners using Harris-Stephens method
 * @author OpenCV team
 */

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

/// Global variables
Mat src;

void mouse_callback(int event, int x, int y, int flags, void* unused)
{
if (event == EVENT_LBUTTONDOWN)
	cout << "You have clicked on point (" << x << ", " << y << ")\n";
}



int main( int, char** argv )
{
  const char *win_name = "My window";
  
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  /// Create a window and display the image
  namedWindow( win_name, CV_WINDOW_AUTOSIZE );
  imshow( win_name, src );

  setMouseCallback(win_name, mouse_callback, NULL);


  // Wait for the user to hit a key
  waitKey(0);
  return(0);
}


