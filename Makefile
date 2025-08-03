gcc:
	g++ -O3 -march=native -flto -funroll-loops -o a app.cpp