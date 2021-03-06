// (C) Copyright Gert-Jan de Vos and Jan Wilmans 2016.
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

// Repository at: https://github.com/djeedjay/DebugViewPP/

#include "stdafx.h"
#include "DebugView++Lib/TimelineDC.h"
#include <string>
#include <cassert>

namespace fusion {
namespace graphics {

// todo: find out how this works (DECLARE_HANDLE(HDC); 
// ::GetClientRect(m_hDC, &rect); is a compiler-time error, which is pretty cool
RECT TimelineDC::GetClientArea()
{
	RECT rect;
	GetClipBox(&rect);
	return rect;
}

void TimelineDC::DrawTextOut(const std::wstring& str, int x, int y)
{
	TextOut(x, y, str.c_str(), str.size());
}

void TimelineDC::DrawPolygon(const std::vector<POINT>& points)
{
	Polygon(points.data(), points.size());
}

void TimelineDC::DrawTimeline(const std::wstring& name, int x, int y, int width, COLORREF color)
{
	CPen pen(CreatePen(PS_SOLID, 1, color));
	SelectPen(pen);
	DrawTextOut(name, x + 15, y -15);
	Rectangle(x + s_drawTimelineMax, y, x + s_drawTimelineMax + width, y + 2);
}

void TimelineDC::DrawFlag(const std::wstring& /* tooltip */, int x, int y)
{
	MoveTo(x, y);
	LineTo(x, y - 20);
	LineTo(x + 7, y - 16);
	LineTo(x, y - 12);
}

void TimelineDC::DrawSolidFlag(const std::wstring& /* tooltip */, int x, int y)
{
	DrawPolygon({ { x, y - 20 },{ x + 7, y - 16 },{ x, y - 12 } });
	MoveTo(x, y);
	LineTo(x, y - 20);
}

void TimelineDC::DrawSolidFlag(const std::wstring& tooltip, int x, int y, COLORREF border, COLORREF fill)
{
	CPen pen(CreatePen(PS_SOLID, 1, border));
	SelectPen(pen);
	CBrush b(CreateSolidBrush(fill));
	SelectBrush(b);
	DrawSolidFlag(tooltip, x, y);
}

void TimelineDC::DrawFlag(const std::wstring& tooltip, int x, int y, COLORREF color, bool solid)
{
	CPen pen(CreatePen(PS_SOLID, 1, color));
	SelectPen(pen);
	if (solid)
		DrawSolidFlag(tooltip, x, y);
	else
		DrawFlag(tooltip, x, y);
}

} // namespace graphics
} // namespace fusion
