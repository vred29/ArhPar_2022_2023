all: homework.exe

homework.exe: homework.c _OpenCLUtil.c
	gcc -o homework homework.c _OpenCLUtil.c -L "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\lib\x64" -I "C:\Program Files\NVIDIA GPU Computing Toolkit\CUDA\v11.8\include" -lOpenCL

clean:
	del /Q /F homework.exe