#include <iostream>
#include <bits/stdc++.h>
using namespace std;
/**

1.left left

         z                                      y
        / \                                   /   \
       y   T4      Right Rotate (z)          x      z
      / \          - - - - - - - - ->      /  \    /  \
     x   T3                               T1  T2  T3  T4
    / \
  T1   T2

2.left right
     z                               z                           x
    / \                            /   \                        /  \
   y   T4  Left Rotate (y)        x    T4  Right Rotate(z)    y      z
  / \      - - - - - - - - ->    /  \      - - - - - - - ->  / \    / \
T1   x                          y    T3                    T1  T2 T3  T4
    / \                        / \
  T2   T3                    T1   T2

3.right right
  z                                y
 /  \                            /   \
T1   y     Left Rotate(z)       z      x
    /  \   - - - - - - - ->    / \    / \
   T2   x                     T1  T2 T3  T4
       / \
     T3  T4

4.right left
   z                            z                            x
  / \                          / \                          /  \
T1   y   Right Rotate (y)    T1   x      Left Rotate(z)   z      y
    / \  - - - - - - - - ->     /  \   - - - - - - - ->  / \    / \
   x   T4                      T2   y                  T1  T2  T3  T4
  / \                              /  \
T2   T3                           T3   T4


*/
struct node
{
    int value;
    int height;
    node* left;
    node* right;
    node()
    {
        height=0;
        left=NULL;
        right=NULL;
    }
    node (int v)
    {
        value=v;
        height=1;
        left=NULL;
        right=NULL;
    }
    void UpdateHeight()
    {
        int leftheigh=0;
        int rightheigh=0;
        if(left!=NULL)
            leftheigh=left->height;
        if(right!=NULL)
            rightheigh=right->height;
        height=1+max(leftheigh,rightheigh);
    }
    int balancefactor()
    {
        int leftheigh=0;
        int rightheigh=0;
        if(left!=NULL)
            leftheigh=left->height;
        if(right!=NULL)
            rightheigh=right->height;
        int ret=leftheigh-rightheigh;
        return ret;
    }
};

node* rightrotation(node*& z)
{
    node* y=z->left;
    node* t3=NULL;
    if(y!=NULL)
     t3=y->right;
    y->right=z;
    z->left=t3;

    z->UpdateHeight();
    y->UpdateHeight();

    return y;
}

node* leftrotation(node*& z)
{
    node* y=z->right;
    node* t2=NULL;
    if(y!=NULL);
     t2=y->left;
    y->left=z;
    z->right=t2;

    z->UpdateHeight();
    y->UpdateHeight();

    return y;
}





node* balance(node*& curr)
{
    if(curr->balancefactor()==2)   ///left
    {
        if(curr->left->balancefactor()==-1)   ///if this condition is valid so it is left right
            curr->left=leftrotation(curr->left);   ///here i convert it to left left

        /// when i do this i am pretty sure that i am in left left case so i convert it to a balance tree
        curr=rightrotation(curr);
    }

    else if(curr->balancefactor()==-2)///right
    {

        if(curr->right->balancefactor()==1)  ///if this condition is valid so it is right left
            curr->right=rightrotation(curr->right);    /// here i convert it to right right

        ///when i do this i am pretty sure that i am in right right case so i convert it a balance tree
        curr=leftrotation(curr);
    }
    return curr;
}

node* Insert(node*& curr, int val)
{

        if (curr==NULL)
        {
            return new node(val);
        }
        else if (val<=curr->value)
        {
            curr->left=Insert(curr->left,val);
        }
        else
        {
            curr->right=Insert(curr->right,val);
        }

       curr->UpdateHeight();
        curr=balance(curr);

        return curr;
}

//void Delete(node*& root)  ///we will give it the pointer node we want to delete it , not the value , and after deleting we will call balance function given the root
//{
//    node*prev;
//    node*temp=root;
//    if(root->right==NULL)
//    {
//        root=root->left;
//    }
//    else if(root->left==NULL)
//    {
//        root=root->right;
//    }
//    else{
//        temp=root->left;
//        prev=root;
//        while(temp-right!=NULL)
//        {
//            prev=temp;
//            temp=temp->right;
//        }
//        root->value=temp->value;
//        if(prev==root)
//            prev->left=temp->left;
//        else prev->right=temp->left;
//    }
//    delete temp;
//
//}

void preorder(node*& root)
{
    if(root!=NULL){
    cout<<root->value<<" ";
    preorder(root->left);
    preorder(root->right);
    }
}

void inorder(node* root)
{
    if(root!=NULL){
    inorder(root->left);
    cout<<root->value<<" ";
    inorder(root->right);
    }
}

void postorder(node* root)
{
    if(root!=NULL){
    postorder(root->left);
    postorder(root->right);
    cout<<root->value<<" ";
    }
}


int main()
{
   node* root=NULL;

   root=Insert(root, 10);
   Insert(root, 20);
   Insert(root, 30);
   Insert(root, 40);
   Insert(root, 50);
   Insert(root, 60);
   Insert(root, 70);
      Insert(root, 80);
   Insert(root, 90);



   preorder(root);
    return 0;
}
