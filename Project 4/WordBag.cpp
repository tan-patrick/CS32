#include "provided.h"
#include <string>
#include "MyMap.h"
using namespace std;

class WordBagImpl
{
public:
    WordBagImpl(const string& text);
    bool getFirstWord(string& word, int& count);
    bool getNextWord(string& word, int& count);
private:
	MyMap<string, int> wordMap;
};

WordBagImpl::WordBagImpl(const string& text) //Constructs a wordbag; O(N log N)
{
	Tokenizer map(text);
	string w;
	int* check;
	while(map.getNextToken(w)) // O(N)
	{
		strToLower(w);
		check = wordMap.find(w); // O(log N)
		if(check == NULL)
			wordMap.associate(w, 1); // O(log N)
		else
			wordMap.associate(w, *check + 1); // O(log N)
	}
}

bool WordBagImpl::getFirstWord(string& word, int& count) //sends the first word and the number of times it appears
{
	int* pass;
	pass = wordMap.getFirst(word);
	if(pass == NULL)
	    return false;
	count = *pass;
	return true;
}

bool WordBagImpl::getNextWord(string& word, int& count) //sends the next word and the number of times it appears
{
	int* pass;
	pass = wordMap.getNext(word);
	if(pass == NULL)
	    return false;
	count = *pass;	
	return true;
}

//******************** WordBag functions *******************************

// These functions simply delegate to WordBagImpl's functions.
// You probably don't want to change any of this code.

WordBag::WordBag(const std::string& text)
{
    m_impl = new WordBagImpl(text);
}

WordBag::~WordBag()
{
    delete m_impl;
}

bool WordBag::getFirstWord(string& word, int& count)
{
    return m_impl->getFirstWord(word, count);
}

bool WordBag::getNextWord(string& word, int& count)
{
    return m_impl->getNextWord(word, count);
}
