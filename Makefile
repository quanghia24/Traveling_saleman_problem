all:
	g++ -o main main.cpp
.PHONY: clean
clean:
	rm -f main