prog: vector.o
	g++ -o prog reading.cpp vector.o
clean:
	rm *.o prog.exe