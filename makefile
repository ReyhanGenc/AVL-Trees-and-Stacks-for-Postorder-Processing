Tum: derleme calistirma


derleme:
	g++ -I ./include/ -o ./lib/agac.o -c ./src/agac.cpp
	g++ -I ./include/ -o ./lib/yigit.o -c ./src/yigit.cpp
	g++ -I ./include/ -o ./bin/Test ./lib/agac.o ./lib/yigit.o ./src/Test.cpp

calistirma:
	./bin/Test