all:
	make folders
	make clean
	mkdir -p lib/utils/math
	rm -rf build/release/*
	
	g++ -Wall -Werror -fPIC -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	
	
	g++ -Wall -Werror -fPIC -c src/utils/network.cpp -I include/ -o lib/utils/network.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	
	
	g++ -Wall -Werror -fPIC -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o

	
	g++ -Wall -Werror -fPIC -c src/utils/math/math.cpp -I include/ -o lib/utils/math/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/math.a lib/utils/math/math.o
	
	g++ -Wall -Werror -fPIC -c src/utils/math/physics.cpp -I include/ -o lib/utils/math/physics.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/physics.a lib/utils/math/physics.o
	
	g++ -Wall -Werror -fPIC -c src/utils/math/statistics.cpp -I include/ -o lib/utils/math/statistics.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/statistics.a lib/utils/math/statistics.o
	
	g++ -Wall -Werror -fPIC -c src/utils/utils.cpp -I include/ -o lib/utils/utils.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/utils.a lib/utils/utils.o

	
	g++ -Wall -Werror src/main.cpp -I include/ -o build/release/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math/math.a lib/utils/network.a lib/utils/utils.a lib/vision/image.a -DBLUE -std=c++11

	rm lib/vision/image.o
	rm lib/utils/network.o
	rm lib/utils/logger.o
	rm lib/utils/math/math.o	

	
alldebug:
	make folders
	make clean
	rm -rf build/debug/*
	
	g++ -g -Wall -Werror -fPIC -c src/vision/image.cpp -I include/ -o lib/vision/imaged.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/imaged.a lib/vision/imaged.o
	
	g++ -g -Wall -Werror -fPIC -c src/utils/network.cpp -I include/ -o lib/utils/networkd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/networkd.a lib/utils/networkd.o
	
	g++ -g -Wall -Werror -fPIC -c src/utils/logger.cpp -I include/ -o lib/utils/loggerd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/loggerd.a lib/utils/loggerd.o
	
	g++ -g -Wall -Werror -fPIC -c src/utils/math/math.cpp -I include/ -o lib/utils/math/mathd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/mathd.a lib/utils/math/mathd.o
	
	g++ -g -Wall -Werror -fPIC -c src/utils/utils.cpp -I include/ -o lib/utils/utilsd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/utilsd.a lib/utils/utilsd.o
		
	g++ -g -Wall -Werror src/main.cpp -I include/ -o build/debug/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/loggerd.a lib/utils/mathd.a lib/utils/networkd.a lib/utils/utilsd.a lib/vision/imaged.a -DDEBUG -DBLUE -std=c++11
	
	rm lib/vision/imaged.o
	rm lib/utils/networkd.o
	rm lib/utils/loggerd.o
	rm lib/utils/mathd.o	

network:
	g++ -Wall -Werror -fPIC -c src/utils/network.cpp -I include/ -o lib/utils/network.o lib/utils/utils.a -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/network.a lib/utils/network.o
	g++ -Wall -Werror -fPIC -c src/utils/network.cpp -I include/ -o lib/utils/networkd.o lib/utils/utilsd.a -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/networkd.a lib/utils/networkd.o

utils:
	g++ -Wall -Werror -fPIC -c src/utils/utils.cpp -I include/ -o lib/utils/utils.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/utils.a lib/utils/utils.o
	g++ -Wall -Werror -fPIC -c src/utils/utils.cpp -I include/ -o lib/utils/utilsd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/utilsd.a lib/utils/utilsd.o

math:
	g++ -Wall -Werror -fPIC -c src/utils/math/math.cpp -I include/ -o lib/utils/math/math.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/math.a lib/utils/math/math.o
	g++ -Wall -Werror -fPIC -c src/utils/math/math.cpp -I include/ -o lib/utils/math/mathd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/math/mathd.a lib/utils/math/mathd.o
	
	g++ -Wall -Werror -fPIC -c src/utils/math/statistics.cpp -I include/ -o lib/utils/math/statistics.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/statistics.a lib/utils/math/statistics.o
	g++ -Wall -Werror -fPIC -c src/utils/math/statistics.cpp -I include/ -o lib/utils/math/statisticsd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/math/statisticsd.a lib/utils/math/statisticsd.o
	
	g++ -Wall -Werror -fPIC -c src/utils/math/physics.cpp -I include/ -o lib/utils/math/physics.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/math/physics.a lib/utils/math/physics.o
	g++ -Wall -Werror -fPIC -c src/utils/math/math.cpp -I include/ -o lib/utils/math/mathd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/math/physicsd.a lib/utils/math/physicsd.o
	
logger:
	g++ -Wall -Werror -fPIC -c src/utils/logger.cpp -I include/ -o lib/utils/logger.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/utils/logger.a lib/utils/logger.o
	g++ -Wall -Werror -fPIC -c src/utils/logger.cpp -I include/ -o lib/utils/loggerd.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/utils/loggerd.a lib/utils/loggerd.o

image:
	g++ -Wall -Werror -fPIC -c src/vision/image.cpp -I include/ -o lib/vision/image.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -std=c++11
	ar rcs lib/vision/image.a lib/vision/image.o
	g++ -Wall -Werror -fPIC -c src/vision/image.cpp -I include/ -o lib/vision/imaged.o -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu -DDEBUG -std=c++11
	ar rcs lib/vision/imaged.a lib/vision/imaged.o

camera:
	rm -rf build/release
	mkdir build/release
	g++ -Wall -Werror src/main.cpp -I include/ -o build/release/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math/math.a lib/utils/network.a lib/utils/utils.a lib/vision/image.a -DGREEN -std=c++11

red:
	rm -rf build/release
	mkdir build/release
	g++ -Wall -Werror src/main.cpp -I include/ -o build/release/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math/math.a lib/utils/network.a lib/utils/utils.a lib/vision/image.a -DRED -std=c++11

blue:
	rm -rf build/release
	mkdir build/release
	g++ -Wall -Werror src/main.cpp -I include/ -o build/release/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math/math.a lib/utils/network.a lib/utils/utils.a lib/vision/image.a -DBLUE -std=c++11

green:
	rm -rf build/release
	mkdir build/release
	g++ -Wall -Werror src/main.cpp -I include/ -o build/release/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/logger.a lib/utils/math/math.a lib/utils/network.a lib/utils/utils.a lib/vision/image.a -DGREEN -std=c++11
	
debug:
	rm -rf build/debug
	mkdir build/debug
	g++ -g -Wall -Werror src/main.cpp -I include/ -o build/debug/Camera -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_video -lopencv_gpu lib/utils/loggerd.a lib/utils/mathd.a lib/utils/networkd.a lib/utils/utilsd.a lib/vision/imaged.a -DDEBUG -DRED -std=c++11
clean:
	rm -rf bin/utils/*
	rm -rf bin/vision/*
	rm -rf lib/utils/*
	rm -rf lib/vision/*
folders:
	mkdir -p bin/utils
	mkdir -p bin/vision
	mkdir -p lib/utils/math
	mkdir -p lib/vision
	mkdir -p build/release
	mkdir -p build/debug
	
