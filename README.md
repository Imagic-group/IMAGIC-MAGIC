# IMAGIC-SERVER-SIDE
## PREPARING
First of all you need to run some commands in terminal (of course you have to be in the main folder of the project):
```
  chmod +x install_openCV
  ./install_openCV
```
Yeah!
You've installed OpenCV for C++, congratulations!
Now you should build my Project
## BUILDING
Just run the following commands:
```
  chmod +x build
  ./build all
```
You can also build components independently like this
```
  ./build magic
  ./build photo
  ./build trans
  ./build video
  ./build magic video photo trans
```
###(WARNING: In the last line order matters!!!)

Fine! Now you are about the finish!
## RUNNING
For removing chroma key from the web camera you need to run
```
  ./video
  background_path/background.jpg
```
To get the result for picture, run this one
```
  ./photo
  photo_path/some_photo.jpg
  background_path/some_background.jpg
  result_path/some_result.jpg
  -1
```
### That's all. Thanks for download ;)
