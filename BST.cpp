#include <iostream>
#include <cstdlib>

#include "BST.h"

using namespace std;

ariel::BST::BST()
{
	Root = NULL;
}

ariel::BST::node* ariel::BST::CreateLeaf(int key)
{
	node* n = new node;
	n->key = key;
	n->left = NULL;
	n->right = NULL;

	return n;
}

void ariel::BST::insert(int key)
{
	addleafprivate(key, Root);
}

void ariel::BST::addleafprivate(int key, node* ptr)
{
	if (Root == NULL)
	{
		Root = CreateLeaf(key);
	}
	else if (key < ptr->key)
	{
		if (ptr->left != NULL)
		{
			addleafprivate(key, ptr->left);
		}
		else
		{
			ptr->left = CreateLeaf(key);
		}
	}
	else if (key > ptr->key)
	{
		if (ptr->right != NULL)
		{
			addleafprivate(key, ptr->right);
		}
		else
		{
			ptr->right = CreateLeaf(key);
		}
	}
	else
	{
		cout << "this key - " << key << "is already added to the tree\n";
	}
}

void ariel::BST::print()
{
	printinorderprivate(Root);
}

void ariel::BST::printinorderprivate(node* ptr)
{
	if(Root != NULL)
	{
		if(ptr->left != NULL)
		{
			printinorderprivate(ptr->left);
		}
		cout << ptr->key << " ";
		if (ptr->right != NULL)
		{
			printinorderprivate(ptr->right);
		}
	}
	else
	{
		cout << "-the tree is empty- \n";
	}
}
ariel::BST::node* ariel::BST::returnode(int key) {
	return returnodeprivate(key, Root);
}
ariel::BST::node* ariel::BST::returnodeprivate(int key, node* ptr) {
	if (ptr != NULL)
	{
		if (ptr->key == key)
		{
			return ptr;
		}
		else 
		{
			if(key<ptr->key)
			{
				return returnodeprivate(key, ptr->left);
			}
			else
			{
				return returnodeprivate(key, ptr->right);
			}
		}
	}
	else
		return NULL;
}
int ariel::BST::root()
{
	if (Root != NULL)
	{
		return Root->key;
	}
	else
	{
		cout << "there is no root";
		return 0;
	}
}

void ariel::BST::printchildren(int key)
{
	node* ptr = returnode(key);
	if (ptr != NULL)
	{
		cout << "parent node = " << ptr->key << endl;
	ptr->left == NULL ?
		cout << "left child = null\n" :
		cout << "left child = " << ptr->left->key << endl;

	ptr->right == NULL ?
		cout << "right child = null\n" :
		cout << "right child = " << ptr->right->key << endl;
	}
	else
	{
		cout << "key " << key << " is not in the tree\n";
	}
}

int ariel::BST::findsmallest() {
	return findsmallestprivate(Root);
}
int ariel::BST::findsmallestprivate(node* ptr) {
	if (Root == NULL)
	{
		cout << "the tree is empty\n";
		return 0;
	}
	else
	{
		if (ptr->left != NULL)
		{
			return findsmallestprivate(ptr->left);
		}
		else
		{
			return ptr->key;
		}
	}
}

void ariel::BST::remove(int key)
{
	removenodeprivate(key, Root);
}
void ariel::BST::removenodeprivate(int key,node* ptr)
{
	if (ptr != NULL)
	{
		if (Root->key == key)
		{
			removerootmatch();
		}
		else
		{
			if (key < ptr->key && ptr->left != NULL)
			{
				ptr->left->key == key ?
				removematch(ptr, ptr->left, true) :
				removenodeprivate(key, ptr->left);
			}
			else if (key > ptr->key && ptr->right != NULL)
			{
				ptr->right->key == key ?
				removematch(ptr, ptr->right, true) :
				removenodeprivate(key, ptr->right);
			}
			else
			{
				cout << "the key " << key << " was not found in the tree\n";
			}
		}
	}
	else
	{
		cout << "the tree is empty\n";
	}
}

