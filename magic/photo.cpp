#include "magic.h"
#include <iostream>
#include <string>

int main() {
  std::string imname;
  std::getline(std::cin, imname);
  cv::Mat im = cv::imread(imname);
  
  std::string bgname;
  std::getline(std::cin, bgname);
  cv::Mat bg = cv::imread(bgname);
  
  std::string resname;
  std::getline(std::cin, resname);  

  int sensivity;
  std::cin >> sensivity;

  cv::Mat res = IMAGIC::ChromaKey(+1, im, bg, sensivity);
  cv::imwrite(resname, res);
}
