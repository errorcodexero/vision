all:
	rm -rf ./errorLogs/err.txt
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DBLUE -std=c++11 -o Axis.out -DSHOWWINDOWS

debug:
	rm -rf ./errorLogs/err_debug.txt
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -opencv_gpu -Wall -std=c++11 -DDEBUG -o Axis_Debug.out
green:
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DGREEN -std=c++11 -o Axis.out -DSHOWWINDOWS
red:
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DRED -std=c++11 -o Axis.out -DSHOWWINDOWS
blue:
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DBLUE -std=c++11 -o Axis.out -DSHOWWINDOWS
