#pragma once
#include <set>

class CguiDoc;
class GUID_;
typedef unsigned long DWORD;

class CUDARenderCache;
class CUDARender;

class CUDARenderCache
{
	int frame = 0;
	bool cached = false;
	DWORD * buffer = nullptr;
	CUDARender * renderer;

	void alloBuffer(int size);
	void freeBuffer();
public:
	CUDARenderCache(CUDARender * renderer);
	void change();
	void change(int frame);
	bool isCached(int frame);
	DWORD * getImage(int height, int width, int frame, float camX, float camY, float scaleX, float scaleY, CguiDoc * doc, std::set<GUID_> * selected);
};

class CUDARender
{
protected:
	static CUDARender * cudaRender;
	CUDARenderCache * cache = nullptr;
	CUDARender();
public:
	static CUDARender * getCudaRender();
	void renderScene(DWORD * output,int height,int width,int frame,float camX,float camY,float scaleX,float scaleY, CguiDoc * doc,std::set<GUID_> * selected );
	CUDARenderCache * getCache();
};
