#include "Multiset.h"
#include <iostream>
using namespace std;

Multiset::Multiset()
	:m_uniqueSize(0), m_size(0)
{
	m_head = NULL;
	m_tail = NULL;
	dummy = new Node; //Creates a dummy node in the double-linked list between m_head and m_tail
	dummy->next = m_head;
	dummy->previous = m_tail;
}

bool Multiset::empty() const
{
	return size() == 0;
}

int Multiset::size() const
{
	return m_size;
}

int Multiset::uniqueSize() const
{
	return m_uniqueSize;
}

bool Multiset::insert(const ItemType& value)
{
	Node *check;

	if(find(value, check)) //Checks if the value is already in the multiset
	{
		check->m_count++;
		m_size++;
		return true; //If it is, adds one to the count of the value and increments size by one
	}
	else
	{
		Node *newest = new Node; //Create a new node, and initialize with the value stored, next as the current m_head, and count as one
		newest->m_value = value;
		newest->next = m_head;
		if(m_head == NULL) //Sets the next value to dummy if it is the first node
		{
			newest->next = dummy;
			dummy->next = m_head;
		}	
		newest->m_count = 1;
		newest->previous = dummy;
		if(m_head != NULL) //Ensures that this is not the first node
			m_head->previous = newest;
		m_head = newest;
		if(m_tail == NULL) //Sets the first value to m_tail and m_tails next value to dummy
		{
			m_tail = m_head;
			m_tail->next = dummy;
			dummy->previous = m_tail;
		}
		m_uniqueSize++;
		m_size++;
		return true;
	}
	return false;
}

int Multiset::erase(const ItemType& value)
{
	return doErase(value, false);
}

int Multiset::eraseAll(const ItemType& value)
{
	return doErase(value, true);
}

bool Multiset::contains(const ItemType& value) const
{
	Node *sub = new Node; //Throwaway Node to run function find
	return find(value, sub);
}

int Multiset::count(const ItemType& value) const
{
	Node *target = new Node;
	if(find(value, target)) //Finds if the value is present and returns the count if it is
		return target->m_count;
	return 0;
}

int Multiset::get(int i, ItemType& value) const
{
	if (i < 0  ||  i >= m_uniqueSize) //Checks to make sure i is in the multiset
        return 0;
	Node *track = m_head;
	for(int count = 0; count < i; track = track->next, count++) //Traverses to the ith location in the linked list
	{}
	value = track->m_value;
	return track->m_count;
}

void Multiset::swap(Multiset& other) //Trades all private variables with the other multiset
{
	Node* tempDummy = dummy;
    dummy = other.dummy;
    other.dummy = tempDummy;

	Node* tempHead = m_head;
    m_head = other.m_head;
    other.m_head = tempHead;

	Node* tempTail = m_tail;
    m_tail = other.m_tail;
    other.m_tail = tempTail;

	int tempSize = m_size;
	m_size = other.m_size;
	other.m_size = tempSize;

	int tempUnique = m_uniqueSize;
	m_uniqueSize = other.m_uniqueSize;
	other.m_uniqueSize = tempUnique;
}

Multiset::~Multiset()
{
	Node* temp = m_head;
	Node* nextDelete;
	while(m_head != NULL && temp != dummy) //Checks that the list is not empty and ends the loop when it reaches the m_tail
	{	
		nextDelete = temp->next; //Traverses the linked list, deleting Nodes as it goes
		delete temp;
		temp = nextDelete;
	}
	delete dummy;
}

Multiset::Multiset(const Multiset& other) //Initializes all values 
 : m_uniqueSize(other.m_uniqueSize), m_size(other.m_size)
{
	m_head = new Node;
	dummy = new Node;
	m_tail = new Node;
	Node* current = other.m_head;
	Node* before = m_head;
	if(other.m_head != NULL) //Check to make sure the other multiset is not empty
	{
		before->m_value = current->m_value;
		before->m_count = current->m_count;
		before->previous = dummy;
		dummy->next = before;
		while(current->next != other.dummy) //Traverses the entire linked list of the other multiset
		{
			current = current->next;
			Node* newest = new Node;
			newest->m_count = current->m_count;
			newest->m_value = current->m_value;
			newest->previous = before;
			before->next = newest;
			newest->next = dummy;
			before = newest; //Create new node, set new nodes values, and place it in the linked list
		}
	before->next->previous = before;
	m_tail = dummy->previous;
	}
}

Multiset& Multiset::operator=(const Multiset& rhs)
{
    if (this != &rhs) //Ensures it is not copying itself
    {
        Multiset temp(rhs); //Creates a multiset with the copy constructor and swaps it with the chosen multiset
        swap(temp);
    }
    return *this;
}

bool Multiset::find(const ItemType& value, Node*& check) const //Finds if a value is present in the linked list, and stores the pointer where it is located
{
	check = m_head;
	if(check == NULL) //Checks for an empty list
		return false;

	while(check != dummy)  //Goes through the whole list
	{
		if(check->m_value == value)
            return true;		//If the value of check is the value we are looking for, return true and stores the pointer to the Node in check
		check = check->next;
	}
    return false; //Returns false if the value is not present in the multiset
}

int Multiset::doErase(const ItemType& value, bool all)
{
	Node *check;

	if(find(value, check)) //Checks if the value is present and stores the pointer if it is
	{
		if (!all  &&  check->m_count > 1) //If we are only removing one and there is more than one, we simply lower count and m_size by 1
		{
			check->m_count--;
			m_size--;
			return 1;
		}
		int nErased = check->m_count; //If we are removing all or if there is only one left, we lower the size by number erased, and unique size by 1
		m_size -= nErased;
		m_uniqueSize--;
		check->previous->next = check->next;	//Resets the pointers of the next and previous nodes to each other, skipping the node being deleted
		check->next->previous = check->previous;
		if(check == m_head) //Checks for cases of deleting m_head or m_tail
		{
			m_head = check->next;
			dummy->next = m_head;
		}
		if(check == m_tail)
		{
			m_tail = check->previous;
			dummy->previous = m_tail;
		}
		delete check;
		return nErased;
	}
	else
	{
		return 0;
	}
}