#pragma once
#include <set>

class CguiDoc;
class GUID_;
typedef unsigned long DWORD;

class CUDARender
{
protected:
	static CUDARender * cudaRender;
	CUDARender();
public:
	static CUDARender * getCudaRender();
	void renderScene(DWORD * output,int height,int width,int frame,float camX,float camY,float scaleX,float scaleY, CguiDoc * doc,std::set<GUID_> * selected );
};
