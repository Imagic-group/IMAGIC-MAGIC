#include <opencv2/opencv.hpp>
#include <bits/stdc++.h>

using namespace cv;
using namespace std;

double dist(const Vec3b& a, const Vec3b& b) {
  return sqrt(
    (a[0] - b[0]) * (a[0] - b[0]) +
    (a[1] - b[1]) * (a[1] - b[1]) +
    (a[2] - b[2]) * (a[2] - b[2])
  );
}

int main(int argc, char* argv[]) {
  string filename;
  getline(cin, filename);
  Mat im = imread("TestData/"+filename);
  
  Mat res;
  GaussianBlur(im, res, Size(3, 3), 0);
  //swap(im, res);
  //adaptiveBilateralFilter(im, res, Size(5, 5), 150);
  
  int n = res.rows;
  int m = res.cols;
  vector<Vec3b> keys = {
    res.at<Vec3b>(0, 0),
    res.at<Vec3b>(0, m - 1),
    res.at<Vec3b>(n - 1, 0),
    res.at<Vec3b>(n - 1, m - 1)
  };
  
  for (auto key : keys) {
    for (int i = 0; i < res.rows; ++i) {
      for (int j = 0; j < res.cols; ++j) {
        if (dist(res.at<Vec3b>(i, j), key) < 64) {
          Vec3b color(0, 0, 0);
          res.at<Vec3b>(i, j) = color;
        }
      }
    }
  }
  
  swap(im, res);

  vector<Mat> lays;
  split(im, lays);
  Mat lay;
  erode(lays[1], lay, getStructuringElement(MORPH_RECT, Size(5, 5)));
  swap(lay, lays[1]);
  merge(lays, res);
  
  namedWindow("kek");
  imwrite("TestData/res.jpg", res);
  imshow("kek", res);
  waitKey(0);
  destroyWindow("kek");
}
