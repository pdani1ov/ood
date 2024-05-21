#pragma once
#include "IImage.h"
#include <memory>
#include "IParagraph.h"

/*
Неизменяемый элемент документа
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

	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<const IImage> GetImage() const
	{
		return m_image;
	}

	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph() const
	{
		return m_paragraph;
	}

	virtual ~CConstDocumentItem() = default;
private:
	std::shared_ptr<const IImage> m_image;
	std::shared_ptr<const IParagraph> m_paragraph;
};