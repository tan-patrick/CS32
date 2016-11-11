#include "provided.h"
#include <iostream>
using namespace std;

void foo(const string& webPageContents)
{
	WordBag wb(webPageContents);
	string word;
	int count;
	bool gotAWord = wb.getFirstWord(word, count);
	while (gotAWord)
	{
	cout << "The word " << word << " occurs " << count
	<< " times" << endl;
	gotAWord = wb.getNextWord(word,count);
	}
}

int main()
{
    WordBag wb("<html>I’m livin’ 2 love hash tables, I say.</html>");
	string word;
	int count;
	bool gotAWord = wb.getFirstWord(word, count);
	while (gotAWord)
	{
	cout << "The word " << word << " occurs " << count
	<< " times" << endl;
	gotAWord = wb.getNextWord(word,count);
	}
}
