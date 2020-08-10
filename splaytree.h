#ifndef splayBST_H
#define splayBST_H

#include <iostream>
#include <cstdlib>
#include <string>
#include "bst.h"

/**
* A special kind of node for an splay tree, which adds the
balance as a data member, plus
* other additional helper functions. You do NOT need to
implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class splayNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    splayNode(const Key& key, const Value& value, splayNode<Key,
              Value>* parent);
    virtual ~splayNode();

    // Getter/setter for the node's height.
    char getBalance () const;
    void setBalance (char balance);
    void updateBalance(char diff);

    // int setHeight(splayNode<Key, Value> *n);

// Getters for parent, left, and right. These need to be redefined since they
// return pointers to splayNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual splayNode<Key, Value>* getParent() const override;
    virtual splayNode<Key, Value>* getLeft() const override;
    virtual splayNode<Key, Value>* getRight() const override;

protected:
    char balance_;
};

/*
--------------------------------------------
Begin implementations for the splayNode class.
--------------------------------------------
*/

/**
* Constructor for an splayNode. Nodes are initialized with a balance of 0.
*/
template<typename Key, typename Value>
splayNode<Key, Value>::splayNode(const Key& key, const Value& value,
                                 splayNode<Key, Value>* parent)
    : Node<Key, Value>(key, value, parent),
      balance_(0)
{

}

/**
* Destructor.
*/
template<typename Key, typename Value>
splayNode<Key, Value>::~splayNode()
{

}

