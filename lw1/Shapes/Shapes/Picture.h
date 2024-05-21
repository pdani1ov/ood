#pragma once
#include <unordered_map>

#include "ICanvas.h"
#include "Shape.h"

class CPicture
{
public:
	CPicture(std::shared_ptr<ICanvas>&& canvas)
		: m_canvas(std::move(canvas))
	{}

	void AddShape(const std::string& id, std::unique_ptr<CShape>&& shape)
	{
		if (m_shapes.contains(id))
		{
			throw std::runtime_error("Shape with id(" + id + ") already exists");
		}
		m_shapes.insert({ id, std::move(shape) });
		m_insertOrderedIds.push_back(id);
	}

	void DeleteShape(const std::string& id)
	{
		EnsureElementExists(id);
		std::erase(m_insertOrderedIds, id);
		m_shapes.erase(id);
	}


	std::unique_ptr<CShape>& GetShape(const std::string& id)
	{
		EnsureElementExists(id);
		return m_shapes[id];
	}

	void ShowList(std::ostream& out)
	{
		if (m_insertOrderedIds.empty())
		{
			out << "List is empty" << std::endl;
			return;
		}

		int num = 1;
		for (const auto& id : m_insertOrderedIds)
		{
			out << std::to_string(num++) << ". " << id << " "
				<< m_shapes[id]->GetType() << " " << m_shapes[id]->GetColor().GetHex() << " "
				<< m_shapes[id]->GetShapeInfo() << std::endl;
		}
	}

	void DrawShape(const std::string& id)
	{
		EnsureElementExists(id);
		m_shapes[id]->Draw(*m_canvas.get());
	}

	void MovePicture(const Point& delta)
	{
		for (const auto& id : m_insertOrderedIds)
		{
			m_shapes[id]->Move(delta);
		}
	}

	void DrawPicture()
	{
		for (const auto& id : m_insertOrderedIds)
		{
			m_shapes[id]->Draw(*m_canvas.get());
		}
	}
private:
	void EnsureElementExists(const std::string& id) const
	{
		if (!m_shapes.contains(id))
		{
			throw std::runtime_error("Shape does not exists " + id);
		}
	}

	std::vector<std::string> m_insertOrderedIds;
	std::unordered_map<std::string, std::unique_ptr<CShape>> m_shapes;
	std::shared_ptr<ICanvas> m_canvas;
};