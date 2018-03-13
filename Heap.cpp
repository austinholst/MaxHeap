#include <iostream>
#include "Node.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

void treeBuild(Node* &head, Node* nodeArray[100], int counter); 
void Heapify(Node* node1, Node* node2, Node* head);
void remove(Node* head, Node* nodeArray[200], int counter);
void printTree(Node* head, int space);
void swap(Node* current);

int main() {
  Node* nodeArray[100];  
  //char input[200];
  char answer[20];
  int* numbers = new int[200];
  int counter = 0;
  Node* head = new Node(NULL);

  cout << "Would you like to input numbers 'manually' or input from a 'file'?" << endl;
  cin.getline(answer, 20);
  
  //If the user wants to input numbers manually
  if(strcmp(answer, "manually") == 0) {
    cout << "Input up to 100 numbers with spaces in between each number" << endl;
    char input[200];
    cin.getline(input, 200);
    //Putting the numbers in an int array
    for(int i = 0; i < strlen(input); i++) {
      int start = i;
      int length = 1;
      //Go until the next character is a space	
      while(input[i + 1] != char(32) && i < strlen(input)) {
	length++;
	i++;
      }
      //Make a char with the number in it
      char* charNum = new char[length];
      for(int j = 0; j < length; j++) {
	charNum[j] = input[start + j];
      }
      //Turn the char into an int
      numbers[counter] = atoi(charNum);
      //Add to the total amount of numbers
      counter++;
    }
    //Set the 0 index of the node array to null (So the index dividing stuff works)
    nodeArray[0] = NULL;
    //Putting the number into a node and the node into an array of nodes
    for(int i = 0; i < counter; i++) {
      Node* newNode = new Node(numbers[i]);
      nodeArray[i + 1] = newNode;
    }
    treeBuild(head, nodeArray, counter);
    printTree(head, 0);
    cout << "" << endl;
    remove(head, nodeArray, counter);
  }
  //If the user wants to input numbers from a file
  else if(strcmp(answer, "file") == 0) {
    cout << "What is the name of the file you wish to read in from (be sure to add the .txt)" << endl;
    char fileName[100];
    //Take in the name of the file	  
    cin >> fileName;	  
    char input[200];
    //Set the file to the user input
    ifstream myFile(fileName);
    //If the file is opened correctly
    if(myFile.is_open()) {
      myFile.getline(input, 200);
      //Close the file
      myFile.close();
      //From here on down it's the same as the manual input
      for(int i = 0; i < strlen(input); i++) {
	int start = i;
	int length = 1;
	while(input[i + 1] != char(32) && i < strlen(input)) {
	  length++;
	  i++;
	}
	char* charNum = new char[length];
	for(int j = 0; j < length; j++) {
	  charNum[j] = input[start + j];
	}
	numbers[counter] = atoi(charNum);
	counter++;
      }
      nodeArray[0] = NULL;
      for(int i = 0; i < counter; i++) {
	Node* newNode = new Node(numbers[i]);
	nodeArray[i + 1] = newNode;
      }
      treeBuild(head, nodeArray, counter);
      printTree(head, 0);
      remove(head, nodeArray, counter);
    }
    //If there was an error getting the file(couldn't find the file or something like that)
    else {
     cout << "Unable to load file" << endl;
    }
  }
  //if the user didn't type file or manually
  else {
    cout << "That wasn't one of the options" << endl;
  }
  
  return 0;
}

//Build the tree
void treeBuild(Node* &head, Node* nodeArray[200], int counter) {
  for(int i = 1; i < counter + 1; i++) {
    //set the first index to the head
    if(i == 1) {
      head = nodeArray[i];
    }
    else {
      //Current node's index divided by two equals index of parent
      int parent = -1;
      parent = trunc(i / 2);
      //If the parent has no left child, set all the connections and heapify that number
      if(nodeArray[parent]->getLeft() == NULL) {;
	nodeArray[parent]->setLeft(nodeArray[i]);
	nodeArray[i]->setParent(nodeArray[parent]);
	Heapify(nodeArray[parent], nodeArray[i], head);
      }
      //If the parent does have a left child, set it to the right and heapify it
      else {
	nodeArray[parent]->setRight(nodeArray[i]);
	nodeArray[i]->setParent(nodeArray[parent]);
	Heapify(nodeArray[parent], nodeArray[i], head);
      }
    }
  }
}

