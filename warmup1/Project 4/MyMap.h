#ifndef MYMAP_INCLUDED
#define MYMAP_INCLUDED

#include <queue>
using namespace std;

template <class KeyType, class ValueType>
class MyMap
{
public:
    MyMap()
    {
		root = NULL;
		numNodes = 0;
    }

    ~MyMap()
    {
		end(root);
    }

    void clear()
    {
		end(root);
		root = NULL;
		numNodes = 0;
    }

    int size() const
    {
        return numNodes;
    }

    void associate(const KeyType& key, const ValueType& value)
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
		while(ptr != NULL)
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

    const ValueType* find(const KeyType& key) const
    {
		Node* ptr = root;
		while(ptr != NULL)
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

    ValueType* getFirst(KeyType& key)
    {
		nodeQueue.push(root->left);
		nodeQueue.push(root->right);
		key = root->key;
        return &(root->value);
    }

    ValueType* getNext(KeyType& key)
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