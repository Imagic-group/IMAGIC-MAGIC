#include "MagicTool.h"

int main() {
  string imname;
  getline(cin, imname);
  Mat im = imread(imname);
  
  string bgname;
  getline(cin, bgname);
  Mat bg = imread(bgname);
	
  string resname;
  getline(cin, resname);  

	Mat res = IMAGIC::ChromaKey(+1, im, bg);
  imwrite(resname, res);
}
