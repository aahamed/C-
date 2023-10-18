run: sharedPtr
	./sharedPtr.exe

leaks: sharedPtr
	leaks -atExit -- ./sharedPtr.exe

sharedPtr: sharedPtr.cpp
	g++ sharedPtr.cpp -o sharedPtr.exe -std=c++17 -O0 -fno-elide-constructors

clean:
	rm *.exe