void ariel::BST::removerootmatch()
{
	if (Root != NULL)
	{
		node* delptr = Root;
		int rootkey = Root->key;
		int smallestinrightsubtree;

		//case 0 - 0 children
		if (Root->left == NULL && Root->right == NULL)
		{
			Root = NULL;
			delete delptr;
		}

		// case 1 - 1 children 
		else if (Root->left == NULL && Root->right != NULL)
		{
			Root = Root->right;
			delptr->right = NULL;
			delete delptr;
			cout << "the root node with the key" << rootkey << " was deleted" <<
				" the new root contains key " << Root->key << endl;
		}
		else if (Root->left != NULL && Root->right == NULL)
		{
			Root = Root->left;
			delptr->left = NULL;
			delete delptr;
			cout << "the root node with the key" << rootkey << " was deleted" <<
				" the new root contains key " << Root->key << endl;
		}

		//case 2 - 2 children
		else
		{
			smallestinrightsubtree = findsmallestprivate(Root->right);
			removenodeprivate(smallestinrightsubtree, Root);
			Root->key = smallestinrightsubtree;
			cout << "the root key containing key " << rootkey <<
				"was overwritten with key " << Root->key << endl;
		}
	}
	else
	{
		cout << "can't remove the root because the tree is empty";
	}
}
int ariel::BST::left(int key) {
	if (returnode(key) == NULL)
	{
		cout << "the key dosn't exist in the tree" << endl;
		return 0;
	}
	else
	{
		if (returnode(key)->left == NULL)
		{
			cout << "the key dosn't have a left child" << endl;
			return 0;
		}
		else
		{
			return returnode(key)->left->key;
		}

	}
}
int ariel::BST::right(int key) {
	if (returnode(key)==NULL)
	{
		cout << "the key dosn't exist in the tree" << endl;
		return 0;
	}
	else
	{
		if (returnode(key)->right == NULL)
		{
			cout << "the key dosn't have a right child" << endl;
			return 0;
		}
		else
		{
			return returnode(key)->right->key;
		}

	}
}

void ariel::BST::removematch(node* ptr, node* mch, bool left)
{
	if (Root != NULL)
	{
		node* delptr;
		int matchkey = mch->key;
		int smallestinrightsubtree;

		//case 0 - 0 children
		if (mch->left == NULL && mch->right == NULL)
		{
			delptr = mch;
			left == true ? ptr->left = NULL : ptr->right = NULL;
			delete delptr;
			cout  << "the node containing the key " << matchkey << " was removed\n";
		}
		//case 1 - 1 children
		else if (mch->left != NULL && mch->right == NULL)
		{
			left == true ? ptr->left = mch->right : ptr->right = mch->right;
			mch->right = NULL;
			delptr = mch;
				delete delptr;
				cout << "the node containing the key " << matchkey << " was removed\n";

		}
		else if (mch->left == NULL && mch->right != NULL)
		{
			left == true ? ptr->left = mch->left : ptr->right = mch->left;
			mch->left = NULL;
			delptr = mch;
				delete delptr;
				cout << "the node containing the key " << matchkey << " was removed\n";
		}
		
		//case 2 - 2 children
		else
		{
			smallestinrightsubtree = findsmallestprivate(mch->right);
			removenodeprivate(smallestinrightsubtree, mch);
			mch->key = smallestinrightsubtree;
		}
	}
	else
	{
		cout << "cant remove match because the tree is empty\n";
	}
}


ariel::BST::~BST() {
	removesubtree(Root);
}


void ariel::BST::removesubtree(node* ptr) {
	if (ptr != NULL)
	{
		if (ptr->left != NULL)
		{
			removesubtree(ptr->left);
		}
		if (ptr->right != NULL)
		{
			removesubtree(ptr->right);
		}
		cout << "deleting the node containing key" << ptr->key << endl;
		delete ptr;
	}
}
bool ariel::BST::contains(int key) {
	return containsprivate(Root, key);
}


bool ariel::BST::containsprivate(node* ptr, int key) {
	if (ptr == NULL) return false;
	else {
		if (key== ptr->key)
			return true;
		else if (key < ptr->key)
			return containsprivate(ptr->left, key);      //you forgot to return the value
		else if (key > ptr->key)
			return containsprivate(ptr->right, key);
	}
}

int ariel::BST::size()
{
	return sizeprivate(Root);
}

int ariel::BST::sizeprivate(node* ptr)
{
	if (ptr == NULL)
		return 0;
	else
		return  1 + (sizeprivate(ptr->left) + sizeprivate(ptr->right));
}

int ariel::BST::parent(int key) {
	return parentprivate(Root, key);
}

int ariel::BST::parentprivate(node* ptr, int key)
{
	if (ptr->left == NULL && ptr->right == NULL)
		return 0;

	if (ptr->left->key == key || ptr->right->key == key)
		return ptr->key;

	if (ptr->key > key)
		return parentprivate(ptr->left, key);

	if (ptr->key < key)
		return parentprivate(ptr->right, key);

}