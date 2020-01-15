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

vector<Vec3b> get_keys(const Mat& im) {
  int n = im.rows;
  int m = im.cols;
  return {
    im.at<Vec3b>(0, 0),
    im.at<Vec3b>(0, m - 1),
    im.at<Vec3b>(n - 1, 0),
    im.at<Vec3b>(n - 1, m - 1)
  };
}

Mat remove_treshold(Mat im, int rude) {
	int lowThreshold = 100;
	int ratio = 3;
	int kernelSize = 3;
	
	Mat srcGray, cannyEdges, blurred;

	erode(im, im, getStructuringElement(MORPH_RECT, Size(rude, rude)));
	srcGray = im.clone();
	
	blur(srcGray, cannyEdges, Size(rude - 2, rude - 2));
	Canny(cannyEdges, cannyEdges, lowThreshold, lowThreshold * ratio, kernelSize);
	
	int dilation_size = 5;
	Mat element = getStructuringElement(MORPH_CROSS,
	Size(2 * dilation_size + 1, 2 * dilation_size + 1),
	Point(dilation_size, dilation_size));
	
	dilate(cannyEdges, cannyEdges, element);
	im.copyTo(blurred);
	blur(blurred, blurred, Size(rude - 1, rude - 1));
	blurred.copyTo(im, cannyEdges);
  cerr << cannyEdges.type() << endl;
  namedWindow("kek");
  imshow("kek", cannyEdges);
  waitKey(0);
  destroyWindow("kek");
  
  return im;
}

Mat get_mask(const Mat im, const vector<Vec3b>& keys) {
  double dst = 0;
  for (auto key1 : keys) {
    for (auto key2 : keys) {
      dst = max(dst, dist(key1, key2));
    }
  }
  Mat res(im.size(), CV_8UC1);
  for (int i = 0; i < im.rows; ++i) {
    for (int j = 0; j < im.cols; ++j) {
      res.at<unsigned char>(i, j) = 255;
    }
  }
  for (auto key : keys) {
    for (int i = 0; i < im.rows; ++i) {
      for (int j = 0; j < im.cols; ++j) {
        if (dist(im.at<Vec3b>(i, j), key) < max(100, int(dst))) {
          res.at<unsigned char>(i, j) = 0;
        }
      }
    }
  }
  return res;
}

Mat solve(Mat im, Mat bg, Mat mask0, Mat mask1) {
  vector<Mat> msk = {mask0, mask1, mask0};
  vector<Mat> res(3), v, u;
  split(im, v);
  split(bg, u);
  
  v[0].copyTo(res[0], msk[0]);
  subtract(cv::Scalar::all(255), msk[0], msk[0]);
  u[0].copyTo(res[0], msk[0]);
  subtract(cv::Scalar::all(255), msk[0], msk[0]);

  v[1].copyTo(res[1], msk[1]);
  subtract(cv::Scalar::all(255), msk[1], msk[1]);
  u[1].copyTo(res[1], msk[1]);
  subtract(cv::Scalar::all(255), msk[1], msk[1]);
  
  v[2].copyTo(res[2], msk[0]);
  subtract(cv::Scalar::all(255), msk[0], msk[0]);
  u[2].copyTo(res[2], msk[0]);
  subtract(cv::Scalar::all(255), msk[0], msk[0]);
  
  merge(res, im);
  return im;
}

void equalize(Mat& im) {
  {
 		Mat hist_equalized_image;
    cvtColor(im, hist_equalized_image, COLOR_BGR2YCrCb);

    //Split the image into 3 channels; Y, Cr and Cb channels respectively and store it in a std::vector
    vector<Mat> vec_channels;
    split(hist_equalized_image, vec_channels); 

    //Equalize the histogram of only the Y channel 
    equalizeHist(vec_channels[0], vec_channels[0]);

    //Merge 3 channels in the vector to form the color image in YCrCB color space.
    merge(vec_channels, hist_equalized_image); 
        
    //Convert the histogram equalized image from YCrCb to BGR color space again
    cvtColor(hist_equalized_image, hist_equalized_image, COLOR_YCrCb2BGR);
		swap(im, hist_equalized_image);  
	}
  //im.convertTo(im, -1, 4, -128);
}

void fit(Mat& im, Mat& bg) {
  double imr = double(im.rows) / im.cols;
  double bgr = double(bg.rows) / bg.cols;
  
  bool transposed = false;
  if (imr < bgr) {
    transpose(im, im);
    transpose(bg, bg);
    transposed = true;
  }
  
  double imScale = double(im.rows) / bg.rows;
  if (imScale >= 1) {
    resize(bg, bg, im.size(), 1.0 / imScale, 1.0 /imScale);
  } else {
    resize(im, im, im.size(), imScale, imScale);
    resize(im, im, im.size(), 1.0, 1.0);
  }

  if (transposed) {
    transpose(im, im);
    transpose(bg, bg);
  }
}

int main(int argc, char* argv[]) {
  string imname;
  getline(cin, imname);
  Mat im = imread("TestData/"+imname);
  
  string bgname;
  getline(cin, bgname);
  Mat bg = imread("TestData/"+bgname);
  fit(im, bg);

  Mat for_mask = im.clone();
  equalize(for_mask);
  adaptiveBilateralFilter(im, for_mask, Size(5, 5), 150);
  
  vector<Vec3b> keys = get_keys(for_mask);
	Mat mask = get_mask(for_mask, keys);
  
  Mat res = solve(im, bg, remove_treshold(mask, 5),
                          remove_treshold(mask, 7));
  
  namedWindow("kek");
  imwrite("TestData/res.png", res);
  imshow("kek", res);
  waitKey(0);
  destroyWindow("kek");
}
