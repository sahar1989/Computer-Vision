#include <fstream>
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"

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
  Mat imLeft, imRight;
  Mat rectLeft, rectRight;
  
  imLeft= imread(argv[1], 1);
  imRight= imread(argv[2], 1);


  // ... add your code
  cvtColor(imLeft, imLeft, CV_BGR2GRAY);
  cvtColor(imRight, imRight, CV_BGR2GRAY);

   vector<Point2f> points1=chessPoints(imLeft);
   vector<Point2f> points2=chessPoints(imRight);


   Mat img1 = imread( "calib1-L.png", 1 );
   Mat img2 = imread( "calib1-R.png", 1 );
   Mat img3 = imread( "calib2-L.png", 1 );
   Mat img4 = imread( "calib2-R.png", 1 );//F2(img1,img2,img3,img4);/*
   Mat fundamental_matrix = findFundamentalMat(points1, points2, FM_RANSAC, 3, 0.99);
   for( int i = 0; i < fundamental_matrix.rows; i++){
       for( int j = 0; j < fundamental_matrix.cols; j++){
            cout << fundamental_matrix.at<double>(i,j) << endl;
       }	
    }

   
    Size imageSize= imLeft.size(); 
    Mat homLeft;
    Mat homRight;
    stereoRectifyUncalibrated(points1,points2, fundamental_matrix, imageSize, homLeft, homRight,5 );
    warpPerspective(imRight, rectRight, homRight, imRight.size());
    warpPerspective(imLeft, rectLeft, homLeft, imLeft.size());
    imshow("line Left", imLeft);
    imshow("line Right ", imRight);
    imshow("recx Left", rectLeft);
    imshow("recx Right ", rectRight);
    imwrite("rectified1LF1.png", rectLeft);
    imwrite("rectified1RF1.png", rectRight);


        /* write in stereo match 
        Mat rectLeft1, rectRight1;
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

	sbm(rectLeft, rectRight, rectLeft1);
	normalize(rectLeft1, rectRight1, 0, 255, CV_MINMAX, CV_8U);

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

	sgbm(rectLeft, rectRight, rectLeft1);
	normalize(rectLeft1, rectRight1, 0, 255, CV_MINMAX, CV_8U);

        imshow("recx Left1 " , rectLeft1);
        imshow("recx Right1 ", rectRight1);
       imwrite("matchL.png", rectLeft1);
       imwrite("matchR.png", rectRight1);*/

    waitKey(0); 
    return 0;
}
