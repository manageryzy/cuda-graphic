#pragma once
#ifdef __USE_CUDA_HEAD__
namespace CUDARenderCore
{
	bool init();
	cudaError_t render(DWORD * output,
		int height, int width, 
		float camX, float camY, 
		float scaleX, float scaleY,
		int graphicCount,
		int pointCount,
		GraphicBasicPoint * points,
		DWORD * fillColor,
		int * startPos
	);
}
#endif