#pragma once
#include <vector>
#include <filesystem>
#include <stdexcept>
#include <random>

#include "IDocument.h"
#include "History.h"
#include "SetTextCommand.h"
#include "DeleteItemCommand.h"
#include "InsertItemCommand.h"
#include "Paragraph.h"
#include "Image.h"
#include "HTMLEncode.h"

class CDocument : public IDocument
{
public:
	std::shared_ptr<IParagraph> InsertParagraph(const std::string& text,
		std::optional<size_t> position = std::nullopt) override
	{
		CDocumentItem item(std::make_shared<CParagraph>(text, m_history));
		m_history.AddAndExecuteCommand(std::make_shared<CInsertItemCommand>(m_items, std::make_shared<CDocumentItem>(item), position));
		return item.GetParagraph();
	}

	std::shared_ptr<IImage> InsertImage(const std::string& path, int width, int height,
		std::optional<size_t> position = std::nullopt) override
	{
		if (width < 1 || width > 10000)
		{
			throw std::invalid_argument("Incorrect width of image");
		}

		if (height < 1 || height > 10000)
		{
			throw std::invalid_argument("Incorrect height of image");
		}

		if (!std::filesystem::exists(path))
		{
			throw std::logic_error("Invalid path to image");
		}

		std::string format = std::filesystem::path(path).extension().string();
		std::string newFileName = GenerateRandomFilename(format);

		if (!std::filesystem::directory_entry(SUB_FOLDER).exists())
		{
			std::filesystem::create_directory(SUB_FOLDER);
		}

		std::filesystem::copy_file(path, newFileName);

		CDocumentItem item(std::make_shared<CImage>(std::filesystem::path(newFileName), width, height, m_history));

		m_history.AddAndExecuteCommand(std::make_shared<CInsertItemCommand>(m_items, std::make_shared<CDocumentItem>(item), position));

		return item.GetImage();
	}

	size_t GetItemsCount() const override
	{
		return m_items.size();
	}

	std::shared_ptr<CConstDocumentItem> GetItem(size_t index) const override
	{
		CheckCorrectPosition(index);
		return m_items[index];
	}

	std::shared_ptr<CDocumentItem> GetItem(size_t index) override
	{
		CheckCorrectPosition(index);
		return m_items[index];
	}

	void DeleteItem(size_t index) override
	{
		m_history.AddAndExecuteCommand(std::make_shared<CDeleteItemCommand>(m_items, index));
	}

	std::string GetTitle()const override
	{
		return m_title;
	}

	void SetTitle(const std::string& title) override
	{
		m_history.AddAndExecuteCommand(std::make_shared<CSetTextCommand>(m_title, title));
	}

	bool CanUndo() const override
	{
		return m_history.CanUndo();
	}
	
	void Undo() override
	{
		m_history.Undo();
	}

	bool CanRedo() const override
	{
		return m_history.CanRedo();
	}

	void Redo() override
	{
		m_history.Redo();
	}

	void Save(const std::string& path) const override
	{	
		CopyFilesToSavePath(path);
		std::ofstream fOut(path);

		if (!fOut.is_open())
		{
			throw std::logic_error("File is not open");
		}
		
		fOut << "<!doctype html>" << std::endl
			<< "<html lang = ""ru"">" << std::endl
			<< "<head>" << std::endl
			<< "<meta charset = ""utf-8"" />" << std::endl
			<< "<title>" << HTMLEncode(m_title) << "</title>" << std::endl
			<< "<link rel = ""stylesheet"" href = ""style.css"" />" << std::endl
			<< "</head>" << std::endl
			<< "<body>" << std::endl;

		for (auto& item : m_items)
		{
			auto image = item->GetImage();
			auto paragraph = item->GetParagraph();
			if (paragraph)
			{
				fOut << "<div>" << HTMLEncode(item->GetParagraph()->GetText()) << "</div>" << std::endl;
			}
			else
			{
				fOut << "<img src="""
					<< item->GetImage()->GetPath().string()
					<< """ width=" << std::to_string(item->GetImage()->GetWidth())
					<< " height="
					<< std::to_string(item->GetImage()->GetHeight())
					<< " >" << std::endl;
			}
		}

		fOut << "</body>" << std::endl
			<< "</html>" << std::endl;

	}
private:
	const std::string SUB_FOLDER = "images";
	const char CATALOG_SEPARATOR = '/';
	const size_t FILE_NAME_LENGHT = 10;

	std::string GenerateRandomFilename(std::string format)
	{
		std::vector<char> charset({ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K',
			'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
			'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_' });

		std::default_random_engine rng(std::random_device{}());
		std::uniform_int_distribution<> dist(0, int(charset.size() - 1));

		auto getRandomChar = [charset, &dist, &rng]() {
			return charset[dist(rng)];
		};

		std::string randomFileName(FILE_NAME_LENGHT, 0);
		generate_n(randomFileName.begin(), FILE_NAME_LENGHT, getRandomChar);

		randomFileName = SUB_FOLDER + CATALOG_SEPARATOR + randomFileName + format;

		return randomFileName;
	}

	void CheckCorrectPosition(std::optional<size_t> index) const
	{
		if (index.has_value() && index >= m_items.size())
		{
			throw std::logic_error("Incorrect position");
		}
	}

	void CopyFilesToSavePath(const std::string& path) const
	{
		std::filesystem::path pathToFile(path);
		std::filesystem::path directory = pathToFile.parent_path().string() + "//" + SUB_FOLDER;

		if (std::filesystem::path(pathToFile.parent_path().string() + SUB_FOLDER) == std::filesystem::path(SUB_FOLDER))
		{
			return;
		}

		if (std::filesystem::directory_entry(pathToFile.parent_path().string() + "//" + SUB_FOLDER).exists())
		{
			std::filesystem::copy("images", pathToFile.parent_path().string() + "//" + SUB_FOLDER);
		}
		else
		{
			for (auto const& file : std::filesystem::directory_iterator(SUB_FOLDER))
			{
				std::filesystem::create_directories(directory);
				std::filesystem::copy_file(file, directory / file.path().filename().string(), std::filesystem::copy_options::overwrite_existing);
			}
		}

		std::filesystem::remove_all(SUB_FOLDER);
	}

	std::string m_title;
	std::vector<std::shared_ptr<CDocumentItem>> m_items;
	CHistory m_history;
};