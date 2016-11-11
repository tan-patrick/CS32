#include "provided.h"
#include "http.h"
#include <string>
#include <vector>
using namespace std;

class WebCrawlerImpl
{
public:
    void addUrl(string url);
    int getNumberOfUrls() const;
    void crawl(void (*callback)(string url, bool success));
    bool save(string filenameBase);
    bool load(string filenameBase);
private:
	Indexer myIndex;
	vector<string> myUrls;
};

void WebCrawlerImpl::addUrl(string url) //adds a URL to the list to be crawled
{
	myUrls.push_back(url);
}

int WebCrawlerImpl::getNumberOfUrls() const //returns number of URLs to be crawled
{
    return myUrls.size();
}

void WebCrawlerImpl::crawl(void (*callback)(string url, bool success)) //Crawls, or goes through the list of URLs, downloading the text from each site
{
	string page;
	for(int i = 0; i < myUrls.size(); i++)
	{
		if(HTTP().get(myUrls[i], page))
		{
			WordBag wb(page);
			if(!myIndex.incorporate(myUrls[i], wb))
				callback(myUrls[i], false);
			else
				callback(myUrls[i], true);
		}
		else
			callback(myUrls[i], false);
	}
}

bool WebCrawlerImpl::save(string filenameBase) //saves a webcrawler
{
	return myIndex.save(filenameBase);
}

bool WebCrawlerImpl::load(string filenameBase) //loads a webcrawler
{
    return myIndex.load(filenameBase);
}

//******************** WebCrawler functions *******************************

// These functions simply delegate to WebCrawlerImpl's functions.
// You probably don't want to change any of this code.

WebCrawler::WebCrawler()
{
    m_impl = new WebCrawlerImpl;
}

WebCrawler::~WebCrawler()
{
    delete m_impl;
}

void WebCrawler::addUrl(string url)
{
    m_impl->addUrl(url);
}

int WebCrawler::getNumberOfUrls() const
{
    return m_impl->getNumberOfUrls();
}

void WebCrawler::crawl(void (*callback)(string url, bool success))
{
    m_impl->crawl(callback);
}

bool WebCrawler::save(string filenameBase)
{
    return m_impl->save(filenameBase);
}

bool WebCrawler::load(string filenameBase)
{
    return m_impl->load(filenameBase);
}
