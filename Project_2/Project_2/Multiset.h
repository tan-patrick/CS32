#ifndef MULTISET_INC
#define MULTISET_INC

#include <string>
typedef std::string ItemType;

class Multiset
{
  public:
    Multiset(); //Constructor
    bool empty() const; //Finds if Multiset is empty
    int size() const; //Returns number of items
    int uniqueSize() const; //Returns number of unique items
    bool insert(const ItemType& value); //Adds a value to the multiset
    int erase(const ItemType& value); //Erases a single value
    int eraseAll(const ItemType& value); //Erases all of a value
    bool contains(const ItemType& value) const; //Finds if a value is in the multiset
    int count(const ItemType& value) const; //Returns the amount of times a value appears
    int get(int i, ItemType& value) const; //Returns the amount at a certain Node and stores the value
    void swap(Multiset& other); //Swaps two multisets
	~Multiset(); //Destructor
	Multiset(const Multiset& other); //Copy constructor
	Multiset& operator=(const Multiset& rhs); //Assignment operator
  private:
	struct Node //Structure Node containing value, count, and pointers to the next and previous nodes in the linked list
    {
        ItemType m_value;
        int      m_count;
		Node	 *next;
		Node	 *previous;
    };
    int  m_uniqueSize;
    int  m_size;
	Node *m_head;
	Node *m_tail;
	Node *dummy;
	
	bool find(const ItemType& value, Node*& check) const; //Finds if a value is present in the linked list, and stores the pointer where it is located
	int doErase(const ItemType& value, bool all); //Erases a value: single or all of the value
};

inline
void combine(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	int amount = 0;
	int count = 0;
	ItemType add;
	result = ms1;
	for(int i = 0; i < ms2.uniqueSize(); i++) //Add all values from ms2 to result
	{
		amount = ms2.get(i, add);
		while(count < amount)
		{
			result.insert(add);
			count++;
		}
		count = 0;
		amount = 0;
	}
}

inline
void subtract(const Multiset& ms1, const Multiset& ms2, Multiset& result)
{
	int amount = 0;
	int count = 0;
	result = ms1;
	ItemType subtract;
	for(int i = 0; i < ms2.uniqueSize(); i++) //Subtract all values from ms2 from result
	{
		amount = ms2.get(i, subtract);
		while(count < amount)
		{
			result.erase(subtract);
			count++;
		}
		count = 0;
		amount = 0;
	}
}
#endif