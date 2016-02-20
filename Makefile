all:
	rm -rf ./errorLogs/err.txt	
	g++ main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DGREEN -std=c++11 -o Axis.out		

debug:
	rm -rf ./errorLogs/err_debug.txt
	g++ -g main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -opencv_gpu -Wall -std=c++11 -DDEBUG -o Axis_Debug.out
green:
	g++ main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DGREEN -std=c++11 -o Axis.out
red:
	g++ main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DRED -std=c++11 -o Axis.out
blue:
	g++ main.cpp VisualUtils.cpp -I ./include -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_features2d -lopencv_gpu -Wall -DBLUE -std=c++11 -o Axis.out
