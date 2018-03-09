#ifndef HEADERGUARD
#define HEADERGUARD
#include <iostream>

using namespace std;

class Node {
 public:
  Node(int number);
  //Setters
  void setLeft(Node* node);
  void setRight(Node* node);
  void setParent(Node* node);
  void setNum(int newNum);
  //Getters
  Node* getLeft();
  Node* getRight();
  Node* getParent();
  int getNum();
 private:
  Node* left = NULL;
  Node* right = NULL;
  Node* parent = NULL;
  int num = -1;
};

#endif
