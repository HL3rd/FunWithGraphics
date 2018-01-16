# Makefile for lab 10
#   make: creates all three executables
#   make symbol: creates the symbol executable
#   same for bounce and animate
 
lab10: symbol bounce animate

symbol: symbol.cpp 
	g++ symbol.cpp gfx.o -lX11 -o symbol

bounce: bounce.cpp 
	g++ bounce.cpp gfx.o -lX11 -o bounce

animate: animate.cpp 
	g++ animate.cpp gfx.o -lX11 -o animate

clean:
	rm symbol bounce animate

