#include "../../../catch/catch.hpp"
#include "../editor/CDocument.h"
#include <iostream>

TEST_CASE("Check work of document operations")
{
	CDocument document;
	//init
	REQUIRE(!document.CanRedo());
	REQUIRE(!document.CanUndo());
	REQUIRE_NOTHROW(document.Redo());
	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(document.GetItemsCount() == 0);
	REQUIRE_THROWS_AS(document.GetItem(0), std::logic_error);
	REQUIRE(document.GetTitle() == "");


	//Check width and height range
	REQUIRE_THROWS(document.InsertImage("testImage.jpg", 10001, 50));
	REQUIRE_THROWS(document.InsertImage("testImage.jpg", 100, 10001));

	//Check insert image
	REQUIRE_THROWS(document.InsertImage("randomString", 100, 100));
	REQUIRE_NOTHROW(document.InsertImage("testImage.jpg", 100, 100));
	REQUIRE(document.GetItemsCount() == 1);
	std::shared_ptr<CDocumentItem> img = document.GetItem(0);
	REQUIRE(img->GetImage() != nullptr);
	REQUIRE(img->GetParagraph() == nullptr);
	REQUIRE(img->GetImage()->GetHeight() == 100);
	REQUIRE(img->GetImage()->GetWidth() == 100);

	//Check resize image
	REQUIRE_THROWS(img->GetImage()->Resize(10001, 50));
	REQUIRE_THROWS(img->GetImage()->Resize(50, 10001));
	REQUIRE_NOTHROW(img->GetImage()->Resize(50, 50));
	REQUIRE(img->GetImage()->GetHeight() == 50);
	REQUIRE(img->GetImage()->GetWidth() == 50);

	//Check undo and redo

	REQUIRE(document.CanUndo());
	REQUIRE(!document.CanRedo());

	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(document.CanUndo());
	REQUIRE(document.CanRedo());
	REQUIRE(img->GetImage()->GetHeight() == 100);
	REQUIRE(img->GetImage()->GetWidth() == 100);

	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(!document.CanUndo());
	REQUIRE(document.CanRedo());
	REQUIRE(document.GetItemsCount() == 0);

	REQUIRE_NOTHROW(document.Redo());
	REQUIRE(document.CanUndo());
	REQUIRE(document.CanRedo());
	REQUIRE(document.GetItemsCount() == 1);
	REQUIRE(img->GetImage()->GetHeight() == 100);
	REQUIRE(img->GetImage()->GetWidth() == 100);

	REQUIRE_NOTHROW(img->GetImage()->Resize(500, 500));
	REQUIRE(document.CanUndo());
	REQUIRE(!document.CanRedo());
	REQUIRE(img->GetImage()->GetHeight() == 500);
	REQUIRE(img->GetImage()->GetWidth() == 500);

	//Check insert paragraph
	REQUIRE_NOTHROW(document.InsertParagraph("hello world", 0));
	REQUIRE(document.GetItemsCount() == 2);
	std::shared_ptr<CConstDocumentItem> paragraph = document.GetItem(0);
	REQUIRE(paragraph->GetImage() == nullptr);
	REQUIRE(paragraph->GetParagraph() != nullptr);
	REQUIRE(paragraph->GetParagraph()->GetText() == "hello world");

	//Check change text
	std::shared_ptr<CDocumentItem> editableParagraph = document.GetItem(0);
	REQUIRE_NOTHROW(editableParagraph->GetParagraph()->SetText("HI WORLD!"));
	REQUIRE(editableParagraph->GetParagraph()->GetText() == "HI WORLD!");
	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(editableParagraph->GetParagraph()->GetText() == "hello world");
	REQUIRE_NOTHROW(document.Redo());
	REQUIRE_NOTHROW(editableParagraph->GetParagraph()->SetText("HI WORLD!"));

	//Check set title
	REQUIRE_NOTHROW(document.SetTitle("TITLE"));
	REQUIRE(document.GetTitle() == "TITLE");
	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(document.GetTitle() == "");
	REQUIRE_NOTHROW(document.Redo());
	REQUIRE(document.GetTitle() == "TITLE");

	//Check delete item
	REQUIRE_THROWS(document.DeleteItem(10));
	REQUIRE_NOTHROW(document.DeleteItem(0));
	REQUIRE(document.GetItemsCount() == 1);
	REQUIRE(document.GetItem(0)->GetParagraph() == nullptr);
	REQUIRE(document.GetItem(0)->GetImage() != nullptr);

	REQUIRE_NOTHROW(document.Undo());
	REQUIRE(document.GetItemsCount() == 2);
	REQUIRE(document.GetItem(0)->GetParagraph() != nullptr);
	REQUIRE(document.GetItem(0)->GetImage() == nullptr);
	REQUIRE_NOTHROW(document.DeleteItem(1));

	//Check save
	REQUIRE_NOTHROW(document.Save("test.html"));
	REQUIRE(std::filesystem::exists("test.html"));

	std::filesystem::remove_all("images");
	std::filesystem::remove("test.html");
}

TEST_CASE("Check limit of operations in history")
{
	CDocument document;

	for (int pos = 1; pos <= 11; pos++)
	{
		REQUIRE_NOTHROW(document.InsertParagraph(std::to_string(pos)));
	}

	for (int pos = 1; pos <= 11; pos++)
	{
		REQUIRE_NOTHROW(document.Undo());
	}

	REQUIRE(document.GetItemsCount() == 1);
}