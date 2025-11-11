#ifndef _laiba_ali_binary_tree_array_implementation_09
#define _laiba_ali_binary_tree_array_implementation_09

#include <iostream>
#include <string>
#include <cmath>
#include "queue/queue.h"
using namespace std;

template <typename t>
class binaryTREE
{
   int height;
   t *data;
   bool *status;
   void helperRemoval(int index)
   {
      if (index >= this->size())
      {
         return;
      }
      helperRemoval(2 * index + 1);
      helperRemoval(2 * index + 2);
      status[index] = false;
   }
   void preorder(int index)
   {
      if (index >= this->size())
      {
         return;
      }
      if (status[index] == true)
      {
         cout << data[index];
         preorder(2 * index + 1);
         preorder(2 * index + 2);
      }
   }
   void postorder(int index)
   {
      if (index >= this->size())
      {
         return;
      }
      if (status[index] == true)
      {
         postorder(2 * index + 1);
         postorder(2 * index + 2);
         cout << data[index];
      }
   }
   void inorder(int index)
   {
      if (index >= this->size())
      {
         return;
      }
      if (status[index] == true)
      {
         inorder(2 * index + 1);
         cout << data[index];
         inorder(2 * index + 2);
      }
   }

public:
   binaryTREE(int h)
   {
      status = new bool[int(pow(2, h) - 1)](); // all elements initalized by false
      height = h;
      data = new t[int(pow(2, h) - 1)];
   }
   void setRoot(t v)
   {
      if (status[0] == false)
      {
         data[0] = v;
         status[0] = true;
      }
   }
   t getRoot()
   {
      if (status[0] == false)
      {
         throw "no root exsist";
      }
      return data[0];
   }

   ~binaryTREE()
   {
      delete[] data;
      delete[] status;
   }
   void setLeft(t parent, t val);
   t getLeft(t parent);
   void setRight(t parent, t val);
   t getRight(t parent);
   void remove(t parent);
   void removeSubtree(t parent);
   int search(t val);
   void preOrder();
   void inOrder();
   void levelOrder();
   void postOrder();
   int searchParent(t child);
   int size()
   {
      return (int(pow(2, height) - 1));
   }

   // task 15
   void displayLevel(int levelNo)
   {
      if (this->size() < (pow(2, levelNo) - 1))
      {
         cout << "out of bound" << endl;
      }
      else
      {
         int start = int(pow(2, levelNo) - 1);
         int end = int(pow(2, levelNo + 1) - 1);
         for (int i = start; i < end; i++)
         {
            if (status[i] == true)
            {
               cout << data[i];
            }
         }
      }
   }
   int findLevelOfNode(t node)
   {
      int index_node = -1;
      for (int i = 0; i < this->size(); i++)
      {
         if (data[i] == node)
         {
            index_node = i;
            break;
         }
      }
      if (index_node == -1)
      {
         cout << "node value not matched";
         return 0;
      }
      else
      {
         for (int i = 0; i < this->size(); i++)
         {
            if (((pow(2, i) - 1) < index_node && index_node < (pow(2, i + 1) - 1)))
            {
               index_node = i;
               break;
            }
         }
      }
      return index_node;
   }
   // task 8
   void displayAncestors(t node)
   {
      int curr_node = -1;
      for (int i = 0; i < this->size(); i++)
      {
         if (data[i] == node)
         {
            curr_node = i;
            break;
         }
      }
      if (curr_node == -1)
      {
         cout << "value not found" << endl;
         return;
      }
      else
      {
         int parent_index = curr_node;
         while (parent_index > 0)
         {
            int parent = (parent_index - 1) / 2;
            if (status[parent] == true)
            {
               cout << data[parent] << " ";
            }
            parent_index = parent;
         }
      }
      return;
   }
   // task 9
   void displayDescendents(t node)
   {
      int index;
      for (int i = 0; i < this->size(); i++)
      {
         if (data[i] == node && status[i] == true)
         {
            index = i;
            break;
         }
      }
      if (status[2 * index + 1] == true)
      {
         preorder(2 * index + 1);
      }
      if (status[2 * index + 2] == true)
      {
         preorder(2 * index + 2);
      }
      // preorder(index);
   }
   // task 10
   void heightOfTree()
   {
      int count = 1;
      for (int i = 0; i < this->size(); i = i * 2 + 1)
      {
         if (status[2 * i + 1] == true || status[2 * i + 2] == true)
         {
            count = count + 1;
         }
      }
      cout << count << endl;
   }
   // last task
   void helperparenthesis(int index)
   {
      if (index >= this->size()||status[index] == false)
      {
         return;
      }
      if (status[index] == true)
      {
         cout << data[index];
         if (status[2 * index + 1] == true || status[2 * index + 2]==true)
         {
            cout << "(";
         
        
      helperparenthesis(2 * index + 1);
         // if(status[2 * index + 1] == false || status[2 * index + 2]==false)
         cout << ",";
      helperparenthesis(2 * index + 2);
         // if(status[2*index+2]==true)
         // {
         cout << ")";
         }
         // }
      }
       
   }
   void displayParenthesizedView()
   {
      helperparenthesis(0);
   }
};

