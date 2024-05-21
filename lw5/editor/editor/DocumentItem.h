#pragma once
#include "ConstDocumentItem.h"

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem : public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IParagraph> paragraph)
		: CConstDocumentItem(paragraph),
		m_paragraph(paragraph)
	{}

	CDocumentItem(std::shared_ptr<IImage> image)
		: CConstDocumentItem(image),
		m_image(image)
	{}

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}

	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}
private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};