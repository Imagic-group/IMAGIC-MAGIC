namespace IMAGIC {
  double dist(const Vec3b& a, const Vec3b& b);
  vector<Vec3b> get_keys(const Mat& im);
  void  remove_treshold(Mat& im, int rude);
  Mat  get_mask(const Mat im, const vector<Vec3b>& keys, int sensivity);
  void solve(Mat& im, Mat& bg, const Mat& mask0, const Mat& mask1);
  void equalize(Mat& im);
  void fit(const Mat& a, Mat& b);
  Mat  ChromaKey(int quality, Mat im, Mat bg, int sensivity = -1);
}
