#pragma once

#include "Menu.h"
#include "Picture.h"
#include "Canvas.h"
#include "CircleStrategy.h"
#include "LineStrategy.h"
#include "RectangleStrategy.h"
#include "TextStrategy.h"
#include "TriangleStrategy.h"

class CPictureController
{
public:
	CPictureController(const std::string& fileName);
	void Run();
private:
	void Exit();
	void AddShape(std::istream& in);
	void MoveShape(std::istream& in);
	void MovePicture(std::istream& in);
	void DeleteShape(std::istream& in);
	void ShowList();
	void ChangeColor(std::istream& in);
	void ChangeShape(std::istream& in);
	void DrawShape(std::istream& in);
	void DrawPicture(std::istream& in);

	std::unique_ptr<IShapeStrategy> CreateStrategy(std::istream& in, std::string& type);
	CCircleStrategy CreateCircleStrategy(std::istream& in);
	CLineStrategy CreateLineStrategy(std::istream& in);
	CRectangleStrategy CreateRectangleStrategy(std::istream& in);
	CTextStrategy CreateTextStrategy(std::istream& in);
	CTriangleStrategy CreateTriangleStrategy(std::istream& in);

	CMenu m_menu;
	std::shared_ptr<CPicture> m_picture;
};