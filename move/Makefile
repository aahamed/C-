run: move
	./move

move: move.cpp
	g++ move.cpp -o move -std=c++17

leaks: move
	leaks -atExit -- ./move | grep LEAK:

clean:
	rm move