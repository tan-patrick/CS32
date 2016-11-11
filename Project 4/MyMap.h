#ifndef MYMAP_INCLUDED
#define MYMAP_INCLUDED

#include <queue>
using namespace std;

template <class KeyType, class ValueType>
class MyMap
{
public:
    MyMap() // Constructor for MyMap
    {
		root = NULL;
		numNodes = 0;
    }

    ~MyMap() // Destructor for MyMap
    {
		end(root);
    }

    void clear() // Clear all nodes from MyMap
    {
		end(root);
		root = NULL;
		numNodes = 0;
    }

    int size() const //Returns number of Nodes in the map
    {
        return numNodes;
    }

    void associate(const KeyType& key, const ValueType& value) //Associates a key with a value; O(log N)
    {
		Node* temp = new Node;
		temp->value = value;
		temp->key = key;
		temp->left = NULL;
		temp->right = NULL;
		if(root == NULL)
		{
			root = temp;
			numNodes++;
			return;
		}
		ValueType* available = find(key);
		if(available != NULL)
		{
			*available = value;
			return;
		}

		Node* ptr = root;
		Node* add;
		bool less;
		while(ptr != NULL) //O(log N)
		{
			add = ptr;
			if(key < ptr->key)
			{
				ptr = ptr->left;
				less = true;
			}
			else
			{
				ptr = ptr->right;
				less = false;
			}
		}
		if(less)
			add->left = temp;
		else
			add->right = temp;
		numNodes++;
    }

    const ValueType* find(const KeyType& key) const // Finds the value for a given key; O(log N)
    {
		Node* ptr = root;
		while(ptr != NULL) //O(log N)
		{
			if(key == ptr->key)
				return &(ptr->value);
			else if(key < ptr->key)
				ptr = ptr->left;
			else
				ptr = ptr->right;
		}
		return NULL;
    }
        
    ValueType* find(const KeyType& key)
    {
          // Do not change the implementation of this overload of find
        const MyMap<KeyType,ValueType>* constThis = this;
        return const_cast<ValueType*>(constThis->find(key));
    }

    ValueType* getFirst(KeyType& key) // Sets the key variable to the key of the first node and returns the value of node
    {
		if(root->left != NULL)
			nodeQueue.push(root->left);
		if(root->right != NULL)
			nodeQueue.push(root->right);
		key = root->key;
        return &(root->value);
    }

    ValueType* getNext(KeyType& key) // Sets the key variable to the key of the next node and returns the value of node
    {
        if(nodeQueue.empty())
			return NULL;

		Node* current = nodeQueue.front();
		nodeQueue.pop();

		if(current->left != NULL)
			nodeQueue.push(current->left);
	
		if(current->right != NULL)
			nodeQueue.push(current->right);

		key = current->key;
		return &(current->value);
    }

private:
    MyMap(const MyMap &other);
    MyMap &operator=(const MyMap &other);

    // Add needed members
	struct Node
	{
		KeyType key;
		ValueType value;
		Node* left;
		Node* right;
	};
	Node* root;
	int numNodes;
	queue<Node*> nodeQueue;

	void end(Node* cur)
	{
		if(cur == NULL)
			return;
		end(cur->left);
		end(cur->right);
		delete cur;
	}
};

#endif // MYMAP_INCLUDED