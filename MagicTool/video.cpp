#include "MagicTool.h"

int main() {
  /*
  string imname;
  getline(cin, imname);
  Mat im = imread("TestData/"+imname);
  
  string bgname;
  getline(cin, bgname);
  Mat bg = imread("TestData/"+bgname);

  Mat res = IMAGIC::ChromaKey(im, bg);
  
  imwrite("TestData/res.jpg", res);
  */

  VideoCapture cap(0);//("MagicTool/TestData/v2.mp4");
  cap.set(CV_CAP_PROP_FRAME_HEIGHT, 800);
  cap.set(CV_CAP_PROP_FRAME_WIDTH, 600);
  Mat bg = imread("MagicTool/TestData/bg.jpg");
  
  //String vid0 = "Original Video";
  String vid1 = "ChromaKeyVideo";
  //namedWindow(vid0, WINDOW_NORMAL);
  namedWindow(vid1, WINDOW_NORMAL);
  while (true) {
    Mat frame;
		bool bSuccess;
		for (int i = 0; i < 1; ++i) {
    	bSuccess = cap.read(frame); 
    	if (bSuccess == false) {
      	break;
    	}
		}
    if (bSuccess == false) {
      cout << "Found the end of the video" << endl;
      break;
    }
		
    if (frame.size() != bg.size()) {
      IMAGIC::fit(frame, bg);
    }

    //imshow(vid0, frame);
		frame = IMAGIC::ChromaKey(-1, frame, bg);	
		imshow(vid1, frame);
		if (waitKey(5) == 27) {
      cout << 
				"Esc key is pressed by the user. Stopping the video"
			<< endl;
      break;
    }
	}
	destroyAllWindows();
}