all: test.exe

test.exe: test.c
	gcc -o test test.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL


clean:
	del /Q /F test.exe