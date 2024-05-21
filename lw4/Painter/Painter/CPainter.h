#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft const& draft, ICanvas& canvas) const
	{
		unsigned countOfShapes = draft.GetShapeCount();

		for (unsigned i = 0; i < countOfShapes; i++)
		{
			ShapePtr shapePtr = draft.GetShape(i);
			shapePtr->Draw(canvas);
		}
	}
};