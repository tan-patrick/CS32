#include "provided.h"
#include "MyMap.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

struct IdCount //Structure using an int id in place of a string url
{
	int id;
	int count;
};

class IndexerImpl
{
public:
    bool incorporate(string url, WordBag& wb);
    vector<UrlCount> getUrlCounts(string word);
    bool save(string filenameBase);
    bool load(string filenameBase);
private:
	MyMap<string, vector<IdCount>> urlMap;
	MyMap<string, int> urlToId;
	MyMap<int, string> idToUrl;
	vector<int> addedIds;
};

bool IndexerImpl::incorporate(string url, WordBag& wb) // Incorporates a wordbag under a given URL into the urlMap; O(W log N)
{
	int add;
	if(urlToId.find(url) != NULL)
		return false;
	else
	{
		vector<int>::iterator itr;
		do
		{
			add = rand() % 100000;
			itr = find(addedIds.begin(), addedIds.end(), add);
		}while(itr != addedIds.end());
		urlToId.associate(url, add);
		idToUrl.associate(add, url);
	}

	string word;
	int count;
	vector<IdCount> currentUrl;

	if(!wb.getFirstWord(word, count))
		return true;

	bool check;

	do
	{
		check = false;
		if(urlMap.find(word) != NULL)
		{
			currentUrl = *urlMap.find(word);
			for(int i = 0; i < currentUrl.size(); i++) //O(P), if P is the average number of URLs associated with the word
			{
				if(currentUrl[i].id == add)
				{
					check = true;
					currentUrl[i].count += count;
					urlMap.associate(word, currentUrl); //O(log N), if N is the number of words in the current index
				}
			}
			if(!check)
			{
				IdCount addNew;
				addNew.id = add;
				addNew.count = count;
				currentUrl.push_back(addNew);
				urlMap.associate(word, currentUrl); //O(log N), if N is the number of words in the current index
			}
		}
		else
		{
			currentUrl.clear();
			IdCount addNew;
			addNew.id = add;
			addNew.count = count;
			currentUrl.push_back(addNew);
			urlMap.associate(word, currentUrl);
		}
	}while(wb.getNextWord(word, count)); // O(W), where W is number of words in the wordbag
	return true;
}

vector<UrlCount> IndexerImpl::getUrlCounts(string word) //Returns the URL counts associated to a word; O(P log N)
{
	vector<UrlCount> urlCount;
	strToLower(word);
	if(urlMap.find(word) == NULL)
		return vector<UrlCount>();
	vector<IdCount> idCount = *urlMap.find(word); //O(N), given N is the number of words in the index
	for(int i = 0; i < idCount.size(); i++) //O(P), if P is the average amount of URLs associated to each word
	{
		UrlCount add;
		add.count = idCount[i].count;
		add.url = *idToUrl.find(idCount[i].id); //O(N), given N is the number of words in the index
		urlCount.push_back(add);
	}
	return urlCount;
}

void writeItem(ostream& stream, string& s) //writes a string
{
	stream << s << endl;
}

void writeItem(ostream& stream, int& i) //writes an int
{
	stream << i << endl;
}

void writeItem(ostream& stream, vector<IdCount>& v) //writes a vector's information
{
	int i = v.size();
	writeItem(stream, i);
	for(vector<IdCount>::iterator itr = v.begin(); itr!= v.end(); itr++)
	{
		writeItem(stream, itr->count);
		writeItem(stream, itr->id);
	}
}

template<typename KeyType, typename ValueType>
bool saveMyMap(string filename, MyMap<KeyType,ValueType>& m) //Saves a map to a text file
{
	ofstream stream(filename);
	if(!stream)
		return false;
	stream << m.size() << endl;
	KeyType key;
	if(m.size() == 0)
		return true;
	for(ValueType* value = m.getFirst(key); value != NULL; value = m.getNext(key))
	{
		writeItem(stream, key);
		writeItem(stream, *value);
	}
	return true;
}

bool IndexerImpl::save(string filenameBase) //saves a map
{
    return saveMyMap(filenameBase + ".u2i", urlToId) && saveMyMap(filenameBase + ".i2u", idToUrl) && saveMyMap(filenameBase + ".w2id", urlMap);
}

bool readItem(istream& stream, string& s) //reads in a string
{
	if(!(stream >> s))
		return false;
	return true;
}

bool readItem(istream& stream, int& i) //reads in an int
{
	if(!(stream >> i))
		return false;
	return true;
}

bool readItem(istream& stream, vector<IdCount>& v) //reads in a vector
{
	int num, vID, vCount;
	IdCount add;
	readItem(stream, num);
	for(int i = 0; i < num; i++)
	{
		if(!readItem(stream, vCount) || !readItem(stream, vID))
			return false;
		add.count = vCount;
		add.id = vID;
		v.push_back(add);
	}
	return true;
}

template<typename KeyType, typename ValueType>
bool loadMyMap(string filename, MyMap<KeyType,ValueType>& m) //loads a map from file
{
	m.clear();
	ifstream stream(filename);
	if(!stream)
		return false;
	int k;
	if(!readItem(stream, k))
		return false;
	for(int i = 0; i < k; i++)
	{
		KeyType key;
		if(!readItem(stream, key))
			return false;
		ValueType value;
		if(!readItem(stream, value))
			return false;
		m.associate(key, value);
	}
	return true;
}

bool IndexerImpl::load(string filenameBase) //loads a map from a text document
{
    return loadMyMap(filenameBase + ".u2i", urlToId) && loadMyMap(filenameBase + ".i2u", idToUrl) && loadMyMap(filenameBase + ".w2id", urlMap);
}

//******************** Indexer functions *******************************

// These functions simply delegate to IndexerImpl's functions.
// You probably don't want to change any of this code.

Indexer::Indexer()
{
    m_impl = new IndexerImpl;
}

Indexer::~Indexer()
{
    delete m_impl;
}

bool Indexer::incorporate(string url, WordBag& wb)
{
    return m_impl->incorporate(url, wb);
}

vector<UrlCount> Indexer::getUrlCounts(string word)
{
    return m_impl->getUrlCounts(word);
}

bool Indexer::save(string filenameBase)
{
    return m_impl->save(filenameBase);
}

bool Indexer::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}