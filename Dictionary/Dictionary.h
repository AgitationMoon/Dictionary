#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <exception>
#include <filesystem>

class Dictionary
{
public:
	struct Entry
	{
		std::string GermWord;
		std::string EnglWord;

		Entry(std::string germWord, std::string englWord)
			: GermWord{germWord}, EnglWord{englWord}
		{}
	};

	void Load(std::string fileName);

	void InsertEntry (std::string germWord, std::string englWord)
	{
		m_dictionary.emplace_back(germWord, englWord);
	}

	void save()
	{

	}

	//void save_as(string NewName)
	//{
	//	//if (exists(DictFileName))
	//	//{
	//	//	copy(DictFileName, NewName);
	//	//}

	//}

	using const_iterator = std::vector<Entry>::const_iterator;

	const_iterator begin() const
	{
		return m_dictionary.cbegin();
	}

	const_iterator end() const
	{
		return m_dictionary.cend();
	}

	size_t size() const
	{
		return m_dictionary.size();
	}

private:
	std::string m_fileName;
	std::vector<Entry> m_dictionary;
};

inline std::ostream& operator<< (std::ostream& os, const Dictionary::Entry& entry)
{
	os << entry.GermWord << " " << entry.EnglWord;
	
	return os;
}