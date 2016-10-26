#pragma once
#include <vector>

typedef struct GraphicBasicPoint_ 
{
	//store value for one frame
public:
	float x;
	float y;
	DWORD color;
	float width;
	DWORD glowColor;
	float glowWidth;
	DWORD shadowColor;
	float shadowWidth;
} GraphicBasicPoint;

template<typename T>
class GraphicAttrTimeline 
{
	
public://attr
	std::vector<std::pair<int, T>> attr;
public://method
	T atFrame(int frame);
	void setAttrAtFrame(T val, int frame);
	void Serialize(CArchive& ar);
};


template<typename T>
inline T GraphicAttrTimeline<T>::atFrame(int frame)
{
	if (attr.size() == 0)
	{
		return 0;
	}

	T attr1, attr2;
	int frame1 = -1, frame2 = -1;

	for (auto it = attr.begin(); it != attr.end(); ++it)
	{
		if (frame == (*it).first)
		{
			return (*it).second;
		}
		else if (frame < (*it).first)
		{
			frame2 = (*it).first;
			attr2 = (*it).second;
		}
	}
	for (auto it = attr.end()-1; it != attr.begin(); --it)
	{
		if (frame >(*it).first)
		{
			frame1 = (*it).first;
			attr1 = (*it).second;
		}
	}

	if (frame1 == -1 && frame2 == -1)
	{
		return 0;
	}

	if (frame1 == -1)
		return attr2;

	if (frame2 == -1)
		return attr1;

	return ((frame2 - frame)*attr2 + (frame - frame1)*attr1) / (frame2 - frame1);
}

template<typename T>
inline void GraphicAttrTimeline<T>::setAttrAtFrame(T val, int frame)
{
	if (attr.size() == 0)
	{
		attr.push_back(std::pair<int, T >(frame, val ));
		return;
	}

	for (auto i = attr.begin(); i != attr.end(); ++i)
	{
		if (frame == i->first)
		{
			i->second = val;
		}
		else if (frame < i->first)
		{
			attr.insert(i, std::pair<int, T >(frame, val ));
			break;
		}
	}
}

template<typename T>
inline void GraphicAttrTimeline<T>::Serialize(CArchive & ar)
{
	if (ar.IsLoading())
	{
		int len;
		ar >> len;
		for (auto i = 0; i < len; i++)
		{
			int t;
			T val;
			ar >> t;
			ar >> val;
			setAttrAtFrame(val, t);
		}
	}
	else if(ar.IsStoring())
	{
		ar << attr.size();
		for (auto & i : attr)
		{
			ar << i.first;
			ar << i.second;
		}
	}
}

class GraphicColorTimeLine :
public	GraphicAttrTimeline<DWORD>
{
public:
	GraphicColorTimeLine();
	~GraphicColorTimeLine();
	DWORD atFrame(int frame);
protected:
	inline DWORD blendColor(DWORD color1, DWORD color2, double t)
	{
		BYTE r1, g1, b1, a1;
		BYTE r2, g2, b2, a2;
		BYTE r, g, b, a;

		r1 = GetRValue(color1);
		g1 = GetGValue(color1);
		b1 = GetBValue(color1);
		a1 = LOBYTE(color1 >> 24);

		r2 = GetRValue(color2);
		g2 = GetGValue(color2);
		b2 = GetBValue(color2);
		a2 = LOBYTE(color2 >> 24);

		r = (BYTE)(t*r1 + (1 - t)*r2);
		g = (BYTE)(t*g1 + (1 - t)*g2);
		b = (BYTE)(t*b1 + (1 - t)*b2);
		a = (BYTE)(t*a1 + (1 - t)*a2);

		DWORD color = RGB(r, g, b) | (DWORD)a << 24;

		return color;
	}

};


class GraphicPoint 
{
public :
	//frame value pair of attr
	GraphicAttrTimeline<float> x;
	GraphicAttrTimeline<float> y;
	GraphicColorTimeLine color;
	GraphicAttrTimeline<float> width;
	GraphicColorTimeLine glowColor;
	GraphicAttrTimeline<float> glowWidth;
	GraphicColorTimeLine shadowColor;
	GraphicAttrTimeline<float> shadowWidth;

	GraphicBasicPoint atFrame(int frame);

	GraphicPoint();
	GraphicPoint(const GraphicPoint & o);
	void init();

	void Serialize(CArchive& ar);
};

