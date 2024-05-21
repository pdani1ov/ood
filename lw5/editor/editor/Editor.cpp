#include "Editor.h"
#include <functional>

CEditor::CEditor()
	:m_document(std::make_unique<CDocument>())
{
	auto insertParagraph = [this](std::istream& in) { this->InsertParagraph(in); };
	auto insertImage = [this](std::istream& in) { this->InsertImage(in); };
	auto setTitle = [this](std::istream& in) { this->SetTitle(in); };
	auto showList = [this](std::istream&) { ShowList(); };
	auto replaceText = [this](std::istream& in) { this->ReplaceText(in); };
	auto resizeImage = [this](std::istream& in) { this->ResizeImage(in); };
	auto deleteItem = [this](std::istream& in) { this->DeleteItem(in); };
	auto help = [this](std::istream&) { m_menu.ShowInstructions(); };
	auto undo = [this](std::istream&) { this->Undo(); };
	auto redo = [this](std::istream&) { this->Redo(); };
	auto save = [this](std::istream& in) { this->Save(in); };
	auto exit = [this](std::istream&) {this->Exit(); };

	m_menu.AddItem("insertParagraph", "Insert paragraph. Args: <position> | end < text>", insertParagraph);
	m_menu.AddItem("insertImage", "Insert image. Args: <position>|end <width> <height> <path>", insertImage);
	m_menu.AddItem("setTitle", "Changes title. Args: <new title>", setTitle);
	m_menu.AddItem("showList", "Show document", showList);
	m_menu.AddItem("replaceText", "Replace text. Args: <position> <text>", replaceText);
	m_menu.AddItem("resizeImage", "Resize image. Args: <position> <width> <height>", resizeImage);
	m_menu.AddItem("deleteItem", "Delete item. Args: <position>", deleteItem);
	m_menu.AddItem("help", "Help", help);
	m_menu.AddItem("undo", "Undo command", undo);
	m_menu.AddItem("redo", "Redo command", redo);
	m_menu.AddItem("save", "Save document to html file. Args: <path>", save);
	m_menu.AddItem("exit", "Exit", exit);
}

void CEditor::Run()
{
	m_menu.Run();
}

void CEditor::InsertParagraph(std::istream& in) const
{
	std::string posStr;
	std::string text;

	in >> posStr;

	if (posStr.size() == 0)
	{
		throw std::invalid_argument("Insert paragraph: invalid argument");
	}

	getline(in, text);

	if (posStr == "end")
	{
		m_document->InsertParagraph(text);
	}
	else
	{
		std::optional<size_t> pos = StringToNum(posStr);
		if (pos != std::nullopt)
		{
			m_document->InsertParagraph(text, pos);
		}
		else
		{
			throw std::invalid_argument("Insert paragraph: invalid argument");
		}
	}
}

void CEditor::InsertImage(std::istream& in) const
{
	std::string posStr;
	std::string widthStr;
	std::string heightStr;
	std::string path;

	in >> posStr >> widthStr >> heightStr >> path;

	std::optional<int> pos = StringToNum(posStr);

	if (posStr != "end" && pos == std::nullopt)
	{
		throw std::invalid_argument("Insert image : invalid argument");
	}

	std::optional<int> width = StringToNum(widthStr);
	std::optional<int> height = StringToNum(heightStr);

	if (width != std::nullopt && height != std::nullopt)
	{
		m_document->InsertImage(path, width.value(), height.value(), pos);
	}
	else
	{
		throw std::invalid_argument("Insert image : invalid argument");
	}
}

void CEditor::SetTitle(std::istream& in)
{
	std::string title;
	if (getline(in, title))
	{
		m_document->SetTitle(title);
	}
}

void CEditor::ShowList() const
{
	std::cout << "Title: " << m_document->GetTitle() << std::endl;
	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		const auto item = m_document->GetItem(i);

		std::cout << std::to_string(i) << ". ";

		std::shared_ptr<IParagraph> paragraph = item->GetParagraph();
		std::shared_ptr<IImage> image = item->GetImage();

		if (image != nullptr)
		{
			std::cout << image->GetWidth() << " " << image->GetHeight() << " " << image->GetPath().string() << std::endl;
		}
		else if (paragraph != nullptr)
		{
			std::cout << paragraph->GetText() << std::endl;
		}
	}
}

void CEditor::ReplaceText(std::istream& in) const
{
	std::string posStr;
	std::string text;

	in >> posStr;

	std::optional<size_t> pos = StringToNum(posStr);

	if (!pos)
	{
		throw std::invalid_argument("Replace text: invalid argument");
	}

	getline(in, text);

	std::shared_ptr<IParagraph> paragraph = m_document->GetItem(pos.value())->GetParagraph();

	if (paragraph == nullptr)
	{
		throw std::logic_error("Item at this position is not a paragraph");
	}

	paragraph->SetText(text);
}

void CEditor::ResizeImage(std::istream& in) const
{
	std::string posStr;
	std::string widthStr;
	std::string heightStr;

	in >> posStr >> widthStr >> heightStr;

	std::optional<size_t> pos = StringToNum(posStr);

	if (pos == std::nullopt)
	{
		throw std::invalid_argument("Resize image : invalid argument");
	}

	std::optional<int> width = StringToNum(widthStr);
	std::optional<int> height = StringToNum(heightStr);

	if (width == std::nullopt || height == std::nullopt)
	{
		throw std::invalid_argument("Resize image : invalid argument");
	}

	std::shared_ptr<IImage> image = m_document->GetItem(pos.value())->GetImage();

	if (image == nullptr)
	{
		throw std::logic_error("Item at this position is not a iamge");
	}

	image->Resize(width.value(), height.value());
}

void CEditor::DeleteItem(std::istream& in) const
{
	std::string posStr;

	in >> posStr;

	std::optional<size_t> pos = StringToNum(posStr);

	if (!pos)
	{
		throw std::invalid_argument("Delete item: invalid argument");
	}
	else
	{
		m_document->DeleteItem(pos.value());
	}
}

void CEditor::Help() const
{
	m_menu.ShowInstructions();
}

void CEditor::Undo() const
{
	m_document->Undo();
}

void CEditor::Redo() const
{
	m_document->Redo();
}

void CEditor::Save(std::istream& in) const
{
	std::string path;

	in >> path;

	if (path.size() == 0)
	{
		throw std::invalid_argument("Save: invalid argument");
	}

	std::filesystem::path file(path);
	if (file.extension() != ".html")
	{
		throw std::invalid_argument("Save: invalid argument");
	}

	m_document->Save(path);
}

std::optional<size_t> CEditor::StringToNum(std::string& posStr) const
{
	try
	{
		size_t pos = std::stoi(posStr);
		return pos;
	}
	catch (...)
	{
		return std::nullopt;
	}
}

void CEditor::Exit()
{
	m_menu.Exit();
}