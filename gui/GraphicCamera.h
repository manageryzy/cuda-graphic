#pragma once


class GraphicCamera
{
public:
	GUID_ guid;
	float x, y, scale;

	void Serialize(CArchive& ar);
	GraphicCamera();

	D2D1_POINT_2F inline _move(D2D1_POINT_2F pt, D2D1_POINT_2F move)
	{
		D2D1_POINT_2F out;
		out.x = pt.x + move.x;
		out.y = pt.y + move.y;
		return out;
	}

	D2D1_POINT_2F inline _rotate(D2D1_POINT_2F pt,float t)
	{
		D2D1_POINT_2F out;
		out.x = pt.x * cosf(t) - pt.y * sinf(t);
		out.y = pt.x * sinf(t) + pt.y * cosf(t);
		return out;
	}

	D2D1_POINT_2F inline _scale(D2D1_POINT_2F pt, float s)
	{
		D2D1_POINT_2F out;
		out.x = s * pt.x;
		out.y = s * pt.y;
		return out;
	}

	D2D1_POINT_2F inline toCameraView(D2D1_POINT_2F pt)
	{
		pt.x -= x;
		pt.y -= y;

		pt = _scale(pt, scale);

		return pt;
	}
	D2D1_POINT_2F inline toCameraView(float x, float y)
	{
		D2D1_POINT_2F pt;
		pt.x = x;
		pt.y = y;
		return toCameraView(pt);
	}
	D2D1_POINT_2F inline toWorld(D2D1_POINT_2F pt)
	{
		pt = _scale(pt, 1 / scale);
		pt.x += x;
		pt.y += y;

		return pt;
	}
	D2D1_POINT_2F inline toWorld(float x, float y)
	{
		D2D1_POINT_2F pt;
		pt.x = x;
		pt.y = y;

		return toWorld(pt);
	}
};