
#pragma once
#include <iostream>


using namespace std;

template<typename Type> class SLLIter;

template<typename Type>
class SLList
{

private:

	// Create Node struct.
	struct Node
	{
		Type _data;
		Node* _next;

	};

	// Assign new head to null for now.
	Node* head = nullptr;

	// Start counter for size at zero.
	unsigned int counter = 0;




public:

	// Make the class SLLIter a friend.
	friend class SLLIter<Type>;

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Notes : constructs an empty list
	/////////////////////////////////////////////////////////////////////////////
	SLList();

	/////////////////////////////////////////////////////////////////////////////
	// Function : Destructor
	// Notes : Destroys the list
	/////////////////////////////////////////////////////////////////////////////
	~SLList();

	/////////////////////////////////////////////////////////////////////////////
	// Function : Assignment Operator
	/////////////////////////////////////////////////////////////////////////////
	SLList<Type>& operator=(const SLList<Type>& that);

	/////////////////////////////////////////////////////////////////////////////
	// Function : Copy Constructor
	/////////////////////////////////////////////////////////////////////////////
	SLList(const SLList<Type>& that);

	/////////////////////////////////////////////////////////////////////////////
	// Function : addHead
	// Parameters :	v - the item to add to the list
	/////////////////////////////////////////////////////////////////////////////
	void addHead(const Type& v);

	/////////////////////////////////////////////////////////////////////////////
	// Function : clear
	// Notes : clears the list, freeing any dynamic memory
	/////////////////////////////////////////////////////////////////////////////
	void clear();




	/////////////////////////////////////////////////////////////////////////////
	// Function : insert
	// Parameters :	index - an iterator to the location to insert at
	//				v - the item to insert
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void insert(SLLIter<Type>& index, const Type& v);

	/////////////////////////////////////////////////////////////////////////////
	// Function : remove
	// Parameters :	index - an iterator to the location to remove from
	// Notes : do nothing on a bad iterator
	/////////////////////////////////////////////////////////////////////////////
	void remove(SLLIter<Type>& index);

	/////////////////////////////////////////////////////////////////////////////
	// Function : size
	// Return : the number of items stored in the linked list.
	/////////////////////////////////////////////////////////////////////////////
	inline unsigned int size() const;


	void SetCounter(unsigned int update);

	void recurse(Node* n);


};


template<typename Type>
SLList<Type>::SLList()
{

	// Set new size to zero.
	counter = 0;

}



template<typename Type>
SLList<Type>::~SLList()
{
	// Call your clear here to delete all the nodes.
	clear();

}


template<typename Type>
inline SLList<Type>& SLList<Type>::operator=(const SLList& that)
{

	// Check to see that we are not making a deep copy of the same object.
	if (this != &that)
	{
		// Delete previous stored information.
		clear();


		// Assign the items in the correct order.
		recurse(that.head);


		// Copy over the size of the list passed in.
		counter = that.size();

	}

	return (*this);
}



template<typename Type>
inline void SLList<Type>::recurse(Node * n)
{

	if (n != nullptr)
	{
		recurse(n->_next);
		addHead(n->_data);
	}

}



template<typename Type>
inline SLList<Type>::SLList(const SLList& that)
{

	// Assign nodes to the list in order.
	recurse(that.head);


	// Copy over the size of the list passed in.
	this->counter = that.size();

}


template<typename Type>
void SLList<Type>::addHead(const Type& v)
{

	// Create a new node.
	Node* node = new Node;

	// Assign new node's data to the one passed in.
	node->_data = v;

	// Add the list behind the node.
	node->_next = this->head;

	// Now set the head of the list to the address of the temp node.
	head = node;

	// Increase size for new node added.
	unsigned int update = counter + 1;
	SetCounter(update);

}


template<typename Type>
inline void SLList<Type>::clear()
{
	// Create a refernce to a Node and assign to the head of the list.
	Node* temp = head;


	// Loop through and start deleting all the nodes one by one.
	while (temp != nullptr)
	{
		Node* temp2 = temp->_next;

		delete temp;

		temp = temp2;

	}

	head = nullptr;

	// Set counter to 0.
	SetCounter(0);

}


