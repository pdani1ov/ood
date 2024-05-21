#pragma once
#include <map>
#include <string>

const std::map<char, std::string> HTML_ENTITY_MAP = {
	{'"', "&quot;"},
	{'\'', "&apos;"},
	{'<', "&lt;"},
	{'>', "&gt;"},
	{'&', "&amp;"}
};


inline std::string HTMLEncode(const std::string& html)
{
	std::string decodedStr = "";

	//этот цикл может никогда не завершиться, если строка очень длинная
	for (auto ch : html)
	{
		auto replaceText = HTML_ENTITY_MAP.find(ch);
		if (replaceText != HTML_ENTITY_MAP.end())
		{
			decodedStr += replaceText->second;
		}
		else
		{
			decodedStr += ch;
		}
	}

	return decodedStr;
};