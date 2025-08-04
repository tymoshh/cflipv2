gccv2:
	g++ app.cpp -O3 -march=native -flto -funroll-loops -fomit-frame-pointer -ffast-math -funsafe-math-optimizations -DNDEBUG -static -o a
gccv1:
	g++ -O3 -march=native -flto -funroll-loops -o a app.cpp
clangv1:
	C:\msys64\mingw64\bin\clang++.exe app.cpp
clangv2:
	C:\msys64\mingw64\bin\clang++.exe app.cpp -O3 -march=native -flto -funroll-loops -fomit-frame-pointer -ffast-math -funsafe-math-optimizations -DNDEBUG -static -o a.exe