template<typename Type>
inline void SLList<Type>::insert(SLLIter<Type>& index, const Type& v)
{

	//Start new.

	if (index.CurrentNodeptr == nullptr)
	{
		return;
	}
	else if (index.previousNodeptr == nullptr)
	{
		// Create new node.
		Node* node = new Node;

		// Assign the type passed in to your new node created
		node->_data = v;

		node->_next = index.CurrentNodeptr;

		index.CurrentNodeptr = node;

		head = index.CurrentNodeptr;

		unsigned int update = counter + 1;
		SetCounter(update);

	}
	else
	{
		// Create new node.
		Node* node = new Node;

		// Assign the type passed in to your new node created
		node->_data = v;

		//Insert new node to previous next if not nullptr
		index.previousNodeptr->_next = node;


		//nodes next = the Current node pointer.
		node->_next = index.CurrentNodeptr;


		index.CurrentNodeptr = index.previousNodeptr->_next;


		unsigned int update = counter + 1;
		SetCounter(update);
	}


}



template<typename Type>
void SLList<Type>::remove(SLLIter<Type>& index)
{
	//Start new.
	if (index.CurrentNodeptr == nullptr)
	{
		return;

	}
	else
	{

		if (index.CurrentNodeptr == head)
		{
			head = index.CurrentNodeptr->_next;

			delete index.CurrentNodeptr;

			index.CurrentNodeptr = head;

			// Decrement the size of the list.
			unsigned int update = counter - 1;
			SetCounter(update);
		}
		else
		{
			index.previousNodeptr->_next = index.CurrentNodeptr->_next;

			// Now delete the node current pointer is pointing to.
			delete index.CurrentNodeptr;


			index.CurrentNodeptr = index.previousNodeptr->_next;


			// Decrement the size of the list.
			unsigned int update = counter - 1;
			SetCounter(update);

		}
		

	}




}


template<typename Type>
unsigned int SLList<Type>::size() const
{
	// Print out size.
	return counter;
}


template<typename Type>
void SLList<Type>::SetCounter(unsigned int update)
{
	// Adjust counter as needed.
	counter = update;
}





template<typename Type>
class SLLIter
{

public:

	friend class SLList<Type>;

	//The SLLIter class will have the following public interface :

	/////////////////////////////////////////////////////////////////////////////
	// Function : Constructor
	// Parameters :	listToIterate - the list to iterate
	/////////////////////////////////////////////////////////////////////////////
	SLLIter(SLList<Type>& listToIterate);



	/////////////////////////////////////////////////////////////////////////////
	// Function : begin
	// Notes : moves the iterator to the head of the list
	/////////////////////////////////////////////////////////////////////////////
	void begin();



	/////////////////////////////////////////////////////////////////////////////
	// Function : end
	// Notes : returns true if we are at the end of the list, false otherwise
	/////////////////////////////////////////////////////////////////////////////
	bool end() const;

	/////////////////////////////////////////////////////////////////////////////
	// Function : operator++
	// Notes : move the iterator forward one node
	/////////////////////////////////////////////////////////////////////////////
	SLLIter<Type>& operator++();



	/////////////////////////////////////////////////////////////////////////////
	// Function : current
	// Notes : returns the item at the current iterator location
	/////////////////////////////////////////////////////////////////////////////
	Type& current() const;


	SLList<Type>* _iterator = nullptr;
	typename SLList<Type>::Node* CurrentNodeptr = nullptr;
	typename SLList<Type>::Node* previousNodeptr = nullptr;


};

template<typename Type>
inline SLLIter<Type>::SLLIter(SLList<Type>& listToIterate)
{
	// Set the Current to the list that was passed through.
	_iterator = &listToIterate;


	// Now you have set the current position to the head of the list and _iterator.
	CurrentNodeptr = _iterator->head;

}

template<typename Type>
inline void SLLIter<Type>::begin()
{

	// Assign _iterator to the head of the list.
	CurrentNodeptr = _iterator->head;

	// Keep the previous behind the current node, which would be nullptr.
	previousNodeptr = nullptr;

}


template<typename Type>
bool SLLIter<Type>::end() const
{

	// Start new method.


	if (CurrentNodeptr == nullptr)
	{
		
		return true;
	}

	return false;

}



template<typename Type>
SLLIter<Type>& SLLIter<Type>::operator++()
{
	// Start new.

	if (CurrentNodeptr != nullptr)
	{
		previousNodeptr = CurrentNodeptr;
		CurrentNodeptr = CurrentNodeptr->_next;
	}


	return *this;
}


template<typename Type>
Type& SLLIter<Type>::current() const
{
	return CurrentNodeptr->_data;
}


