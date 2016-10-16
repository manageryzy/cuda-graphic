#include "stdafx.h"
#include "GraphicStyle.h"

#define LOAD_POINT(X,Y) \
ar >> len;\
for (auto i = 0; i < len; i++)\
{\
	int t;\
	Y data;\
	ar >> t;\
	ar >> data;\
	set ## X ## AtFrame(data,t);\
}

#define STORE_POINT(X) \
ar << X ## .size();\
for (auto & p : X)\
{\
	ar << p.first;\
	ar << p.second;\
}

IMPLEMENT_SERIAL(GraphicPoint, CObject, 1)

void GraphicPoint::Serialize(CArchive & ar)
{
	int len;
	if (ar.IsLoading())
	{
		LOAD_POINT(x, float);
		LOAD_POINT(y, float);
		LOAD_POINT(color, int);
		LOAD_POINT(width, float);
		LOAD_POINT(glowColor, int);
		LOAD_POINT(glowWidth, float);
		LOAD_POINT(shadowColor, int);
		LOAD_POINT(shadowWidth, float);
	}
	else if (ar.IsStoring())
	{
		STORE_POINT(x);
		STORE_POINT(y);
		STORE_POINT(color);
		STORE_POINT(width);
		STORE_POINT(glowColor);
		STORE_POINT(glowWidth);
		STORE_POINT(shadowColor);
		STORE_POINT(shadowWidth);
	}
}

#undef STORE_POINT
#undef LOAD_POINT


//void GraphicPoint::setxAtFrame(float x, int frame)
//{
//	if (this->x.size() == 0)
//	{
//		this->x.push_back(std::pair<int, float>(frame, x));
//		return;
//	}
//
//	for (auto i = this->x.begin(); i != this->x.end(); ++i)
//	{
//		if (frame < i->first)
//		{
//			this->x.insert(i, std::pair<int, float>(frame, x));
//			break;
//		}
//	}
//}
#define POINT_SET_FRAME(X,Y) \
void GraphicPoint::set ## X ## AtFrame( Y  X , int frame)\
{\
	if (this-> ## X ## .size() == 0)\
	{\
		this-> ## X ## .push_back(std::pair<int, Y >(frame, X ));\
		return;\
	}\
\
	for (auto i = this-> ## X ## .begin(); i != this-> ## X ## .end(); ++i)\
	{\
		if (frame < i->first)\
		{\
			this-> ## X ## .insert(i, std::pair<int, Y >(frame, X ));\
			break;\
		}\
	}\
}

POINT_SET_FRAME(x, float)
POINT_SET_FRAME(y, float)
POINT_SET_FRAME(color, int)
POINT_SET_FRAME(width, float)
POINT_SET_FRAME(glowColor, int)
POINT_SET_FRAME(glowWidth, float)
POINT_SET_FRAME(shadowColor, int)
POINT_SET_FRAME(shadowWidth, float)

#undef POINT_SET_FRAME