template <typename t>
void binaryTREE<t>::setLeft(t parent, t val)
{
   for (int i = 0; i < this->size(); i++)
   {
      if (status[i] == true && data[i] == parent)
      {
         if ((2 * i + 1) < this->size())
         {
            data[2 * i + 1] = val;
            status[2 * i + 1] = true;
            return;
         }
      }
   }
}
template <typename t>
t binaryTREE<t>::getLeft(t parent)
{
   for (int i = 0; i < this->size(); i++)
   {
      if (data[i] == parent)
      {
         if ((2 * i + 1) < this->size())
         {
            return data[2 * i + 1];
         }
      }
   }
}
template <typename t>
void binaryTREE<t>::setRight(t parent, t val)
{
   for (int i = 0; i < this->size(); i++)
   {
      if (status[i] == true && data[i] == parent)
      {
         if ((2 * i + 2) < this->size())
         {
            data[2 * i + 2] = val;
            status[2 * i + 2] = true;
            return;
         }
      }
   }
}
template <typename t>
t binaryTREE<t>::getRight(t parent)
{
   for (int i = 0; i < this->size(); i++)
   {
      if (data[i] == parent)
      {
         if ((2 * i + 2) < this->size())
         {
            return data[2 * i + 2];
         }
      }
   }
}
template <typename t>
void binaryTREE<t>::preOrder()
{
   this->preorder(0);
}
template <typename t>
void binaryTREE<t>::inOrder()
{
   this->inorder(0);
}
template <typename t>
void binaryTREE<t>::levelOrder()
{
   for (int i = 0; i < this->size(); i++)
   {
      if (status[i] == true)
      {
         cout << data[i] << " ";
      }
   }
}
template <typename t>
void binaryTREE<t>::postOrder()
{
   this->postorder(0);
}
template <typename t>
void binaryTREE<t>::remove(t parent)
{
   for (int i = 0; i < this->size(); i++)
   {
      if (data[i] == parent && status[i] == true)
      {
         status[i] = false;
         return;
      }
   }
}
template <typename t>
void binaryTREE<t>::removeSubtree(t parent)
{
   int index_parent;
   for (int i = 0; i < this->size(); i++)
   {
      if (status[i] == true && data[i] == parent)
      {
         index_parent = i;
         this->helperRemoval(i);
         return;
      }
   }
}
template <typename t>
int binaryTREE<t>::search(t val)
{
   int index = -1;
   for (int i = 0; i < this->size(); i++)
   {
      if (data[i] == val && status[i] == true)
      {
         index = i;
      }
   }
   if (index == -1)
   {
      throw "value not found(search)";
   }
   return index;
}
// search for the parent index for the given chid value;
template <typename t>
int binaryTREE<t>::searchParent(t child)
{
   int parent_index = -1;
   for (int i = 0; i < this->size(); i++)
   {
      if (status[i] == true && data[i] == child)
      {
         parent_index = (i - 1) / 2;
         break;
      }
   }
   if (parent_index < 0)
   {
      throw "no parent exsists";
   }
   return parent_index;
}
#endif