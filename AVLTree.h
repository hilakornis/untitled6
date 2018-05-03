//
// Created by idobu on 30/04/2018.
//

#ifndef DSWET1_AVLTREE_H
#define DSWET1_AVLTREE_H
#include <iostream>
#include <cstddef>
typedef enum {INSERT_SUCCESS,INSERT_ALREADY_EXISTS,INSERT_MEMORY_ERROR} InsertResult;
typedef enum {REMOVE_SUCCESS,REMOVE_NOT_FOUND} RemoveResult;
template <class Key,class Data,class Compare>
class AVLTree {
public:
    explicit AVLTree(const Compare &c):root(NULL),key_compare(c) {}
    InsertResult insert(const Key &k,const Data &d) {
        if(!root) {
            root=new AVLTreeNode(k,d,key_compare);
            if(!root) return INSERT_MEMORY_ERROR;
            return INSERT_SUCCESS;
        }
        return root->insert(k,d);

    }
    RemoveResult remove(const Key &k) {
        if(!root) return REMOVE_NOT_FOUND;
        return root->remove(k);
    }
    Data find(const Key &k) {
        if(!root) return NULL;
        return &(*(root->find(k)));
    }
    void printInOrder() {
        if(!root) {
            std::cout << "empty";
            return;
        }
        root->printInOrder();
        std::cout << std::endl;
    }
    void printPreOrder() {
        if(!root) {
            std::cout << "empty";
            return;
        }
        root->printPreOrder();
        std::cout << std::endl;
    }
private:
    class AVLTreeNode {
        public:
            AVLTreeNode(const Key &k, const Data &d, AVLTreeNode *father):key(k),key_compare(father->key_compare),
                                                              left_son(NULL),right_son(NULL),
                                                              father(father),height(1),balance(0){
                value=new Data(d);
            }

            AVLTreeNode(const Key &k, const Data &d, const Compare &c):key(k),key_compare(c), left_son(NULL),
                                                              right_son(NULL), father(NULL), height(1), balance(0){
                value=new Data(d);
            }

            InsertResult insert(const Key &k, const Data &d) {
                if(key_compare(k,key)==0) return INSERT_ALREADY_EXISTS;
                InsertResult result=INSERT_ALREADY_EXISTS;
                if(key_compare(k,key) > 0) {
                    if(right_son) {
                        if((*right_son).insert(k,d)!=INSERT_SUCCESS) return result;
                    } else {
                        right_son=new AVLTreeNode(k,d,this);
                        if(right_son == NULL) return INSERT_MEMORY_ERROR;
                    }
                } else {
                    if(key_compare(k,key) < 0) {
                        if(left_son) {
                            if((*left_son).insert(k,d)!=INSERT_SUCCESS) return result;
                        } else {
                            left_son=new AVLTreeNode(k,d,this);
                            if(left_son == NULL) return INSERT_MEMORY_ERROR;
                        }
                }
                }
                this->updateHeightAndBalance();
                roll();
                return INSERT_SUCCESS;
            }

            Data *find(const Key &k) {
                if(key_compare(k,key) > 0 && right_son) return right_son->find(k);
                if(key_compare(k,key) < 0 && left_son) return left_son->find(k);
                if(key_compare(k,key) == 0) return value;
                return NULL;
            }

            RemoveResult remove(const Key &k) {
                RemoveResult result = REMOVE_NOT_FOUND;
                if (key_compare(k, key) > 0) {
                    if (!right_son) return REMOVE_NOT_FOUND;
                    if (right_son->remove(k) == REMOVE_NOT_FOUND) return REMOVE_NOT_FOUND;
                } else {
                    if (key_compare(k, key) < 0) {
                        if (!left_son) return REMOVE_NOT_FOUND;
                        if (left_son->remove(k) == REMOVE_NOT_FOUND) return REMOVE_NOT_FOUND;
                    }
                }
                if (key_compare(k, key) != 0) {
                    updateHeightAndBalance();
                    roll();
                    return REMOVE_SUCCESS;
                }
                if (right_son && left_son) {
                    Key new_key;
                    Data *new_value;
                    int remove_son;
                    right_son->replaceAndRemove(&new_key, &new_value,&remove_son);
                    if(remove_son==1) {
                        delete right_son;
                        right_son=NULL;
                    }
                    key = new_key;
                    value = new_value;
                    updateHeightAndBalance();
                    roll();
                } else {
                    if (!right_son) replaceWithLeftSon();
                    if (!left_son) replaceWithRightSon();
                }
                return REMOVE_SUCCESS;
            }

