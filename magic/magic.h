#include <opencv2/opencv.hpp>
#include <vector>

namespace IMAGIC {
  double dist(const cv::Vec3b& a, const cv::Vec3b& b);
  std::vector<cv::Vec3b> get_keys(const cv::Mat& im);
  void remove_treshold(cv::Mat& im, int rude);
  cv::Mat get_mask(const cv::Mat im, const std::vector<cv::Vec3b>& keys, int sensivity);
  void solve(cv::Mat& im, cv::Mat& bg, const cv::Mat& mask0, const cv::Mat& mask1);
  void equalize(cv::Mat& im);
  void fit(const cv::Mat& a, cv::Mat& b);
  cv::Mat ChromaKey(int quality, cv::Mat im, cv::Mat bg, int sensivity = -1);
}
