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
int counter=0;
void apply_homography(){
    if(counter==8){
           // Calculate Homography
            Mat h = findHomography(pts_src, pts_dst);
 
 	   // Output image
 	   Mat im_out;
 	   //Warp source image to destination based on homography
 	    warpPerspective(src, im_out, h, src.size());
 
	    //Display images
	    imshow("Warped Source Image", im_out);
            counter=0;
 	for( int i = 0; i < h.rows; i++){
        	for( int j = 0; j < h.cols; j++){
            cout << h.at<double>(i,j) << endl;
           }	
    	  }
      }
}
void mouse_callback(int event, int x, int y, int flags, void* unused)
{
   if (event == EVENT_LBUTTONDOWN){
	cout << "You have clicked on point (" << x << ", " << y << ")\n";
        if(counter%2==0)
           pts_src.push_back(Point2f(x, y));
        else 
          pts_dst.push_back(Point2f(x, y));
        
        counter++; 
        apply_homography();
    }
}
/*
this points was nice on homography 
You have clicked on point (65, 67)
You have clicked on point (64, 117)
You have clicked on point (189, 80)
You have clicked on point (187, 134)
You have clicked on point (58, 259)
You have clicked on point (58, 308)
You have clicked on point (205, 262)
You have clicked on point (205, 298)
1.0699
0.0915703
-11.5732
-0.0463414
1.13932
2.09932
-0.000121599
0.000636304
1


*/


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


