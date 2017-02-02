/**
* @wl.h
* @author Qing (Sabrina) Yu
* @UW Campus ID 9070146981 
* @email qyu37@wisc.edu 
* @version 1.0
*
* @section LICENSE
*
*
* @section DESCRIPTION This program follows the user input to load, locate, new and end. It has several functions 
* which are to insert new word from a file to a binary search tree, to find the 
* specific word from the tree.
*
* The time class represents a moment of time.
*/

#ifndef __WL_H_
#define __WL_H_
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;

/**
* @brief A struct to implement binary search tree
* @author: Qing (Sabrina) Yu
*
* This TreeNode struct declares a group of variables related to construct a tree.
*/
struct TreeNode
{
	char *word; /**< TreeNode pointer. The key value of each node. The words to put in from the input file. */
	int loc; /**< Another key value which represents the location of a single word in a file */
	TreeNode *left; /**< TreeNode pointer. Left children */
	TreeNode *right; /**< TreeNode pointer. Right children */
	/**
	* A constructor.
	* Initiate the variables in the tree node. 
	*/
	TreeNode()
	{
		word = NULL; 
		loc = 0;
		left = right = NULL;
	}
	/**
	* a normal member taking two arguments.
	* @param data an input word
	* @param n an input location of a word
	* @param word the key of tree node to store an input word
	* @param loc the location of the input word from a file
	* @param left the left child of the node
	* @param right the right child of the node
	*/
	TreeNode(const char *data, int n)
	{
		if (data != NULL){
			word = strdup(data);
		}
		else {
			word = NULL;
		}
		loc = n;
		left = right = NULL;
	}
};

typedef struct TreeNode *  Tree;
/**
 * @brief A class to query given words in a file
 * @author: Qing (Sabrina) Yu
 *
 * This program is used to read in a file and tell users the location of the words 
 * they are querying (also based on the times of occurance of the words). This class can also
 * use for cleaning the tree and exiting the whole program.
 */
class BSTree
{
private:

	Tree root; /**< root */
public:
	/**
	* An BSTree.
	* Initialize a binary search tree
	*/

	BSTree()
	{
		root = NULL;/**< root */
	}
	/**
	* Insert interface function to pass in the root node for recursive function.
	* @param word a word from the file to be inserted to the tree
	* @param n an input location of a word from the file
	* @return the total number of nodes have been inserted
	*/
	int insert_interface(const char *word, int n);
        /**
	* Insert recursive function which add a new node with a key
	* @param node a new node to insert
	* @param word a word from the file to be inserted to the tree
	* @param n the location of a word from the file
	* @return the total number of nodes have been inserted
	*/
	TreeNode * insert_recursion(TreeNode * node, const char *word, int n);
	/**
	* Search function which search a node with a key
	* @param node a node which contains the word to be searched
	* @param word a word from the file to be searched to the tree
	* @param occ the times of occurance of a word
	* @return the node has been found, which matches the requirement
	*/
	TreeNode * search(TreeNode * node, char *word, int occ);
	/**
	* Clean every single node of a tree
	* @param root the root of the tree
	*/
	void clear(Tree root);
	/**
	* read a file 
	* @param filename the file to be open
	*/
	void readFile(char *filename);
	/**
	* Load a file to the binary tree. In other words, insert every single word to the tree
	* @param ptr the point of the start of the file name
	*/
	void Load(char *ptr);
	/**
	* Search for the node that matches with the word and the time of occurance
	* @param ptr the point of the start of the word
	* @return success or error
	*/
	int Locate(char *ptr);
	/**
	* Clear a tree
	* @param ptr the pointer to check whether the user input is a valid command
	*/
	void New(char *ptr);
};

#endif
