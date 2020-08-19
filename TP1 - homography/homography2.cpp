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
vector<Point2f> pts_dst;
vector<Point2f> pts_src;
void apply_homography(){
   /*vector<Point2f> pts_src;
    pts_src.push_back(Point2f(141, 131));
    pts_src.push_back(Point2f(480, 159));
    pts_src.push_back(Point2f(493, 630));
    pts_src.push_back(Point2f(64, 601));*/
    if(pts_src.size()>3){
       // Calculate Homography
           Mat h = findHomography(pts_src, pts_dst);
 
 	   // Output image
 	   Mat im_out;
 	   // Warp source image to destination based on homography
 	  warpPerspective(src, im_out, h, src.size());
 
	    // Display images
	    imshow("My window1", src);
	    imshow("Warped Source Image", im_out);
      }
}
void mouse_callback(int event, int x, int y, int flags, void* unused)
{
   if (event == EVENT_LBUTTONDOWN){
	cout << "You have clicked on point (" << x << ", " << y << ")\n";
        pts_dst.push_back(Point2f(2*x+1, 2*y+1));
        pts_src.push_back(Point2f(2*x, 2*y));
        apply_homography();

    }
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
  
  // Four corners of the book in source image
  
  // setMouseCallback(win_name, mouse_callback, NULL); 
  // Wait for the user to hit a key
  waitKey(0);
  return(0);
}