/**
* A getter for the balance of a splayNode.
*/
template<class Key, class Value>
char splayNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a splayNode.
*/
template<class Key, class Value>
void splayNode<Key, Value>::setBalance(char balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a splayNode.
*/
template<class Key, class Value>
void splayNode<Key, Value>::updateBalance(char diff)
{
    balance_ += diff;
}

/**
* Getter function for the parent. Used since the node
inherits from a base node.
*/
template<typename Key, typename Value>
splayNode<Key, Value>* splayNode<Key, Value>::getParent() const
{
    return static_cast<splayNode<Key, Value>*>(this->mParent);
}

/**
* Getter function for the left child. Used since the node
inherits from a base node.
*/
template<typename Key, typename Value>
splayNode<Key, Value>* splayNode<Key, Value>::getLeft() const
{
    return static_cast<splayNode<Key, Value>*>(this->mLeft);
}

/**
* Getter function for the right child. Used since the node
inherits from a base node.
*/
template<typename Key, typename Value>
splayNode<Key, Value>* splayNode<Key, Value>::getRight() const
{
    return static_cast<splayNode<Key, Value>*>(this->mRight);
}

/*
------------------------------------------
End implementations for the splayNode class.
------------------------------------------
*/

/**
* A templated balanced binary search tree implemented as an splay tree.
*/
template <typename Key, typename Value, typename Comp = std::less<Key> >
class splayTree : public BinarySearchTree<Key, Value>
{
public:
    splayTree(const Comp& c = Comp());
    // Methods for inserting/erasing (removing) elements from the tree.
    // You must implement both of these methods.
    virtual void insert(const std::pair<Key, Value>& keyValuePair) override;
    virtual void erase(const Key& key);
    void splayprint() const ;


private:
    /* Helper functions are strongly encouraged to help separate the problem
       into smaller pieces. You should not need additional data members. */

    /* You should write these helpers for sure.  You may add others. */
    void rotateLeft (splayNode<Key, Value> *n);
    void rotateRight (splayNode<Key, Value> *n);
    bool isRight(splayNode<Key, Value> *n);
    bool isLeft(splayNode<Key, Value> *n);
    void splay(splayNode<Key, Value> *n);
    void removeFix(splayNode<Key, Value> *curr, int temp);
    /* A provided helper function to swap 2 nodes location in the tree */
    void nodeSwap( splayNode<Key, Value>* n1, splayNode<Key, Value>* n2);
    splayNode<Key, Value> *succ(splayNode<Key, Value> *n);
    Comp c_;
    // splayNode<Key, Value>* returnSucc(splayNode<Key, Value> *curr);
};

/*
--------------------------------------------
Begin implementations for the splayTree class.
--------------------------------------------
*/

/**
* Insert function for a key value pair. Finds location to insert the
 node and then balances the tree.
*/

template <typename Key, typename Value, typename Comp>
splayTree<Key, Value, Comp>::splayTree(const Comp& c) : c_(c) {}


template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::insert(const std::pair<Key, Value>& keyValuePair)
{



    splayNode<Key, Value> *node = new splayNode<Key, Value>(keyValuePair.first,
            keyValuePair.second, NULL);

    //this checks to see if the root is null; first node
    if (BinarySearchTree<Key, Value>::mRoot == NULL) {
        //checks to see if there is even a root
        BinarySearchTree<Key, Value>::mRoot = node;
        return;
    }


    splayNode<Key, Value> *newParent = NULL;

    //casting BST node to an splay node
    splayNode<Key, Value> *currNode =
        static_cast<splayNode<Key, Value>*>(this->mRoot);


    while (currNode != NULL) { //going until the current node is not null
        //update the parent each run
        newParent = currNode;
        //if the value key already exists in the function,
        if (keyValuePair.first == newParent->getKey()) {
            newParent->setValue(keyValuePair.second);
            return;
        }
        //checks to see if the value of the curr is less than the parent
        //to see which side it goes on. either Right or left
        else if (keyValuePair.second < newParent->getValue()) {
            if (newParent->getLeft() == NULL) {
                newParent->setLeft(node);
                node->setParent(newParent);
                break;
            }
            currNode = newParent->getLeft();
        }
        else  {
            //if all else is false insert the node
            if (newParent->getRight() == NULL) {
                newParent->setRight(node);
                node->setParent(newParent);
                break;
            }
            currNode = newParent->getRight();
        }

    }
    // Setting the baalance of the parent node
    if (newParent->getBalance() == -1 || newParent->getBalance() == 1) {
        newParent->setBalance(0);
    }
    else {
        if (newParent->getLeft() == node) {
            newParent->setBalance(-1);
        }
        else {
            newParent->setBalance(1);
        }
        //at the end we need to adjust the nodes in order to balance

    }

    splay(node);

    // }
}

/**
* Erase function for a given key. Finds the node, reattaches pointers,
and then balances when finished.
*/
template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::erase(const Key & key) {
    //Cast a BST node to an splay NODE
    splayNode<Key, Value> *curr =
        static_cast<splayNode<Key, Value>*>(this->internalFind(key));
    if (curr == NULL) {
        return; //Could not find Node
    }

    splay(curr);
//Initialize the parent node
    splayNode<Key, Value> *currParent = curr->getParent();


    //Making sure the left Node is not NULL
    if (curr->getLeft() != NULL) {

        if (curr->getRight() != NULL) {
            if (curr == BinarySearchTree<Key, Value>::mRoot) {
                splayNode<Key, Value> *temp = succ(curr);
                nodeSwap(curr, temp);
            }
            else {
                splayNode<Key, Value> *successor = succ(curr);
                nodeSwap(curr, successor);
            }

        }

    }
    //Making sure that the curr node does not have any leaf nodes
    if (curr->getLeft() == NULL && curr->getRight() == NULL) {
        if (currParent == NULL) {
            this->mRoot = NULL;
            return;
        }
        else if (curr == currParent->getLeft()) {
            currParent->setLeft(NULL);
        }
        else if (curr == currParent->getRight()) {
            currParent->setRight(NULL);
        }

    }

    splayNode<Key, Value> *node = curr->getLeft();

    if (curr->getRight() != NULL) {
        node = curr->getRight();
    }

    if (node != NULL) {
        node->setParent(currParent);
    }
    if (currParent == NULL) { //if our parent is null,
        //set the root to our current node
        BinarySearchTree<Key, Value>::mRoot = node;
    }
    else {
        if (curr == currParent->getLeft()) {
            currParent->setLeft(node);
        }
        else {
            currParent->setRight(node);
        }

    }
    delete curr;
}


/**
* Rotates n down and to the left
*/



template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::rotateLeft (splayNode<Key, Value> *n)
{

    //ROATE LEFT FUNCTION

    splayNode<Key, Value> *rightChild = n->getRight();

    if (rightChild->getLeft() != NULL) {
        n->setRight(rightChild->getLeft());
        rightChild->getLeft()->setParent(n);
    }
    else {
        n->setRight(NULL);
    }
    if (n->getParent() == NULL) {

        rightChild->setParent(NULL);
        n->setParent(rightChild);
        BinarySearchTree<Key, Value, Comp>::mRoot = rightChild;

    }
    else {

        splayNode<Key, Value> *grand = n->getParent();
        if (grand->getRight() == n) {
            rightChild->setParent(grand);
            grand->setRight(rightChild);
        }
        else {
            rightChild->setParent(grand);
            grand->setLeft(rightChild);
        }
    }
    rightChild->setLeft(n);
}


//Checks to see if grand is the root



template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::rotateRight (splayNode<Key, Value> *n)
{
    //this function rotates the current node to the right
    splayNode<Key, Value> *leftChild = n->getLeft();

    splayNode<Key, Value> *grand = n->getParent();
    //checks to make sure that the grand node is actually infact
    //the root node
    //if it is then set the left child = the grade
    //So then we can expand the tree

    if (leftChild->getRight() != NULL) {
        n->setLeft(leftChild->getRight());
        leftChild->getRight()->setParent(n);
    }
    else {
        n->setLeft(NULL);
    }


    if (grand == NULL) {
        leftChild->setParent(NULL);
        n->setParent(leftChild);
        BinarySearchTree<Key, Value>::mRoot = leftChild;
    }
    else {
        if (grand->getRight() == n) {
            leftChild->setParent(grand);
            grand->setRight(leftChild);
        }
        else {
            leftChild->setParent(grand);
            grand->setLeft(leftChild);
        }
        n->setParent(leftChild);
    }

    leftChild->setRight(n);
}



template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::splay(splayNode<Key, Value> *curr) {
     if (BinarySearchTree<Key, Value, Comp>::mRoot == curr)
    {

        return;
    }

       
        if (curr->getParent()->getParent() == NULL)
        {
            if(curr->getParent()->getLeft() == curr) {
                rotateRight(curr->getParent());
            } else {
                rotateLeft(curr->getParent());
            }
            return;
        }
        else
        {
            if (curr->getParent()->getParent()->getLeft() == curr->getParent())
            {
                if(curr->getParent()->getLeft() == curr) {
                    rotateRight(curr->getParent()->getParent());
                    rotateRight(curr->getParent());
                    splay(curr);
                } else {
                    rotateLeft(curr->getParent());
                    rotateRight(curr->getParent()->getParent());
                    splay(curr);
                }
 
            } else {
                if(curr->getParent()->getLeft() == curr) {
                    rotateRight(curr->getParent());
                    rotateLeft(curr->getParent()->getParent());
                    splay(curr);
                } else {
                    rotateLeft(curr->getParent()->getParent());
                    rotateLeft(curr->getParent());
                    splay(curr);
                }
            }   
        }
}



template <typename Key, typename Value, typename Comp>
bool splayTree<Key, Value, Comp>::isRight(splayNode<Key, Value> *n) {
    //Checks if the node is a right child
    //If it is it will return true.
    //if it is not it will return false

    if (n->getParent()->getRight() == n) {
        return true;
    }
    else {
        return false;
    }

}

template <typename Key, typename Value, typename Comp>
bool splayTree<Key, Value, Comp>::isLeft(splayNode<Key, Value> *n) {
    //Checks if the node is a right child
    //If it is it will return true.
    //if it is not it will return false

    if (n->getParent()->getLeft() == n) {
        return true;
    }
    else {
        return false;
    }

}

template <typename Key, typename Value, typename Comp>
splayNode<Key, Value>* splayTree<Key, Value, Comp>::succ(splayNode<Key, Value> *n) {
    //Returns the sucessor of the current node passed in

    if (n->getRight() != NULL) {
        n = n->getRight();
        while (n->getLeft() != NULL) {
            n = n->getLeft();
        }
        return n;
    }

    splayNode<Key, Value> *currParent = n->getParent();
    while (currParent != NULL && n == currParent->getRight()) {
        n = currParent;
        currParent = currParent->getParent();
    }
    return currParent;
}



/**
 * Given a correct splay tree, this functions relinks the
  tree in such a way that
 * the nodes swap positions in the tree.  Balances
 are also swapped.
 */
template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::nodeSwap( splayNode<Key, Value>* n1,
        splayNode<Key, Value>* n2)
{
    if ((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if (n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if (n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    char temp2 = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(temp2);

    if ( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if ( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if ( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if ( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }
    if (n1p != NULL && n1p != n2) {
        if (n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if (n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if (n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if (n2p != NULL && n2p != n1) {
        if (n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if (n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if (n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if (this->mRoot == n1) {
        this->mRoot = n2;
    }
    else if (this->mRoot == n2) {
        this->mRoot = n1;
    }

}

template <typename Key, typename Value, typename Comp>
void splayTree<Key, Value, Comp>::splayprint() const {
    this->print();
}

// ------------------------------------------
// End implementations for the splayTree class.
// ------------------------------------------


#endif
