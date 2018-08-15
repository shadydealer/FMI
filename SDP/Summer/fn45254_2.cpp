#include <stdio.h>
#include <limits.h>

struct Node
{
  int data;
  Node *left;
  Node *right;

  Node(int rhs_data,
       Node *rhs_left,
       Node *rhs_right) : data(rhs_data),
                          left(rhs_left),
                          right(rhs_right)
  {
  }
};

void clean(Node * root);
bool isBst(Node * root, int min, int max);
bool isFull(Node* root);
void genBinaryTree(Node * root, int from, int to);

int main()
{
  Node * root = new Node(0, nullptr, nullptr);
  genBinaryTree(root, 1,6);
  
  printf("%d\n",isBst(root, INT_MIN, INT_MAX));
  printf("%d\n",isFull(root));
  
  clean(root);
}

void clean(Node *root)
{
  while (root)
  {

    if (root->right)
      clean(root->right);

    if (root->left)
      clean(root->left);

    delete root;
    root = nullptr;
  }
}

void genBinaryTree(Node * root, int from, int to)
{
  if (from > to) return ;

  if(from <= to)
  {
    root->left = new Node(from+=1, nullptr, nullptr);
  }
  
  if(from <= to)
  {
    root->right = new Node(from+=2, nullptr, nullptr);
  }
  printf("%d\n", from);

  genBinaryTree(root->left, from, to);
  genBinaryTree(root->right, from, to);
}

bool isBst(Node *root, int min, int max)
{
  if(!root) return true;
  if(root->data < min || root->data > max) return false;
  
  //left subtree nodes can't have a larger value than the current nodes value
  //and right subtree nodes can't have aa smaller value than the current nodes value +1
  //the + 1 is to ensure that elements that have values >= the current nodes value are in the left subtree
  //and elements that have values < the current nodes value are in the right subtree
  return isBst(root->left, min, root->data) && isBst(root->right, root->data +1, max);
}

bool isFull(Node* root)
{
  if(!root->left && !root->right)
    return true;

  else if(root->left && root->right)
    return isFull(root->left) && isFull(root->right);
 
  return false;
}