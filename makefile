all: main.cpp mainEX2.cpp
	g++ main.cpp -o p4.out
	g++ mainEX2.cpp -o p4EX2.out

p4.out: main.cpp
	g++ main.cpp -p p4.out

p4EX2.out: mainEX2.cpp
	g++ mainEX2.cpp -o p4EX2.out

proj: p4.out plotter.py
	./p4.out
	python3 plotter.py

projEX: p4EX2.out plotter.py
	./p4EX2.out
	python3 plotter.py
