#include "Dictionary.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <iterator>
#include <numeric>

using namespace std;
using namespace experimental::filesystem;

constexpr const char* DictFileName{ "GermDict.txt" };
constexpr const char* DictBackupFile{ "GermDict.bak" };

Dictionary g_Dictionary;

//void InitialaiseDict()
//{
//	if (!exists(DictFileName))
//	{
//		return;
//	}
//
//	cout << "Using dictionary from: " << system_complete(DictFileName) << endl;
//
//	ifstream dictFile(DictFileName);
//
//	while (dictFile)
//	{
//		string germWord;
//		string englWord;
//
//		dictFile >> germWord;
//		if (!dictFile)
//		{
//			break;
//		}
//
//		dictFile >> englWord;
//		if (!dictFile)
//		{
//			break;
//		}
//
//		g_Dictionary.InsertEntry(germWord, englWord);
//	}
//	dictFile.close();
//}

bool TestOneWord(const Dictionary::Entry& entry)
{
	cout << "Translate German word \"" << entry.GermWord << "\" to English" << endl;

	string input;
	cin >> input;
	if (input == entry.EnglWord)
	{
		cout << "All right" << endl;
		return true;
	}
	cout << "False!" << endl;
	return false;
}

void Exam()
{
	int WordsNumber;
	int Questions = 0;

	cout << "Enter the number of words you'd like to learn this time: " << endl;

	cin >> WordsNumber;
	if (WordsNumber <= 0 || WordsNumber > g_Dictionary.size())
	{
		cout << "Incorrect number. Check the number of words in the dictionary and try again" << endl;
		Exam();
	}

	vector<size_t> exam_index(g_Dictionary.size());
	iota(exam_index.begin(), exam_index.end(), 0);

	random_device rd;
	mt19937 g(rd());
	shuffle(exam_index.begin(), exam_index.end(), g);

	int correct_answer = 0;

	for (auto dictIndex : exam_index)
	{
		Questions++;

		if (TestOneWord(g_Dictionary[dictIndex]))
		{
			correct_answer++;
		}

		WordsNumber--;

		if (WordsNumber == 0)
		{
			break;
		}
	}
		cout << correct_answer << " correct answers out of " << Questions << endl;
}

void Help()
{
	cout << "Supported commands:" << endl;
	cout << "AddWords" << endl;
	cout << "Exam" << endl;
	cout << "Exit" << endl;
	cout << "Help" << endl;
	cout << "ClearDict" << endl;
	cout << "ViewDict" << endl;
	cout << "SaveDict" << endl;
}

void AddWords()
{
	if (exists(DictBackupFile))
	{
		remove(DictBackupFile);
	}

	if (exists(DictFileName))
	{
		copy(DictFileName, DictBackupFile);
	}

	cout << "Enter word pairs 'Deutsch English'" << endl;
	cout << "Type period to stop entring words" << endl;

	for (;;)
	{
		cout << "  : ";

		string germWord;
		cin >> germWord;

		if (germWord == ".")
		{
			cout << "New words succesfully added";
			return;
		}

		string englWord;
		cin >> englWord;


		// ToDo: validate pair of words
		g_Dictionary.InsertEntry(germWord, englWord);

		ofstream dictFile(DictFileName, exists(DictFileName) ? ofstream::app : ofstream::out);

		dictFile << germWord << " ";
		dictFile << englWord << endl;

		dictFile.close();
	}
}

void ClearDict()
{
	ofstream dictFile(DictFileName, ofstream::trunc);
	cout << "The dictionary is empty now. Would you like to add new words? Then type 'AddWords'" << endl;
}

void ViewDict()
{
	cout << "Dictionary contains" << endl;

	for (const auto& dictEntry : g_Dictionary)
	{
		cout << dictEntry << endl;
	}
}

// void ChooseDict()
//{
//	 string DictName;
//	 cout << "Please, choose dictionary. Write 'GermDict' or 'LatDict'" << endl;
//	 cin >> DictName;
//
//	 if (DictName == GermDict)
//	 {
//		constexpr const char* DictFileName{ "GermDict.txt" };
//		constexpr const char* DictBackupFile{ "GermDict.bak" };
//	 }
//
//	 if (DictName == LatDict)
//	 {
//

int main(int c, const char* v[])
{
	if (c >= 2)
	{
		g_Dictionary.Load(v[1]);
	}

	for (;;)
	{
		cout << endl << "Dict mgr> ";
		string command;
		cin >> command;

		if (command == "Exit")
		{
			break;
		}
		if (command == "Help")
		{
			Help();
			continue;
		}
		if (command == "Exam")
		{
			Exam();
			continue;
		}
		if (command == "AddWords")
		{
			AddWords();
			continue;
		}
		if (command == "ClearDict")
		{
			ClearDict();
			continue;
		}
		if (command == "ViewDict")
		{
			ViewDict();
			continue;
		}

		//if (command == "SaveDict")
		//{
		//	cout << "Enter new DictName and type 'save as', or just type 'save'" << endl;
		//	string saving;
		//	cin >> saving;

		//	if (saving == "save as")
		//	{
		//		string NewName;
		//		cin >> NewName;
		//		g_Dictionary.save_as(NewName);
		//	}
		//	continue;
		//}

		cout << "Invalid command. Use Help." << endl;
	}

    return 0;
}