//After you swap data call the funciton again on the parent of the data you swapped
void Heapify(Node* node1, Node* node2, Node* head) {
  //If the second node is larger than the first, swap them
  if(node2->getNum() > node1->getNum()) {
    int temp = node2->getNum();
    node2->setNum(node1->getNum());
    node1->setNum(temp);
    //If the node is not the head, keep on going
    if(node1->getNum() != head->getNum()) {
      swap(node1->getParent(), node2->getParent(), head);
    }
  }
}

//Remove the nodes from the tree while printing out from largest to smallest
void remove(Node* head, Node* nodeArray[200], int counter) {
  Node* current = head;
  counter = counter;
  //For loop goes down so it starts at the last node added to the tree and then goes down
  for(counter; counter > 0; counter--) {
    //swap the head with the last node added
    int temp = head->getNum();
    head->setNum(nodeArray[counter]->getNum());
    nodeArray[counter]->setNum(temp);
    cout << nodeArray[counter]->getNum() << " ";
    //Delete the node that was swapped
    delete nodeArray[counter];
    //Set the parent-child connection to NULL
    if(nodeArray[counter]->getParent() == NULL) {
      head == NULL;
    }
    else if(nodeArray[counter]->getParent()->getLeft() == nodeArray[counter]) {
      nodeArray[counter]->getParent()->setLeft(NULL);
    }
    else if(nodeArray[counter]->getParent()->getRight() == nodeArray[counter]) {
      nodeArray[counter]->getParent()->setRight(NULL);
    }
    //Check if head has no children, if it only has a left child, then if it has two childs
    if(head->getLeft() == NULL && head->getRight() == NULL) {
      head->setNum(head->getNum());
    }
    //Check if the right node is null in which case you only have to check the left
    else if(head->getRight() == NULL) {
      if(head->getLeft()->getNum() > head->getNum()) {
        //Swap the node with the one on the left then swap it until it's in the right place in the tree
	int temp = head->getNum();
        head->setNum(head->getLeft()->getNum());
        head->getLeft()->setNum(temp);
	current = head->getLeft();
        swap(current);
      }
    }
    //Check if the the left node is bigger than the right node or they are the same
    else if(head->getLeft()->getNum() > head->getRight()->getNum() ||
       head->getLeft()->getNum() == head->getRight()->getNum()) {
      if(head->getLeft()->getNum() > head->getNum()) {
	//swap the node with the one on the left and then swap it until it's in the right place in the tree
	int temp = head->getNum();
	head->setNum(head->getLeft()->getNum());
	head->getLeft()->setNum(temp);
	current = head->getLeft();
	swap(current);
      }
    }
    //Check if the right node is bigger than the left
    else if(head->getRight()->getNum() > head->getLeft()->getNum()) {
      if(head->getRight()->getNum() > head->getNum()) {
        //Swap the node and then keep swapping until its in the right place in the tree
	int temp = head->getNum();
	head->setNum(head->getRight()->getNum());
	head->getRight()->setNum(temp);
	current = head->getRight();
	swap(current);
      }
    }
  }  
}

//Print out the tree
void printTree(Node* head, int space) {
  if(head == NULL) {
    return;
  }
  space += 10;
  printTree(head->getRight(), space);
  
  printf("\n");
  for(int i = 10; i < space; i++) {
     printf(" ");
  }
   printf("%d\n", head->getNum());
  printTree(head->getLeft(), space);
}

//Function for swapping data in nodes to put them down the tree. (basically reverse heapify)
void swap(Node* current) {
  while(current->getLeft() != NULL && current->getRight() != NULL) {
    if(current->getLeft()->getNum() > current->getRight()->getNum()
       || current->getLeft()->getNum() == current->getRight()->getNum()) {
      int temp2 = current->getNum();
      current->setNum(current->getLeft()->getNum());
      current->getLeft()->setNum(temp2);
      current = current->getLeft();
    }
    else if(current->getRight()->getNum() > current->getLeft()->getNum()) {
      int temp2 =current->getNum();
      current->setNum(current->getRight()->getNum());
      current->getRight()->setNum(temp2);
      current = current->getRight();
    }
    else {
      break;
    }
  }
}
