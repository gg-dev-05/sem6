all:
	g++ -c imageio.cpp -ltiff -lpng;
	g++ cube.cpp -o openglTexture -lglut -lGLU -lGL imageio.o -ltiff -lpng
	./openglTexture

clean:
	rm openglTexture