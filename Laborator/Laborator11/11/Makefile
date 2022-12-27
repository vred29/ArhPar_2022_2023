all: helloWorld.exe ex01.exe ex02.exe

helloWorld.exe: helloWorld.c _OpenCLUtil.c
	gcc -o helloWorld helloWorld.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex01.exe: ex01.c _OpenCLUtil.c
	gcc -o ex01 ex01.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex02.exe: ex02.c _OpenCLUtil.c
	gcc -o ex02 ex02.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL


clean:
	del /Q /F helloWorld.exe ex01.exe ex02.exe