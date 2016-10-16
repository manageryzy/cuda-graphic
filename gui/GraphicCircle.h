#pragma once

class GraphicCircle :
	public CObject
{
	DECLARE_SERIAL(GraphicCircle)
public:

	virtual void Serialize(CArchive& ar);
	GraphicCircle();
	~GraphicCircle();
};

