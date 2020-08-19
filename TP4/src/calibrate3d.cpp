#include <fstream>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>   
using namespace cv;
using namespace std;

vector<Point2f> chessPoints(Mat image){
 
  vector<Point2f> pointbuf;
  Size boardSize, imageSize;
  boardSize.width= 8;
  boardSize.height= 5;
  bool found;

  found = findChessboardCorners( image, boardSize, pointbuf,
                    CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);

  return pointbuf;
}

double ASE( vector<Point2f> u, vector<Point2f> v, Mat F){

   int size = u.size();
   float sum = 0.0;
   vector<cv::Vec3f> epilines1;
   vector<cv::Vec3f> epilines2;

   // Compute corresponding epipolar lines
    cv::computeCorrespondEpilines(u, // image points //point jsut two first and last
                                  1, // in image 1 (can also be 2)
                                  F, // F matrix
                                  epilines1); // vector of epipolar lines
    
    cv::computeCorrespondEpilines(v, // image points
                                  2, // in image 1 (can also be 2)
                                  F, // F matrix
                                  epilines2); // vector of epipolar lines 



   for(int i=0;i<size;i++){
        float val1 = (v[i].x  - (epilines1[i][0]/epilines1[i][2])) - (u[i].x  - (epilines2[i][0]/epilines2[i][2])); 
        float val2 = (v[i].y  - (epilines1[i][1]/epilines1[i][2])) - (u[i].y  - (epilines2[i][1]/epilines2[i][2]));
        sum  = sqrt(pow(val1,2) + pow(val2,2)) + sum;
   }

  
   double result =sum/size;
   cout << "result : "<<  result<<" \n";
   return result;

}
Mat F1(vector<Point2f> points1, vector<Point2f> points2){

   Mat fundamental_matrix = findFundamentalMat(points1, points2, FM_RANSAC, 3, 0.99);
   for( int i = 0; i < fundamental_matrix.rows; i++){
       for( int j = 0; j < fundamental_matrix.cols; j++){
            cout << fundamental_matrix.at<double>(i,j) << endl;
       }	
    }

   return fundamental_matrix;

} 

Mat F2(Mat img1, Mat img2, Mat img3, Mat img4){

  vector<Point2f> points1=chessPoints(img1);
  vector<Point2f> points2=chessPoints(img2);

  vector<Point2f> points3=chessPoints(img3);
  vector<Point2f> points4=chessPoints(img4);

   vector<Point2f> points13;
   points13.reserve( points1.size() + points3.size() );
   points13.insert( points13.end(), points1.begin(), points1.end() );
   points13.insert( points13.end(), points3.begin(), points3.end() );

   vector<Point2f> points24;
   points24.reserve( points2.size() + points4.size() );
   points24.insert( points24.end(), points2.begin(), points2.end() );
   points24.insert( points24.end(), points4.begin(), points4.end() );

  
   Mat fundamental_matrix = findFundamentalMat(points13, points24, FM_RANSAC, 3, 0.99);
   for( int i = 0; i < fundamental_matrix.rows; i++){
       for( int j = 0; j < fundamental_matrix.cols; j++){
            cout << fundamental_matrix.at<double>(i,j) << endl;
       }	
    }
  return  fundamental_matrix;
}

int main(int argc, char *argv[])
{

    cout << argv[0]<< " \n";
    cout << argv[1]<< " \n";
    cout << argv[2]<< " \n";

  // load + display image
  if (argc != 3) {//5
	cerr << "Usage: " << argv[0] << " image\n";
	return 1;
  }

  Mat img1 = imread( argv[1], 1 );
  Mat img2 = imread( argv[2], 1 );
 /* Mat img3 = imread( argv[3], 1 );
   Mat img4 = imread( argv[4], 1 );*/
   
   vector<Point2f> points1=chessPoints(img1);
   vector<Point2f> points2=chessPoints(img2);

   Mat fundamental_matrix = F1(points1,points2);
   cout << "error :"<< ASE(points1,points2,fundamental_matrix) <<endl;
   cout <<  "*********************"<< endl;
   cout <<  points1[0]<< endl;
   cout <<  points1[points1.size()-1]<< endl;

    vector<cv::Vec3f> epilines;
    vector<cv::Vec3f> epilines1;
    vector<cv::Vec3f> epilines2;
    vector<Point2f> point;
    point.push_back(points1[0]);
    point.push_back(points1[points1.size()-1]);

    cv::computeCorrespondEpilines(point, // image points //point jsut two first and last
                                  1, // in image 1 (can also be 2)
                                  fundamental_matrix, // F matrix
                                  epilines); // vector of epipolar lines


    // for all epipolar lines
    for (std::vector<cv::Vec3f>::const_iterator it = epilines.begin(); it!=epilines.end(); ++it)
    {
        // Draw the line between first and last column
        cv::line(img2,
                 cv::Point(0,-(*it)[2]/(*it)[1]),
                 cv::Point(img1.cols,-((*it)[2]+
                                              (*it)[0]*img1.cols)/(*it)[1]),
                 cv::Scalar(0,255,0));
    }

   imshow("line Left", img1);
   imshow("line Right ", img2);
   waitKey(0); 





 /*
  Mat image; 
  Size boardSize, imageSize;
  vector<Point2f> pointbuf;
  bool found;
  boardSize.width= 8;
  boardSize.height= 5;
imageSize= image.size();
  // find the chessboard
  found = findChessboardCorners( image, boardSize, pointbuf,
                    CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);


  if(found)
  {
	// improve the found corners' coordinate accuracy
	Mat viewGray;

   	cvtColor(image, viewGray, CV_BGR2GRAY);
	cornerSubPix( viewGray, pointbuf, Size(11,11), Size(-1,-1), 
		TermCriteria( CV_TERMCRIT_EPS+CV_TERMCRIT_ITER, 30, 0.1 ));

	drawChessboardCorners( image, boardSize, Mat(pointbuf), found );

	namedWindow( "Display window", WINDOW_AUTOSIZE );// Create a window for display.
	imshow( "Display window", image );                   // Show our image inside it.

	  waitKey(0);                                          // Wait for a keystroke in the window
  }
  else
	cerr << "Chessboard not found.\n";*/

  return 0;
}


