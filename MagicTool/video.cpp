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

  std::string vid1 = "ChromaKeyVideo";
  cv::namedWindow(vid1, CV_WINDOW_AUTOSIZE);
  
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
    cv::imshow(vid1, frame);
    if (cv::waitKey(5) == 27) {
      std::cout << 
        "Esc key is pressed by the user. Stopping the video"
      << std::endl;
      break;
    }
  }
  cv::destroyAllWindows();
}
