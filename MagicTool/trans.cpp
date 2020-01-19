#include "MagicTool.h"
#include <iostream>
#include <string>

int main() {
  cv::VideoCapture cap(0);
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 800);
  
  std::string bg_path;
  std::getline(std::cin, bg_path);
  cv::Mat bg = cv::imread(bg_path);
  
  std::string translation_path;
  std::getline(std::cin, translation_path);

  while (true) {
    cv::Mat frame;
    bool ok = cap.read(frame); 
    if (ok == false) {
      std::cout << "Found the end of the video" << std::endl;
      break;
    }
    
    if (frame.size() != bg.size()) {
      IMAGIC::fit(frame, bg);
    }

    frame = IMAGIC::ChromaKey(-1, frame, bg);  
    cv::imwrite(translation_path + std::to_string(std::rand()), frame);
  }
}
