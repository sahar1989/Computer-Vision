// Computer Vision
// Skeleton program to load images and grab clicked points in OpenCV.
// (c) X. Hilaire, december 2013.

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
  printf("ghjgjhg");  
  const char *win_name = "My window";
  
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  /// Create a window and display the image
  namedWindow( win_name, CV_WINDOW_AUTOSIZE );
  //imshow( win_name, src );
  
  //our code  
  Mat img_gray,img_aligned;
  cvtColor(src, img_gray, CV_BGR2GRAY);
  imshow( win_name, img_gray );

    Matx33f wrap_mat(1,2,3,
                     4,5,6,
                     7,8,9);
   
    // Output image
    Mat im_out;
    warpPerspective(src, im_out, wrap_mat, src.size());
 
    // Display images
    imshow("Source Image", src);
    imshow("Warped Source Image", im_out);
  
  
    //imshow( win_name, img );
  setMouseCallback(win_name, mouse_callback, NULL);


  // Wait for the user to hit a key
  waitKey(0);
  return(0);
}


