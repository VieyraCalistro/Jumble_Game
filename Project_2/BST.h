#pragma once


template<typename Type>
class BST
{
	struct Node
	{
		Type _data;

		Node* left;

		Node* right;

		Node()
		{
			left = nullptr;
			right = nullptr;
		}
	};


public:
		
		
		Node* root = nullptr;

		unsigned int size = 0;

		void RecursionForPrint(Node* temp) const
		{
			if (temp != nullptr)
			{
				
				RecursionForPrint(temp->left);
				cout << temp->_data << " ";
				RecursionForPrint(temp->right);
				
			}
		}

		void RecursionForClear(Node* temp)
		{

			if (temp != nullptr)
			{
				RecursionForClear(temp->left);
				RecursionForClear(temp->right);
				delete temp;
			}
		}

		void RecursiveFunctionForInsert(Node* temp, Node* node)
		{
			if (temp != nullptr)
			{
				if (node->_data < temp->_data)
				{

					if (temp->left == nullptr)
					{
						temp->left = node;
						size++;

						return;
					}

					RecursiveFunctionForInsert(temp->left, node);
				}
				else if (node->_data >= temp->_data)
				{

					if (temp->right == nullptr)
					{
						temp->right = node;
						size++;

						return;
					}

					RecursiveFunctionForInsert(temp->right, node);
				}
			}
			
		}

		void RecursionForFind(Node* temp, Type value, bool &found) const
		{
			if (temp != nullptr)
			{
				if (value < temp->_data)
				{

					RecursionForFind(temp->left, value, found);
				}

				if (value > temp->_data)
				{

					RecursionForFind(temp->right, value, found);
				}

				if (value == temp->_data)
				{
					found = true;
				}
			}

		}

		void RecursionForFindAndRemove(Node* current, Type value, Node* previous, bool &removed)
		{
			if (current != nullptr)
			{
				if (previous == nullptr && current != root)
				{
					previous = root;
				}

				if (value < current->_data)
				{
					if (previous != nullptr)
					{
						if (previous->left == current)
						{
							RecursionForFindAndRemove(current->left, value, previous->left, removed);
						}
						else
						{
							RecursionForFindAndRemove(current->left, value, previous->right, removed);
						}
						
					}
					else
					{

						RecursionForFindAndRemove(current->left, value, previous, removed);
					}
				}

				if (value > current->_data)
				{
					if (previous != nullptr)
					{
						if (previous->right == current)
						{
							RecursionForFindAndRemove(current->right, value, previous->right, removed);
						}
						else
						{
							RecursionForFindAndRemove(current->right, value, previous->left, removed);
						}
						
					}
					else
					{

						RecursionForFindAndRemove(current->right, value, previous, removed);
					}
				}

				if (value == current->_data)
				{
					if (size == 1)
					{
						clear();

						removed = true;

						return;
					}
					else if (current->left == nullptr && current->right == nullptr && current != nullptr)
					{
						if (previous->_data <= current->_data)
						{
							delete current;

							size--;

							removed = true;

							previous->right = nullptr;

							return;
						}
						else if (previous->_data > current->_data)
						{
							delete current;

							size--;

							removed = true;

							previous->left = nullptr;
						}
					}
					else if (size > 1 && current->left == nullptr && current->right != nullptr)
					{

						if (previous != nullptr)
						{
							if (previous->_data <= current->_data)
							{
								previous->right = current->right;

								delete current;

								size--;

								removed = true;

								return;
							}
							else if (previous->_data > current->_data)
							{
								previous->left = current->right;

								delete current;

								size--;

								removed = true;

								return;

							}
						}
						else if (previous == nullptr)
						{
							previous = current->right;

							delete current;

							size--;

							root = previous;

							removed = true;

							return;
						}
					}
					else if (size > 1 && current->left != nullptr && current->right == nullptr)
					{
						Node* temp = current->left;

						if (previous != nullptr)
						{
							if (previous->_data <= current->_data)
							{
								previous->right = current->left;

								delete current;

								size--;

								removed = true;

								return;
							}
							else if (previous->_data > current->_data)
							{
								previous->left = current->left;

								delete current;

								size--;

								removed = true;

								return;
							}
						}
						else if (previous == nullptr)
						{
							previous = current->left;

							delete current;

							size--;

							removed = true;

							return;
						}
					}
					else if (size == 3 && current->left != nullptr && current->right != nullptr)
					{
						previous = current->right;

						previous->left = current->left;

						previous->right = nullptr;

						delete current;

						size--;

						removed = true;

						return;

					}
					else if (size > 2 && current->left != nullptr && current->right != nullptr)
					{
						Type OldCurrent = current->_data;
						
						previous = current;

						current = current->right;

						while (true)
						{
							if (current->left != nullptr)
							{
								current = current->left;
								continue;
							}
							break;
						}

						Type NewCurrent = current->_data;

						current->_data = OldCurrent;

						previous->_data = NewCurrent;

						if (current->right == nullptr)
						{
							previous = previous->right;

							while (true)
							{
								if (previous->left != current)
								{
									previous = previous->left;
									continue;
								}

								break;
							}

							previous->left = current->right;

							delete current;

							size--;

							removed = true;

							return;
						}
						else if (current->right != nullptr)
						{
							previous = previous->right;

							while (true)
							{
								if (previous->left != current)
								{
									previous = previous->left;
									continue;
								}

								break;
							}

							previous->left = current->right;

							delete current;

							size--;

							removed = true;
						}

					}

				}
			}
		}


