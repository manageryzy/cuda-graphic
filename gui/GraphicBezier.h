#pragma once


class GraphicBezier :
	public CObject
{
	DECLARE_SERIAL(GraphicBezier)
public:

	virtual void Serialize(CArchive& ar);
	GraphicBezier();
	~GraphicBezier();
};

