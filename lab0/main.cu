
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>


#include <cstdio>
#include <cstdlib>
#include "SyncedMemory.h"

#define CHECK {\
	auto e = cudaDeviceSynchronize();\
	if (e != cudaSuccess) {\
		printf("At " __FILE__ ":%d, %s\n", __LINE__, cudaGetErrorString(e));\
		abort();\
	}\
}

const int W = 40;
const int H = 12;

__global__ void Draw(char *frame) {
	// TODO: draw more complex things here
	// Do not just submit the original file provided by the TA!
	const int y = blockIdx.y * blockDim.y + threadIdx.y;
	const int x = blockIdx.x * blockDim.x + threadIdx.x;
	int idx;
	//printf("y: %d", y);
	//printf("x: %d", x);
	if (y < H & x < W) {
		char c;
		
		if (x == W-1) {
			c = y == H-1 ? '\0' : '\n';
		}
		else if (y == 0 | y == H-1 | x == 0 | x == W-2) {
			c = ':';
		} 
		else if(y>=5 & y<=10){
			if (x==34 & y==10){
				c='#';
			}
			else if (x==34){
				c='|';
			}
			else{
				switch(y){
					case 5:
						if(x >18 & x<=22){
							c='#';
						}
						else if(x==33){
							c = '<';
						}
						else{
							c=' ';
						}
						break;
					case 6:
						if(x >16 & x<=22){
							c='#';
						}
						else{
							c=' ';
						}
						break;
					case 7:
						if(x >14 & x<=22){
							c='#';
						}
						else{
							c=' ';
						}
						break;
					case 8:
						if(x >12 & x<=22){
							c='#';
						}
						else{
							c=' ';
						}
						break;
					case 9:
						if(x >10 & x<=22){
							c='#';
						}
						else{
							c=' ';
						}
						break;
					case 10:
						if(x >8 & x<=22){
							c='#';
						}
						else{
							c=' ';
						}
						break;
				}
			}
		} 
		else {
			c = ' ';
		}
		
		frame[y*W+x] = c;
	}
}

int main(int argc, char **argv)
{
	MemoryBuffer<char> frame(W*H);
	auto frame_smem = frame.CreateSync(W*H);
	CHECK;

	Draw<<<dim3((W-1)/16+1,(H-1)/12+1), dim3(16,12)>>>(frame_smem.get_gpu_wo());
	CHECK;

	puts(frame_smem.get_cpu_ro());
	CHECK;
	system("pause");
	return 0;
}
