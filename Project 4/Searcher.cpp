#include "provided.h"
#include "MyMap.h"
#include <string>
using namespace std;

struct Hits //Structure holding the amount of hit (only once each term), and the total amount of hits
{
	int hits;
	int totalHits;
};

struct urlHits //Structure holding a url and the amount of total hits the url has
{
	string url;
	int totalHits;
};

class SearcherImpl
{
public:
    vector<string> search(string terms);
    bool load(string filenameBase);
private:
	Indexer myIndex;
}; 

bool compareHits(const urlHits& left, const urlHits& right) //compares two urls to see who had more hits
{
	if(left.totalHits > right.totalHits)
		return true;
	else
		return false;
}

vector<string> SearcherImpl::search(string terms) //searches the index with a given search string; O(W * P log P)
{
	strToLower(terms);
	vector<string> searchTerms;
	Tokenizer find(terms);
	string w;

	while(find.getNextToken(w))	//O(W), if W is the amount of search words
	{
		searchTerms.push_back(w);
	}

	int T = int(.7*searchTerms.size());
	if(T < 1)
		T = 1;

	MyMap<string, Hits> hits;
	vector<UrlCount> urls;
	Hits add;
	for(int i = 0; i < searchTerms.size(); i++) //O(W), if W is the amount of search words
	{
		Hits* check;
		urls = myIndex.getUrlCounts(searchTerms[i]); //O(P log N), if N is the amount of words in the index, and P is the average amount of URLs associated with each word

		for(int j = 0; j < urls.size(); j++) //O(P), if P is the average amount of URLs associated with each word
		{
			check = hits.find(urls[j].url); //O(log P), if P is the average amount of URLs associated with each word
			if(check == NULL)
			{
				add.hits = 1;
				add.totalHits = urls[j].count;
				hits.associate(urls[j].url, add); //O(log P), if P is the average amount of URLs associated with each word
			}
			else
			{
				add.hits += 1;
				add.totalHits += urls[j].count;
				hits.associate(urls[j].url, add); //O(log P), if P is the average amount of URLs associated with each word
			}
		}
	}

    vector<urlHits> completeHits;
	string key;
	urlHits toAdd;
	
	vector<string> ret;

	if(hits.size() == 0)
		return ret;

	for(Hits* value = hits.getFirst(key); value != NULL; value = hits.getNext(key)) //O(P) is maximum value
	{
		if(value->hits >= T)
		{
			toAdd.url = key;
			toAdd.totalHits = value->totalHits;
			completeHits.push_back(toAdd);
		}
	}

	sort(completeHits.begin(), completeHits.end(), compareHits); //O(P log P)

	for(int i = 0; i < completeHits.size(); i++) //O(P) is maximum value
	{
		ret.push_back(completeHits[i].url);
	}

	return ret;
}

bool SearcherImpl::load(string filenameBase) //loads an index from file
{
    return myIndex.load(filenameBase);
}

//******************** Searcher functions *******************************

// These functions simply delegate to SearcherImpl's functions.
// You probably don't want to change any of this code.

Searcher::Searcher()
{
    m_impl = new SearcherImpl;
}

Searcher::~Searcher()
{
    delete m_impl;
}

vector<string> Searcher::search(string terms)
{
    return m_impl->search(terms);
}

bool Searcher::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}
