#pragma once
#include "ConstDocumentItem.h"

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
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

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage()
	{
		return m_image;
	}

	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph()
	{
		return m_paragraph;
	}
private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::shared_ptr<IImage> m_image;
};