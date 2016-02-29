all:
	g++ -Wall -Werror -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	rm lib/vision/image.o
	
	g++ -Wall -Werror -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	rm lib/util/network.o
	
	g++ -Wall -Werror -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	rm lib/util/logger.o
	
	g++ -Wall -Werror -c src/utils/math.cpp -I include/ -o lib/utils/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math.a lib/utils/math.o
	rm lib/utils/math.o
	
	g++ -Wall -Werror src/main.cpp -I include/ -o Camera.out -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math.a lib/utils/network.a lib/vision/image.a -DBLUE -std=c++11

debug: 
	g++ -g -Wall -Werror -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	rm lib/vision/image.o
	
	g++ -g -Wall -Werror -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	rm lib/util/network.o
	
	g++ -g -Wall -Werror -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	rm lib/util/logger.o
	
	g++ -g -Wall -Werror -c src/utils/math.cpp -I include/ -o lib/utils/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math.a lib/utils/math.o
	rm lib/utils/math.o
		
	g++ -g -Wall -Werror src/main.cpp -I include/ -o Camera.out -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math.a lib/utils/network.a lib/vision/image.a -DDEBUG -DBLUE -std=c++11
	
green:
	g++ -Wall -Werror -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	rm lib/vision/image.o
	
	g++ -Wall -Werror -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	rm lib/util/network.o
	
	g++ -Wall -Werror -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	rm lib/util/logger.o
	
	g++ -Wall -Werror -c src/utils/math.cpp -I include/ -o lib/utils/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math.a lib/utils/math.o
	rm lib/utils/math.o	
	
	g++ -Wall -Werror src/main.cpp -I include/ -o Camera.out -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math.a lib/utils/network.a lib/vision/image.a -DBLUE -std=c++11

red:
	g++ -Wall -Werror -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	rm lib/vision/image.o
	
	g++ -Wall -Werror -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	rm lib/util/network.o
	
	g++ -Wall -Werror -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	rm lib/util/logger.o
	
	g++ -Wall -Werror -c src/utils/math.cpp -I include/ -o lib/utils/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math.a lib/utils/math.o
	rm lib/utils/math.o	
	
	g++ -Wall -Werror src/main.cpp -I include/ -o Camera.out -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math.a lib/utils/network.a lib/vision/image.a -DBLUE -std=c++11


blue:
	g++ -Wall -Werror -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	rm lib/vision/image.o
	
	g++ -Wall -Werror -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	rm lib/util/network.o
	
	g++ -Wall -Werror -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	rm lib/util/logger.o
	
	g++ -Wall -Werror -c src/utils/math.cpp -I include/ -o lib/utils/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math.a lib/utils/math.o
	rm lib/utils/math.o		
	
	g++ -Wall -Werror src/main.cpp -I include/ -o Camera.out -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math.a lib/utils/network.a lib/vision/image.a -DBLUE -std=c++11


	
	