#include "Dictionary.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <exception>

using namespace std;
using namespace experimental::filesystem;

void Dictionary::Load(string fileName)
{
	m_fileName.assign(system_complete(fileName).generic_u8string());

	cout << "Using dictionary from: " << m_fileName << endl;

	ifstream dictFile(m_fileName);

	if (!dictFile.good())
	{
		throw exception{ "Could not open dictionary file" };
	}

	while (dictFile)
	{
		string germWord;
		string englWord;

		dictFile >> germWord;
		if (!dictFile)
		{
			break;
		}

		dictFile >> englWord;
		if (!dictFile)
		{
			break;
		}

		InsertEntry(germWord, englWord);
	}
	dictFile.close();

}

