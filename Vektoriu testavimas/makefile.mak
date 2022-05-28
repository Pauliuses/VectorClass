prog: funkc.o
	g++ -o prog main.cpp funkc.o
funkc:
	g++ -c funkc.cpp
clean:
	rm *.o prog.exe