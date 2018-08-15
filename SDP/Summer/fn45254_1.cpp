#include <stdio.h>

struct Node
{
  int data;
  Node *next;

  Node(int data, Node *next)
  {
    this->data = data;
    this->next = next;
  }
};

void clean(Node *root);
void print(Node *root);
Node *rearange(Node *root);

int main()
{
  Node *root = new Node(1, nullptr);
  Node *curr = root;

  for (int i = 2; i <= 50; ++i)
  {
    curr->next = new Node(i, nullptr);
    curr = curr->next;
  }

  root = rearange(root);
  print(root);
  clean(root);
}

Node *rearange(Node *root)
{
  Node *curr = root;
  Node *evenRoot = nullptr, *evenRunner = nullptr;
  Node *oddRoot = nullptr, *oddRunner = nullptr;

  while (curr)
  {
    if (curr->data % 2 == 0)
    {
      if (!evenRoot)
        evenRunner = evenRoot = curr;
      else
        evenRunner = evenRunner->next = curr;
    }
    else
    {
      if (!oddRoot)
        oddRunner = oddRoot = curr;
      else
        oddRunner = oddRunner->next = curr;
    }
    curr = curr->next;
  }

  oddRunner->next = nullptr;

  if (!evenRoot)
    return oddRoot;
  else
    evenRunner->next = oddRoot;

  return evenRoot;
}

void clean(Node *root)
{
  Node *prev = root, *current = root;

  while (current)
  {
    current = current->next;
    delete prev;
    prev = current;
  }
}

void print(Node *root)
{
  while (root)
  {
    printf("%d ", root->data);
    root = root->next;
  }
}