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
)
{
	float x = setting_dev->camX;
	float y = setting_dev->camY;
	float scaleX = setting_dev->scaleX;
	float scaleY = setting_dev->scaleY;

	points_dev[blockIdx.x].x -= x;
	points_dev[blockIdx.x].y -= y;
	points_dev[blockIdx.x].x *+ scaleX;
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

	cudaStatus = cudaMemcpy(points_dev, points, pointCount * sizeof(GraphicBasicPoint), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}

	cudaStatus = cudaMemcpy(fillColor_dev, fillColor, graphicCount * sizeof(DWORD), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}


	cudaStatus = cudaMemcpy(startPos_dev, startPos, graphicCount * sizeof(int), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "cudaMemcpy failed!");
		return false;
	}

	transformKernel <<<graphicCount, 1 >>> (setting_dev, points_dev);
	cudaStatus = cudaGetLastError();
	if (cudaStatus != cudaSuccess) {
		fprintf(stderr, "transform Kernel launch failed: %s\n", cudaGetErrorString(cudaStatus));
		goto Error;
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