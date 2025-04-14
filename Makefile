calculator.exe: main.cpp calculator.cpp
	g++ main.cpp calculator.cpp -o calculator.exe

clean:
	rm -f calculator.exe

run:
	./calculator.exe