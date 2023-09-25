LIBS=-lsfml-graphics -lsfml-window -lsfml-system

default: main.o ball.o solver.o renderer.o
	g++  main.o ball.o solver.o renderer.o -o out.exe  -Wall $(LIBS)

clear:
	rm *.o *.exe

main.o: main.cpp
	g++ -c -o main.o main.cpp -Wall $(LIBS)

ball.o: ball.cpp
	g++ -c -o ball.o ball.cpp -Wall $(LIBS)

solver.o:
	g++ -c -o solver.o solver.cpp -Wall $(LIBS)


renderer.o:
	g++ -c -o renderer.o renderer.cpp -Wall $(LIBS)

run:
	./out.exe

valgrind:
	valgrind ./out.exe




