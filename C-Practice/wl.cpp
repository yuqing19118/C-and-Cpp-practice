/**
* @wl.cpp
* @author Qing (Sabrina) Yu
* @UW Campus ID 9070146981 
* @email qyu37@wisc.edu 
* @version 1.0
*
* @section LICENSE
*
*
* @section DESCRIPTION This program follows the user input to load, locate, new 
* and end. It has several functions which are to insert new word from a file to 
* a binary search tree, to find the specific word from the tree.
*
* The time class represents a moment of time.
*/

#include "wl.h"
#include <cstring>
#include <cstdio>
#include <fstream>

using namespace std;


/**
* Insert interface function
* @param word a word from the file to be inserted to the tree
* @param n an input location of a word from the file
* @return the total number of nodes have been inserted
*/
int BSTree::insert_interface(const char *word, int n)
{


	if (word[0] == 0) return n;
	
	root = insert_recursion(root, word, n);
	return n+1;
}
/**
* Insert recursive function 
* @param node a new node to insert
* @param word a word from the file to be inserted to the tree
* @param n the location of a word from the file
* @return the total number of nodes have been inserted
*/
TreeNode * BSTree::insert_recursion(TreeNode * node, const char *word, int n)
{
	if (node == NULL){
		node = new TreeNode(word, n);
		return node;
	}
	if (strcmp(word,node->word) <= 0) {
		node->left=insert_recursion(node->left, word, n);
	} else {
		node->right = insert_recursion(node->right, word, n);
	}
	return node;
}

/**
* Search function which search a node with a key
* @param node a node which contains the word to be searched
* @param word a word from the file to be searched to the tree
* @param occ the times of occurance of a word
* @return the node has been found, which matches the requirement
*/
TreeNode * BSTree::search(TreeNode * node, char *word, int occ)
{
	if (node == NULL)
		return NULL;

	if (strcmp(word, node->word) == 0)
	{
		occ--;
		if (occ == 0)
		{
			return node;
		}
		else
		{
			return search(node->left, word, occ);
		}
	}
	else if (strcmp(word, node->word) < 0)
	{
		return search(node->left, word, occ);
	}
	else
	{
		return search(node->right, word, occ);
	}

	return NULL;
}

/**
* Clean every single node of a tree
* @param root the root of the tree
*/
void BSTree::clear(Tree root)
{
	if (root == NULL)
		return;
	if (root->left != NULL)
		clear(root->left);
	if (root->right != NULL)
		clear(root->right);

	free(root->word);
	delete root; 
	if (root == this->root) {
		this->root = NULL;
	}
}

/**
* Check if everything is a character from a-z, A-Z, 0-9 or ', if not, treat it as a space
* @param c the character to be checked
* @return True if it is not a legal character, which will be considered as space. False if it is legal. 
*/
bool is_Space(char c)
{
	if (!(c >= 'a' && c <= 'z') && !(c >= 'A' && c <= 'Z') && !(c >= '1' && c <= '9') && c != '\'') {
		return true;
	}
	else {
		return false;
	}
}

/**
* Check whether words are ascii.
* @param p the pointer to character to be checked
* @return True if it is a word character. False if it cannot be considered as a word. 
*/
bool is_Word(char *p)
{
	while (!is_Space(*p))
		p++;

	return (strlen(p) == 0);
}

/**
* Check whether the input is a number.
* @param p the pointer to character to be checked
* @return True if it is a number. False if it cannot be considered as a number. 
*/

bool is_Num(char *p)
{
	while ((*p >= '0' && *p <= '9'))
		p++;

	return (strlen(p) == 0);
}

