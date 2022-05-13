prog: vector.o
	g++ -o prog reading.cpp vector.o
vector:
	g++ -c vector.cpp
clean:
	rm *.o prog.exe