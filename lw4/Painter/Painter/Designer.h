#pragma once
#include <string>
#include <sstream>
#include "IShapeFactory.h"
#include "PictureDraft.h"

class CDesigner
{
public:
	CDesigner(IShapeFactory& factory)
		:m_factory(factory)
	{}

	CPictureDraft CreateDraft(std::istream& inputData)
	{
		CPictureDraft draft;
		std::string description;

		while (getline(inputData, description))
		{
			draft.AddShape(m_factory.CreateShape(description));
		}

		return draft;
	}

private:
	IShapeFactory& m_factory;
};