/**
	* read a file 
	* @param filename the file to be open
*/
void BSTree::readFile(char * filename)
{

	std::string sub = "";
	int count = 1;

	if (filename[strlen(filename) - 1] == '\n')
		filename[strlen(filename) - 1] = '\0';
	ifstream inputfile(filename);

	if (!inputfile)
	{
		cout << "No file called '" << filename << "' has been found" << endl;
		return;
	}

	while (!inputfile.eof())
	{
		inputfile >> sub;
		std::string word = "";
		if (inputfile.fail())
			break;
		if (sub.length() != 0){
			for (unsigned int i = 0; i < sub.length(); i++){
				if (!is_Space(sub[i])){
					word.push_back(sub[i] | 32);
				}
				else {
					count = insert_interface(word.c_str(), count);
					word.clear();
				}
			}
			count = insert_interface(word.c_str(), count);
		}
	}

	inputfile.close();

}
/**
	* Load a file to the binary tree. In other words, insert every single word to the tree
	* @param ptr the point of the start of the file name
*/
void BSTree::Load(char * ptr)
{
	if (*ptr != ' ' || *ptr == '\n')
	{
		cout << "ERROR:invalid command." << endl;
	}
	else
	{
		while (*ptr == ' ')
			ptr++;
		readFile(ptr);
	}
}

/**
	* Search for the node that matches with the word and the time of occurance
	* @param ptr the point of the start of the word
	* @return success or error
*/
int BSTree::Locate(char *ptr)
{
	if ( *ptr != ' ' || *ptr == '\n')
	{
		cout << "ERROR:invalid command." << endl;
	}
	else
	{

		char word[20] = "";
		int occ = 0;
		while (*ptr == ' ' )
			ptr++;
		char * p = strtok(ptr, " \n");
		if (p == NULL)
		{
			cout << "ERROR:invalid command." << endl;
			return -1;
		}
		else if (!is_Word(p))
		{
			cout << "ERROR:invalid command." << endl;
			return -1;
		}

		strcpy(word, p);

		p = strtok(NULL, " \n\t");
		if (p == NULL)
		{
			cout << "ERROR:invalid command." << endl;
			return -1;
		}
		else if (atoi(p)<=0)
		{
			cout << "ERROR: The number of occurance is not a possitive number" << endl;
			return -1;
		}

		occ = atoi(p);

		TreeNode * ptr = search(root, word, occ);

		if (ptr == NULL)
		{
			cout << "No matching entry." << endl;
		}
		else
		{
			cout << ptr->loc << endl;
		}

	}
	return 0;
}
/**
	* Clear a tree
	* @param ptr the pointer to check whether the user input is a valid command
*/
void BSTree::New(char *s)
{
	while (*s == ' ') s++;
	if (*s != '\n')
	{
		cout << "ERROR:invalid command." << endl;
	}
	else
	{
		clear(root);
	}
}

/**
* Main function which parses users input and check command which will be called accordingly.
* @param argc number of inputs passed in
* @param argv all users inputs
* @return 0 if the program succeeds.
*/
int main(int argc, char ** argv)
{

	BSTree task;
	
	while (1)
	{
		char buffer[1024] = "";
		char *p = NULL;


		cout << ">";
		fflush(stdout);
		fgets(buffer, 1024, stdin);

		if (strlen(buffer) <= 0 || buffer[0] == '\n')
			return 0;

		for (unsigned int i = 0; i < strlen(buffer); i++){
			buffer[i] = tolower(buffer[i]);
		}

		p = buffer;
		std::string words;
		std::string command;
		for (unsigned int i = 0; i < strlen(buffer); i++){
			if (buffer[i] != ' ' && buffer[i] != '\n'){
				words.push_back(buffer[i]);
			}
			else{
				command = words;
				words.clear();
				break;
			}
		}
		if (command.compare("load") == 0) {
			task.Load(p + 4);
		}
		else if (command.compare("new") == 0) {
			task.New(p + 3);
		}
		/**< clear the tree and exit the program */
		else if (command.compare("end") == 0) {
			task.New(p + 3);
			return(0);
		}
		else if (command.compare("locate") == 0) {
			task.Locate(p + 6);
		}
		else {
			cout << "ERROR:invalid command." << endl;
		}
	}
	return 0;

}
