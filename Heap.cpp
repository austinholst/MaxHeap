#include <iostream>
#include "Node.h"
#include <stdlib.h>
#include <cstring>
#include <cmath>
#include <stdio.h>
#include <fstream>

using namespace std;

void treeBuild(Node* &head, Node* nodeArray[100], int counter); 
void swap(Node* node1, Node* node2, Node* head);
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
  
  if(strcmp(answer, "manually") == 0) {
    cout << "Input up to 100 numbers with spaces in between each number" << endl;
    char input[200];
    cin.getline(input, 200);
    //Putting the numbers in an int array
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
  else if(strcmp(answer, "file") == 0) {
    cout << "What is the name of the file you wish to read in from (be sure to add the .txt)" << endl;
    char fileName[100];
    cin >> fileName;
    char input[200];
    ifstream myFile(fileName);
    if(myFile.is_open()) {
      myFile.getline(input, 200);
      myFile.close();
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
    else {
     cout << "Unable to load file" << endl;
    }
  }
  else {
    cout << "That wasn't one of the options" << endl;
  }
  
  return 0;
}


void treeBuild(Node* &head, Node* nodeArray[200], int counter) {
  for(int i = 1; i < counter + 1; i++) {
    if(i == 1) {
      head = nodeArray[i];
    }
    else {
      int parent = -1;
      parent = trunc(i / 2);
      if(nodeArray[parent]->getLeft() == NULL) {;
	nodeArray[parent]->setLeft(nodeArray[i]);
	nodeArray[i]->setParent(nodeArray[parent]);
	swap(nodeArray[parent], nodeArray[i], head);
      }
      else {
	nodeArray[parent]->setRight(nodeArray[i]);
	nodeArray[i]->setParent(nodeArray[parent]);
	swap(nodeArray[parent], nodeArray[i], head);
      }
    }
  }
}

//After you swap data call the funciton again on the parent of the data you swapped
void swap(Node* node1, Node* node2, Node* head) {
  if(node2->getNum() > node1->getNum()) {
    int temp = node2->getNum();
    node2->setNum(node1->getNum());
    node1->setNum(temp);
    if(node1->getNum() != head->getNum()) {
      swap(node1->getParent(), node2->getParent(), head);
    }
  }
}

//Use the array length to find the most recent node added. Then just subtract one
void remove(Node* head, Node* nodeArray[200], int counter) {
  Node* current = head;
  counter = counter;
  for(counter; counter > 0; counter--) {
    int temp = head->getNum();
    head->setNum(nodeArray[counter]->getNum());
    nodeArray[counter]->setNum(temp);
    //cout << nodeArray[counter]->getNum() << " ";
    delete nodeArray[counter];
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
    else if(head->getRight() == NULL) {
      if(head->getLeft()->getNum() > head->getNum()) {
        int temp = head->getNum();
        head->setNum(head->getLeft()->getNum());
        head->getLeft()->setNum(temp);
	current = head->getLeft();
        swap(current);
      }
    }
    else if(head->getLeft()->getNum() > head->getRight()->getNum() ||
       head->getLeft()->getNum() == head->getRight()->getNum()) {
      if(head->getLeft()->getNum() > head->getNum()) {
	int temp = head->getNum();
	head->setNum(head->getLeft()->getNum());
	head->getLeft()->setNum(temp);
	current = head->getLeft();
	swap(current);
      }
    }
    else if(head->getRight()->getNum() > head->getLeft()->getNum()) {
      if(head->getRight()->getNum() > head->getNum()) {
	int temp = head->getNum();
	head->setNum(head->getRight()->getNum());
	head->getRight()->setNum(temp);
	current = head->getLeft();
	swap(current);
      }
    }
  }  
}

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

void swap(Node* current) {
  while(current->getLeft() != NULL && current->getRight() != NULL) {
    if(current->getLeft()->getNum() > current->getRight()->getNum()
       || current->getLeft()->getNum() == current->getRight()->getNum()) {
      cout << "Before swap" << endl;
      cout << "Current: " << current->getNum() << endl;
      cout << "Other: " << current->getLeft()->getNum() << endl;
      int temp2 = current->getNum();
      current->setNum(current->getLeft()->getNum());
      current->getLeft()->setNum(temp2);
      cout << "After swap" << endl;
      cout << "Current: " << current->getNum() << endl;
      cout << "Other: "<< current->getLeft()->getNum() << endl;
      current = current->getLeft();
    }
    else if(current->getRight()->getNum() > current->getLeft()->getNum()) {
      cout << "Before swap" << endl;
      cout << "Current: " << current->getNum() << endl;
      cout << "Other: "<< current->getRight()->getNum() << endl;
      int temp2 =current->getNum();
      current->setNum(current->getRight()->getNum());
      current->getRight()->setNum(temp2);
      cout << "After swap" << endl;
      cout << "Current: " << current->getNum() << endl;
      cout << "Other: "<< current->getRight()->getNum() << endl;
      current = current->getRight();
    }
    else {
      break;
    }
  }
}
