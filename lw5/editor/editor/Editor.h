#pragma once
#include <string>
#include "CDocument.h"
#include "Menu.h"

class CEditor
{
public:
	CEditor();
	void Run();
private:
	void InsertParagraph(std::istream& in) const;
	void InsertImage(std::istream& in) const;
	void SetTitle(std::istream& in);
	void ShowList() const;
	void ReplaceText(std::istream& in) const;
	void ResizeImage(std::istream& in) const;
	void DeleteItem(std::istream& in) const;
	void Help() const;
	void Undo() const;
	void Redo() const;
	void Save(std::istream& in) const;
	void Exit();

	std::optional<size_t> StringToNum(std::string& posStr) const;

	CMenu m_menu;
	std::unique_ptr<IDocument> m_document;
};