            void printInOrder() {
                if(left_son) left_son->printInOrder();
                std::cout << *value << " ";
                if(right_son) right_son->printInOrder();
            }

            void printPreOrder() {
                std::cout << *value << " ";
                if(left_son) left_son->printPreOrder();
                if(right_son) right_son->printPreOrder();
            }

            ~AVLTreeNode() {
                delete value;
            }
        private:
            Key key;
            Compare key_compare;
            Data *value;
            AVLTreeNode *left_son;
            AVLTreeNode *right_son;
            AVLTreeNode *father;
            int height;
            int balance;
            void updateHeightAndBalance() {
                if(!left_son && !right_son) {
                    height=1;
                    balance=0;
                    return;
                }
                if(!left_son) {
                    height = 1 + right_son->height;
                    balance = 0 - right_son->height;
                    return;
                }
                if(!right_son) {
                    height = 1 + left_son->height;
                    balance=left_son->height;
                    return;
                }
                (*left_son).height>(*right_son).height? height=1+(*left_son).height : height=1+(*right_son).height;
                balance=(*left_son).height - (*right_son).height;
            }
            void roll() {
                switch(balance) {
                    case 2:
                        if(left_son->balance==-1) left_son->rollL();
                        rollR();
                        break;
                    case -2:
                        if(right_son->balance==1) right_son->rollR();
                        rollL();
                        break;
                    default: break;
                }
            }
            void rollL() {
                AVLTreeNode *left=left_son;
                AVLTreeNode *mid=right_son->left_son;
                AVLTreeNode *right=right_son->right_son;

                Key key_temp=key;
                Data *value_temp=value;
                key=right_son->key;
                value=right_son->value;
                right_son->key=key_temp;
                right_son->value=value_temp;

                left_son=right_son;
                right_son=right;
                if(right_son) right_son->father=this;
                left_son->right_son=mid;
                if(left_son->right_son) mid->father=left_son;
                left_son->left_son=left;
                if(left_son->left_son) left->father=left_son;

                if(left_son) left_son->updateHeightAndBalance();
                updateHeightAndBalance();
            }
            void rollR() {
                AVLTreeNode *right = right_son;
                AVLTreeNode *mid = left_son->right_son;
                AVLTreeNode *left = left_son->left_son;

                Key key_temp=key;
                Data *value_temp=value;
                key=left_son->key;
                value=left_son->value;
                left_son->key=key_temp;
                left_son->value=value_temp;

                right_son=left_son;
                left_son=left;
                if(left_son) left_son->father=this;
                right_son->left_son=mid;
                if(right_son->left_son) mid->father=right_son;
                right_son->right_son=right;
                if(right_son->right_son) right->father=right_son;

                if(right_son) right_son->updateHeightAndBalance();
                updateHeightAndBalance();
            }
            void replaceWithRightSon() {
                key=right_son->key;
                value=right_son->value;
                height=right_son->height;
                balance=right_son->balance;
                AVLTreeNode *to_remove=right_son;
                left_son=right_son->left_son;
                right_son=right_son->right_son;
                delete to_remove;
            }
            void replaceWithLeftSon() {
                key=left_son->key;
                value=left_son->value;
                height=left_son->height;
                balance=left_son->balance;
                AVLTreeNode *to_remove=left_son;
                left_son=left_son->left_son;
                right_son=left_son->right_son;
                delete to_remove;
            }
            void replaceAndRemove(Key *new_key, Data **new_value,int *remove_son) {
                if(!left_son) {
                    *new_key=key;
                    *new_value=new Data(*value);
                    if(right_son) {
                        replaceWithRightSon();
                    } else {
                        *remove_son=1;
                    }
                    return;
                }
                left_son->replaceAndRemove(new_key,new_value,remove_son);
                if(*remove_son==1) {
                    delete left_son;
                    left_son=NULL;
                    *remove_son=0;
                }
                updateHeightAndBalance();
                roll();
            }
    };
    AVLTreeNode *root;
    Compare key_compare;
};
#endif //DSWET1_AVLTREE_H
