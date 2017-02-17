.PHONY: compile

compile: main.c; gcc -o test1 main.c -lobjc -framework AppKit -framework Cocoa

run: compile ; ./test1
