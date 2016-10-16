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
class GraphicAttrTimeline : public CObject
{
public:
	std::vector<std::pair<int, T>> attr;
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
		if (frame < it.first)
		{
			frame2 = it.first;
			attr2 = it.second;
		}
	}
	for (auto it = attr.end(); it != attr.begin; --it)
	{
		if (frame > it.first)
		{
			frame1 = it.first;
			attr1 = it.second;
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
		if (frame < i->first)
		{
			attr.insert(i, std::pair<int, T >(frame, val ));
			break;
		}
	}
}

template<typename T>
inline void GraphicAttrTimeline<T>::Serialize(CArchive & ar)
{
	CObject::Serialize(ar);
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


class GraphicPoint :
CObject
{
public :
	//frame value pair of attr
	GraphicAttrTimeline<float> x;
	GraphicAttrTimeline<float> y;
	GraphicAttrTimeline<DWORD> color;
	GraphicAttrTimeline<float> width;
	GraphicAttrTimeline<DWORD> glowColor;
	GraphicAttrTimeline<float> glowWidth;
	GraphicAttrTimeline<DWORD> shadowColor;
	GraphicAttrTimeline<float> shadowWidth;

	GraphicBasicPoint atFrame(int frame);

	DECLARE_SERIAL(GraphicPoint)
	virtual void Serialize(CArchive& ar);
};

