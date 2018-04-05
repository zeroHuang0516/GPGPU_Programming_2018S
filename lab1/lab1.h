#pragma once
#include <cstdint>
#include <memory>
#include <cmath>
#include <algorithm>
using std::unique_ptr;


static const unsigned W = 640;
static const unsigned H = 480;
static const unsigned NFRAME = 240;

int p[] = { 151,160,137,91,90,15,
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };

int *perm = new int[W*H / 2];

void init() {
	for (int i = 0; i < W*H / 2; i++) {
		perm[i] = p[i & 255];
	}
};

struct Lab1VideoInfo {
	unsigned w, h, n_frame;
	unsigned fps_n, fps_d;
};

class Lab1VideoGenerator {
	struct Impl{
		int t;
		Impl(): t(0){}
	};
	
public:
	Impl* impl;
	Lab1VideoGenerator(){
		impl = new Impl;
		
	};  
	~Lab1VideoGenerator(){};
	void get_info(Lab1VideoInfo &info){
	info.w = W;
	info.h = H;
	info.n_frame = NFRAME;
	// fps = 24/1 = 24
	info.fps_n = 24;
	info.fps_d = 1; 
	}

	void draw_square(uint8_t *yuv, int start_i, int start_j,int time) {
		if (time > 200) {
			if ((start_i == 40 & start_j == 160)| (start_i == 40 & start_j == 240)| \
				(start_i == 40 & start_j == 280)| (start_i == 40 & start_j == 320)|\
				(start_i == 80 & start_j == 160)| (start_i == 80 & start_j == 240)|\
				(start_i == 80 & start_j == 320)| (start_i == 120 & start_j == 160) | \
				(start_i == 120 & start_j == 200) |(start_i == 120 & start_j == 240) |\
				(start_i == 120 & start_j == 320) |\
				
				(start_i == 200 & start_j == 160)|\
				(start_i == 200 & start_j == 200) |(start_i == 200 & start_j == 240) |\
				(start_i == 200 & start_j == 280) |(start_i == 200 & start_j == 320)|\
				(start_i == 240 & start_j == 160)| (start_i == 240 & start_j == 320)|\
				(start_i == 280 & start_j == 160)| (start_i == 280 & start_j == 200) |\
				(start_i == 280 & start_j == 240) | (start_i == 280 & start_j == 280)|\
				(start_i == 280 & start_j == 320) |\
				
				(start_i == 360 & start_j == 160) |\
				(start_i == 400 & start_j == 160) | (start_i == 400 & start_j == 200) | \
				(start_i == 400 & start_j == 240) | (start_i == 400 & start_j == 280) |\
				(start_i == 400 & start_j == 320)|\
				
				(start_i == 480 & start_j == 160)|\
				(start_i == 480 & start_j == 200)| (start_i == 480 & start_j == 240)|\
				(start_i == 480 & start_j == 280)| (start_i == 480 & start_j == 320)|\
				(start_i == 520 & start_j == 160)|(start_i == 520 & start_j == 240)|\
				(start_i == 520 & start_j == 320)| (start_i == 560 & start_j == 160)|\
				(start_i == 560 & start_j == 200)| (start_i == 560 & start_j == 240)|\
				(start_i == 560 & start_j == 280)| (start_i == 560 & start_j == 320)) {
				for (int k = 0; k < 30; k++) {
					for (int q = 0; q < 30; q++) {
						int hello = (rand() % (W*H / 2));
						//setup Y value
						cudaMemset(yuv + (start_i + k + ((start_j + q)*W)), 30, 1 * 1);
						//setup U value
						cudaMemset(yuv + W*H + ((start_i + k) / 2 + ((start_j + q) / 2)*(W / 2)), 174+ perm[hello]*0.1, 1 * 1);
						//setup V value
						cudaMemset(yuv + W*H + W*H / 4 + ((start_i + k) / 2 + ((start_j + q) / 2)*(W / 2)), 147 + perm[hello] * 0.1, 1 * 1);
					}
				}
			}			
		}
		else {
			int haha = 4.19*time*(rand() % 10) / 3 / 10;
			int tmp = (rand() % (W*H / 2));
			for (int k = 0; k < 30; k++) {
				for (int q = 0; q < 30; q++) {
					//setup Y value
					cudaMemset(yuv + (start_i + k + ((start_j + q)*W)), time * 255 / NFRAME, 1 * 1);
					//setup U value
					cudaMemset(yuv + W*H + ((start_i + k) / 2 + ((start_j + q) / 2)*(W / 2)), haha+0.05*perm[tmp], 1 * 1);
					//setup V value
					cudaMemset(yuv + W*H + W*H / 4 + ((start_i + k) / 2 + ((start_j + q) / 2)*(W / 2)), 255- perm[tmp]*0.1, 1 * 1);
				}

			}
		}
		
	}
	void Generate(uint8_t *yuv) {
	/*cudaMemset(yuv, (impl->t)*255/NFRAME, W*H);
	cudaMemset(yuv+W*H, 128, W*H/2);
	++(impl->t);*/
		/*
		static bool first_time = true;
		if (first_time)
		{
			cudaMemset(yuv, 0, W*H);
			cudaMemset(yuv + W*H, 128, W*H / 4);
			cudaMemset(yuv + (W*H) + (W*H / 4), 128, W*H / 4);
			RainFall(yuv);
			first_time = false;
		}
		else
		{
			RainFall(yuv);
		}*/
		/*
		int center[2] = { 320, 240 };
		int radius = impl->t;
		for (int i = (center[0] - radius); i <= (center[0] + radius); i++) {
			for (int j = (center[1] - radius); j <= (center[1] + radius); j++) {
				int len = (i - center[0]) * (i - center[0]) + (j - center[1]) * (j - center[1]);
				if (len <= (radius * radius)) {
					//setup Y value
					cudaMemset(yuv + (i + (j*W)), 0.299 * 255, 1 * 1);
					//setup U value
					cudaMemset(yuv + W*H + (i / 2 + (j / 2)*(W / 2)), -0.169 * 255 + 128, 1 * 1);
					//setup V value
					cudaMemset(yuv + W*H + W*H / 4 + (i / 2 + (j / 2)*(W / 2)), 0.5 * 255 + 128, 1 * 1);
				}
			}
		}*/

		std::random_shuffle(p, p + 256);
		init();
		
		if ((impl->t) == 0) {
			//setup Y value
			cudaMemset(yuv, 0, W*H);
			//setup U value
			cudaMemset(yuv + W * H, 128, W*H / 4);
			//setup V value
			cudaMemset(yuv + W*H + W*H / 4, 128, W*H / 4);
		}
		int i_idx = 0;
		int j_idx = 0;
		int count = 0;

		
		/*
		draw_square(yuv, i_idx, j_idx);
		draw_square(yuv, i_idx, j_idx+40);
		draw_square(yuv, i_idx, j_idx + 80);
		draw_square(yuv, i_idx, j_idx + 120);
		draw_square(yuv, i_idx, j_idx + 160);
		draw_square(yuv, i_idx, j_idx + 200);
		draw_square(yuv, i_idx, j_idx + 240);
		draw_square(yuv, i_idx, j_idx + 280);
		draw_square(yuv, i_idx, j_idx + 320);
		draw_square(yuv, i_idx, j_idx + 360);
		draw_square(yuv, i_idx, j_idx + 400);
		draw_square(yuv, i_idx, j_idx + 440);
		draw_square(yuv, i_idx+40, j_idx + 200);
		draw_square(yuv, i_idx+40, j_idx);
		draw_square(yuv, i_idx + 80, j_idx);
		draw_square(yuv, i_idx + 120, j_idx);
		draw_square(yuv, i_idx + 160, j_idx);
		*/
		for (int i = 0; i < 16; i++) {
			i_idx = 40 * i;
			for (int j = 0; j < 12; j++) {
				j_idx = 40 * j;
				draw_square(yuv,i_idx, j_idx,impl->t);
			}
			
		}
		++(impl->t);
		/*
		static bool first_time = true;
		if (first_time)
		{
			cudaMemset(yuv, 0, W*H);
			cudaMemset(yuv + W*H, 128, W*H / 4);
			cudaMemset(yuv + (W*H) + (W*H / 4), 128, W*H / 4);
			RainFall(yuv);
			first_time = false;
		}
		else
		{
			RainFall(yuv);
		}
		*/
	}
};