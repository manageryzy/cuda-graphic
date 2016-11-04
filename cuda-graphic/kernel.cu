#define __USE_CUDA_HEAD__
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

typedef unsigned long DWORD;
typedef struct GraphicBasicPoint_
{
	//store value for one frame
public:
	float x;
	float y;
	float width;
	float glowWidth;
	float shadowWidth;
	DWORD color;
	DWORD glowColor;
	DWORD shadowColor;
} GraphicBasicPoint;

typedef struct CUDARenderSetting_
{
	//store value for one frame
public:
	float camX;
	float camY;
	float scaleX;
	float scaleY;
	int sizeX;
	int sizeY;
	int graphicCount;
} CUDARenderSetting;

#include "head.cu"

__global__ void transformKernel(
	CUDARenderSetting * setting_dev,
	GraphicBasicPoint * points_dev
);

__global__ void renderKernel(
	CUDARenderSetting * setting_dev,
	GraphicBasicPoint * points_dev,
	DWORD * fillColor_dev,
	int * startPos_dev,
	DWORD * res_dev
);

DWORD inline __device__  blendColor(DWORD color1, DWORD color2);
DWORD inline __device__  gradientColor(DWORD color1, DWORD color2, float s);
float inline __device__  gradientFloat(float x, float y, float s);
float inline __device__  pointToSegDist(float x, float y, float x1, float y1, float x2, float y2);



__global__ void transformKernel(
	CUDARenderSetting * setting_dev,
	GraphicBasicPoint * points_dev
)
{
	float x = setting_dev->camX;
	float y = setting_dev->camY;
	float scaleX = setting_dev->scaleX;
	float scaleY = setting_dev->scaleY;

	points_dev[blockIdx.x].x -= x;
	points_dev[blockIdx.x].y -= y;
	points_dev[blockIdx.x].x *= scaleX;
	points_dev[blockIdx.x].y *= scaleY;
}

__global__ void renderKernel(
	CUDARenderSetting * setting_dev,
	GraphicBasicPoint * points_dev,
	DWORD * fillColor_dev,
	int * startPos_dev,
	DWORD * res_dev
)
{
	DWORD color = 0;

	float x = blockIdx.x;
	float y = blockIdx.y;

	for (int i = 0; i < setting_dev->graphicCount; i++)
	{
		for (int j = startPos_dev[i]; j < startPos_dev[i + 1] - 1; j++)
		{
			float x1 = points_dev[j].x;
			float y1 = points_dev[j].y;
			float x2 = points_dev[j + 1].x;
			float y2 = points_dev[j + 1].y;

			float distToSeg;
			float r;
			{
				float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
				float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
				r = cross / d2;
				
				if (cross <= 0)
				{
					distToSeg = sqrtf((x - x1) * (x - x1) + (y - y1) * (y - y1));
				}
				else if (cross >= d2)
				{
					distToSeg = sqrtf((x - x2) * (x - x2) + (y - y2) * (y - y2));

				}
				else
				{
					float px = x1 + (x2 - x1) * r;
					float py = y1 + (y2 - y1) * r;
					distToSeg = sqrtf((x - px) * (x - px) + (y - py) * (y - py));
				}
			}

			float point_width = gradientFloat(points_dev[j].width, points_dev[j + 1].width,r)*setting_dev->scaleX/2;

			if (distToSeg <= point_width  )
			{
				DWORD point_color = gradientColor(points_dev[j].color, points_dev[j + 1].color, r);
				color = blendColor(point_color, color);
			}
			
		}
	}
	
	res_dev[blockIdx.y * setting_dev->sizeX + blockIdx.x] = color;
	
	//res_dev[blockIdx.y * setting_dev->sizeX + blockIdx.x] = (a << 24)| (b << 16) |(g << 8) |r;
}

DWORD inline __device__  blendColor(DWORD color1,DWORD color2)
{
	unsigned char r1 = color1 & 0xFF;
	unsigned char g1 = (color1 >> 8) & 0xFF;
	unsigned char b1 = (color1 >> 16) & 0xFF;
	unsigned char a1 = (color1 >> 24) & 0xFF;
	unsigned char r2 = color2 & 0xFF;
	unsigned char g2 = (color2 >> 8) & 0xFF;
	unsigned char b2 = (color2 >> 16) & 0xFF;
	unsigned char a2 = (color2 >> 24) & 0xFF;

	unsigned char r = (r1*a1 + r2*a2) / (a1 + a2);
	unsigned char g = (g1*a1 + g2*a2) / (a1 + a2);
	unsigned char b = (b1*a1 + b2*a2) / (a1 + a2);

	return (0xFF << 24) | (b << 16) | (g << 8) | r;
}

