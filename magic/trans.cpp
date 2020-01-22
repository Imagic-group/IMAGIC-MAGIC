#include <iostream>
#include "magic.h"

void read_jpeg(std::istream& file, std::vector<char>& frame_buffer) {
  bool started = false;
  while (true) {
    const int c1 = file.get();
    const int c2 = file.get();
    if (started) {
      frame_buffer.push_back(c1);
      frame_buffer.push_back(c2);

      const uint16_t code = ((c1 << 8) | c2);
      if (code == 0xffd9) {
        break;
      }
    } else {
      const uint16_t code = ((c1 << 8) | c2);
      if (code == 0xffd8) {
        frame_buffer.push_back(c1);
        frame_buffer.push_back(c2);
        started = true;
      }
    }
  }
}

cv::Mat get_frame(std::istream& file) {
  std::vector<char> frame_buffer;
  read_jpeg(file, frame_buffer);
  return imdecode(cv::Mat(frame_buffer), 1);
}

int main(int argc, char** argv) {
  if (argc < 2) {
    std::cerr << "ERROR: unknown name of background\n";
    std::cerr << "Usage: gphoto2 --capture-movie --stdout | ./trans <background>" << std::endl;
    return 0;
  }

  cv::Mat bg = cv::imread(argv[1]);

  while (true) {
    cv::Mat frame = get_frame(std::cin);
    
    if (frame.size() != bg.size()) {
      IMAGIC::fit(frame, bg);
    }

    frame = IMAGIC::ChromaKey(-1, frame, bg);
    
    std::vector<unsigned char> encoded_frame;
    cv::imencode(".jpg", frame, encoded_frame);
    frame = cv::imdecode(cv::Mat(encoded_frame), 1);
    
    for (unsigned char c : encoded_frame) {
      std::cout << c;
    }
    std::cout.flush();
  }
  return 0;
}
