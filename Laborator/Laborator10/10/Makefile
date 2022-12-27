all: helloWorld.exe ex01.exe ex02.exe ex03.exe ex04.exe ex05.exe ex06.exe ex07.exe test.exe

helloWorld.exe: helloWorld.c _OpenCLUtil.c
	gcc -o helloWorld helloWorld.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex01.exe: ex01.c _OpenCLUtil.c
	gcc -o ex01 ex01.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex02.exe: ex02.c _OpenCLUtil.c
	gcc -o ex02 ex02.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex03.exe: ex03.c _OpenCLUtil.c
	gcc -o ex03 ex03.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex04.exe: ex04.c _OpenCLUtil.c
	gcc -o ex04 ex04.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex05.exe: ex05.c _OpenCLUtil.c
	gcc -o ex05 ex05.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex06.exe: ex06.c _OpenCLUtil.c
	gcc -o ex06 ex06.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

ex07.exe: ex07.c _OpenCLUtil.c
	gcc -o ex07 ex07.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

test.exe: test.c _OpenCLUtil.c
	gcc -o test test.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL


clean:
	del /Q /F helloWorld.exe ex01.exe ex02.exe ex03.exe ex04.exe ex05.exe ex06.exe ex07.exe test.exe