DWORD inline __device__  gradientColor(DWORD color1, DWORD color2, float s)
{
	float s_ = 1 - s;
	int r1 = color1 & 0xFF;
	int g1 = (color1 >> 8) & 0xFF;
	int b1 = (color1 >> 16) & 0xFF;
	int a1 = (color1 >> 24) & 0xFF;
	int r2 = color2 & 0xFF;
	int g2 = (color2 >> 8) & 0xFF;
	int b2 = (color2 >> 16) & 0xFF;
	int a2 = (color2 >> 24) & 0xFF;

	unsigned char r = (r1*s + r2*s_);
	unsigned char g = (g1*s + g2*s_);
	unsigned char b = (b1*s + b2*s_);
	unsigned char a = (a1*s + a2*s_);

	return (a << 24) | (b << 16) | (g << 8) | r;
}

float inline __device__  pointToSegDist(float x, float y, float x1, float y1, float x2, float y2)
{
	float cross = (x2 - x1) * (x - x1) + (y2 - y1) * (y - y1);
	if (cross <= 0) return sqrtf((x - x1) * (x - x1) + (y - y1) * (y - y1));

	float d2 = (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);
	if (cross >= d2) return sqrtf((x - x2) * (x - x2) + (y - y2) * (y - y2));

	float r = cross / d2;
	float px = x1 + (x2 - x1) * r;
	float py = y1 + (y2 - y1) * r;

	return sqrtf((x - px) * (x - px) + (y - py) * (y - py));
}

float inline __device__  gradientFloat(float x, float y, float s)
{
	return x*s + y*(1 - s);
}


bool CUDARenderCore::init()
{
	cudaError_t cudaStatus;

	cudaStatus = cudaSetDevice(0);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaSetDevice failed!  Do you have a CUDA-capable GPU installed?");
		return false;
	}

	return true;
}



bool CUDARenderCore::render(DWORD * output,
	int height, int width,
	float camX, float camY,
	float scaleX, float scaleY,
	int graphicCount,
	int pointCount,
	GraphicBasicPoint * points,
	DWORD * fillColor,
	int * startPos
)
{
	cudaError_t cudaStatus;

	CUDARenderSetting setting;
	setting.camX = camX;
	setting.camY = camY;
	setting.graphicCount = graphicCount;
	setting.scaleX = scaleX;
	setting.scaleY = scaleY;
	setting.sizeX = width;
	setting.sizeY = height;

	CUDARenderSetting * setting_dev;
	GraphicBasicPoint * points_dev;
	DWORD * fillColor_dev;
	int * startPos_dev;
	DWORD * res_dev;

	cudaStatus = cudaMalloc((void**)&setting_dev, sizeof(CUDARenderSetting));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		return false;
	}

	cudaStatus = cudaMalloc((void**)&points_dev, (pointCount + 16) * sizeof(GraphicBasicPoint));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		return false;
	}

	cudaStatus = cudaMalloc((void**)&fillColor_dev, (graphicCount + 16) * sizeof(DWORD));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		return false;
	}

	cudaStatus = cudaMalloc((void**)&startPos_dev, (graphicCount + 16) * sizeof(int));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		return false;
	}

	cudaStatus = cudaMalloc((void**)&res_dev, height * width * sizeof(DWORD));
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMalloc failed!");
		return false;
	}

	cudaStatus = cudaMemcpy(setting_dev, &setting, sizeof(CUDARenderSetting), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}

	cudaStatus = cudaMemcpy(points_dev, points, (pointCount+16) * sizeof(GraphicBasicPoint), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}

	cudaStatus = cudaMemcpy(fillColor_dev, fillColor, (graphicCount+16) * sizeof(DWORD), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}


	cudaStatus = cudaMemcpy(startPos_dev, startPos, (graphicCount+16) * sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}

	if (graphicCount != 0)
	{
		transformKernel <<<pointCount, 1 >>> (setting_dev, points_dev);
		cudaStatus = cudaGetLastError();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "transform Kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
			goto Error;
		}

		cudaStatus = cudaDeviceSynchronize();
		if (cudaStatus != cudaSuccess) {
			fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
			goto Error;
		}
	}

	dim3 blocks(width, height);
	renderKernel <<<blocks, 1 >>> (setting_dev, points_dev, fillColor_dev, startPos_dev, res_dev);

	// Check for any errors launching the kernel
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "render Kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
	}

	// cudaDeviceSynchronize waits for the kernel to finish, and returns
	// any errors encountered during the launch.
	cudaStatus = cudaDeviceSynchronize();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaDeviceSynchronize returned error code %d after launching addKernel!\n", cudaStatus);
		goto Error;
	}

	// Copy output vector from GPU buffer to host memory.
	cudaStatus = cudaMemcpy(output, res_dev, height * width * sizeof(DWORD), cudaMemcpyDeviceToHost);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		goto Error;
	}


Error:
	cudaFree(setting_dev);
	cudaFree(points_dev);
	cudaFree(fillColor_dev);
	cudaFree(startPos_dev);
	cudaFree(res_dev);

	return cudaStatus;

}