		/////////////////////////////////////////////////////////////////////////////
		// Function : Constuctor
		// Notes : constucts an empty BST
		/////////////////////////////////////////////////////////////////////////////
		BST()
		{

		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : Destructor
		// Notes : destroys the BST cleaning up any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
		~BST()
		{
			clear();
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : assignment operator
		/////////////////////////////////////////////////////////////////////////////
		BST& operator=(const BST& that)
		{
			if (this != &that)
			{
				clear();

				size = that.size;

				Node* node = that.root;


				RecursionForCopyConstructor(node);

			}
			
			return *this;
		}

		void RecursionForCopyConstructor(Node* node)
		{
			
			if (node != nullptr)
			{
				insert(node->_data);

				if (node->left != nullptr)
				{
					RecursionForCopyConstructor(node->left);
				}
				
				if (node->right != nullptr)
				{
					RecursionForCopyConstructor(node->right);
				}
				

			}
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function: copy constructor
		/////////////////////////////////////////////////////////////////////////////
		BST(const BST& that)
		{
			size = that.size;

			Node* node = that.root;

			RecursionForCopyConstructor(node);
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : insert
		// Parameters :  v - the item to insert 
		/////////////////////////////////////////////////////////////////////////////
		void insert(const Type& v)
		{
			// Create a new node and assign it to the passed in parameter.
			Node* node = new Node;

			node->_data = v;

			// Assign left and right of new node to null.
			node->left = nullptr;
			node->right = nullptr;

			// Check to see if the root is null.
			if (root == nullptr)
			{
				root = node;

				size++;
				return;
			}

			// Create a temporary current pointer.
			Node* temp = root;

			RecursiveFunctionForInsert(temp, node);
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : findAndRemove
		// Parameters : v - the item to find (and remove if it is found)
		// Return : bool - true if the item was removed, false otherwise
		/////////////////////////////////////////////////////////////////////////////
		bool findAndRemove(const Type& v)
		{
			Node* previous = nullptr;

			Node* current = root;

			bool removed = false;

			RecursionForFindAndRemove(current, v, previous, removed);

			return removed;
		}




		/////////////////////////////////////////////////////////////////////////////
		// Function : find
		// Parameters : v - the item to find
		// Return : bool - true if the item was found, false otherwise
		/////////////////////////////////////////////////////////////////////////////
		bool find(const Type& v) const
		{
			Node* temp = root;

			bool found = false;

			RecursionForFind(temp, v, found);

			return found;
		}


		/////////////////////////////////////////////////////////////////////////////
		// Function : clear
		// Notes : clears the BST, cleaning up any dynamic memory
		/////////////////////////////////////////////////////////////////////////////
		void clear()
		{
			Node* temp = root;

			RecursionForClear(temp);

			root = nullptr;

			size = 0;
			
		}

		/////////////////////////////////////////////////////////////////////////////
		// Function : printInOrder
		// Notes : prints the contents of the BST to the screen, in ascending order
		/////////////////////////////////////////////////////////////////////////////
		void printInOrder() const
		{
			Node* temp = root;
			RecursionForPrint(temp);
			cout << endl;
		}

};

