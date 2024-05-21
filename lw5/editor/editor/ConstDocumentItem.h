#pragma once
#include "IImage.h"
#include <memory>
#include "IParagraph.h"

/*
������������ ������� ���������
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<IImage> image)
		:m_image(image)
	{}

	CConstDocumentItem(std::shared_ptr<IParagraph> paragraph)
		:m_paragraph(paragraph)
	{}

	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}

	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}

	virtual ~CConstDocumentItem() = default;
private:
	std::shared_ptr<const IImage> m_image;
	std::shared_ptr<const IParagraph> m_paragraph;
};