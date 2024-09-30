#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
  // read image
  Mat image = imread("red.png");
  namedWindow("image", WINDOW_NORMAL);
  // create output image to draw lines on
  Mat output = image.clone();
  Mat hsvImage;
  // convert image to hsv for thresholding
  cvtColor(image, hsvImage, COLOR_BGR2HSV);
  // bright red range
  Scalar lowerRed(0, 140, 190), upperRed(10, 255, 255);
  Mat redMask;
  // find contours
  inRange(hsvImage, lowerRed, upperRed, redMask);
  vector<vector<Point> > contours;
  findContours(redMask, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);
  // find center of each contour
  vector<Point2f> centers;
  for (int i = 0; i < contours.size(); i++) {
    double area = contourArea(contours[i]);
    if (area > 100) {
      Moments m = moments(contours[i]);
      if (m.m00 != 0) {
        Point2f center(m.m10 / m.m00, m.m01 / m.m00);
        centers.push_back(center);
      }
    }
  }
  // check whether each contour is on the left or right
  vector<Point2f> left;
  vector<Point2f> right;
  for (Point2f contour : centers) {
    if (contour.x > 900) {
      right.push_back(contour);
    }
    else {
      left.push_back(contour);
    }
  }
  // fit a line through each contour and draw it from x = 0 to x = end of image
  Vec4f leftLine;
  Vec4f rightLine;
  fitLine(left, leftLine, 4, CV_PI / 2, CV_PI / 2, true);
  Point leftPoint0 = Point(leftLine[2], leftLine[3]);
  Point leftPoint1, leftPoint2;
  leftPoint1.x = 0;
  leftPoint1.y = leftPoint0.y - (leftLine[1] / leftLine[0]) * leftPoint0.x;
  leftPoint2.x = image.cols;
  leftPoint2.y = leftPoint0.y + (leftLine[1] / leftLine[0]) * (leftPoint2.x - leftPoint0.x);
  fitLine(right, rightLine, 4, CV_PI / 2, CV_PI / 2, true);
  Point rightPoint0 = Point(rightLine[2], rightLine[3]);
  Point rightPoint1, rightPoint2;
  rightPoint1.x = 0;
  rightPoint1.y = rightPoint0.y - (rightLine[1] / rightLine[0]) * rightPoint0.x;
  rightPoint2.x = image.cols;
  rightPoint2.y = rightPoint0.y + (rightLine[1] / rightLine[0]) * (rightPoint2.x - rightPoint0.x);
  line(output, leftPoint1, leftPoint2, Scalar(0, 0, 255), 5);
  line(output, rightPoint1, rightPoint2, Scalar(0, 0, 255), 5);
  // output image
  while (true) {
    imshow("image", output);
    waitKey(20);
  }
}