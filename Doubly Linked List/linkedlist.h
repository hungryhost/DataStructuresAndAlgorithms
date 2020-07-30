#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include "node.h"
#include <fstream>
#include <iostream>
#include "dish.h"
#include<bits/stdc++.h>
template <class T>
class LinkedList{
public:
    LinkedList();
    LinkedList(const LinkedList<T>& otherList);
    ~LinkedList();
    void insert(T node);
    void printlist();
    void getdinner( double n_energy, std::string filename);
    std::vector<std::string> searchNodeByEnergy(double n_energy);
    void accessNode();
    void removeNode(T node);
    void removeAllNodes();
    int size();
    Node<T> gethead();
    void getFromFile();
    void returnToFile();
    std::vector<std::string> assertionByNode();
    friend class dish;
    friend class Node<T>;

    class iterator;
    iterator begin(){
        return(head);
    }
    iterator end(){
        Node<T>* ptr = nullptr;
        return(ptr);
    }
    class iterator {
    private: Node<T> *pt;
    public:

        iterator() : pt(0) {}
        iterator(const Node<T>* pNode) noexcept :
                pt(pNode) { }

                iterator& operator=(Node<T>* pNode)
                {
                    this->m_pCurrentNode = pNode;
                    return *this;
                }
        iterator (Node<T> *pn) : pt(pn) {}
        bool operator!=(const iterator& iterator)
                {
                    return pt != iterator.pt;
                }
        std::string operator*(){return pt->data->name;}
        iterator& operator++(){
            pt = pt->next;
            return *this;
        }
        iterator operator++(int){
            iterator tmp = *this;
            pt = pt->next;
            return tmp;
        }
        iterator operator--(){
            pt = pt->prev;
            return *this;
        }
        iterator operator--(int){
            iterator tmp = *this;
            pt = pt->prev;
            return tmp;
        }
        friend class Node<T>;
    };

    Node<T> *head;

};
template <class T>
LinkedList<T>::LinkedList() : head(0){}
template <class T>
LinkedList<T>::~LinkedList(){
    Node<T> *node = head;
    Node<T> *tempNode;
    while (node != nullptr){
        tempNode = node;
        node = node->next;
        delete tempNode;
    }
}
template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherList)
{
    Node<T>* node = otherList.head;
    head = nullptr;
    while (node != nullptr) {
        insert(node->data);
        node = node->next;
    }
}
template <class T>
void LinkedList<T>::getFromFile(){
    std::string line;
    double line1 = NULL, line2= NULL, line3= NULL, line4= NULL, line5= NULL, line6= NULL;
    int line7 = NULL;
    std::fstream finas;
    /* add filepath here: finas.open(); */
    while(!finas.eof())
    {
        finas >> line >> line1 >> line2 >> line3 >> line4 >> line5 >> line6 >> line7;
        Dish *s1 = new Dish(line, line1, line2, line3, line4, line5, line6, line7);
        insert(s1);
    }
    finas.close();
}
template <class T>
void LinkedList<T>::returnToFile(){
    Node<T> *tempNode = new Node<T>();
    std::fstream finas;
    tempNode = head;
    /* add filepath here: finas.open(); */
    while(tempNode!=nullptr)
    {
        finas << tempNode->data->name<< "\n"<< tempNode->data->weight<< "\n"<< tempNode->data->fats<< "\n" << tempNode->data->proteins << "\n"<< tempNode->data->carbs
              << "\n" << tempNode->data->acids << "\n"<< tempNode->data->cellulose<< "\n" << tempNode->data->energy<< "\n";
        tempNode=tempNode->next;
    }

    finas.close();
}
template <class T>
Node<T> LinkedList<T>::gethead(){
    return head;
}
template <class T>
void LinkedList<T>::insert(T node){
    Node<T> *newNode = new Node<T>();
    newNode->data = node;
    Node<T> *currNode = new Node<T>();
    currNode = head;
    if (head == nullptr){
        head = newNode;
        return;}
    // if the node is to be inserted at the beginning
    // of the doubly linked list
    else if ((head)->data->energy >= newNode->data->energy) {
        newNode->next = head;
        newNode->next->prev = newNode;
        head = newNode;
        return;
    }

    else {
        currNode = head;

        // locate the node after which the new node
        // is to be inserted
        while (currNode->next != NULL &&
               currNode->next->data->energy < newNode->data->energy){
            currNode = currNode->next;
        }
        /* Make the appropriate links */
        newNode->next = currNode->next;

        // if the new node is not inserted
        // at the end of the list
        if (currNode->next != NULL){
            newNode->next->prev = newNode;
        }
        currNode->next = newNode;
        newNode->prev = currNode;
    }
}

template <class T>
void LinkedList<T>::removeNode(T node){
    Node<T> *tempNode, *tempNode2;
    if (head == nullptr){
        return;
    }
    else if (head->data == node || head->data->name == node->name) {
        tempNode = head;
        if (head->next != nullptr){
            head = head->next;
            head -> prev = nullptr;
            delete tempNode;
            tempNode = nullptr;
            return;
        }
        else {
            delete head;
            head = nullptr;
            delete tempNode;
            tempNode = nullptr;
            return;
        }
    }
    tempNode2 = head;
    while (tempNode2->next->next != nullptr) {
        if(tempNode2->next->data == node || tempNode2->data->name == node->name){
            tempNode = tempNode2->next;
            tempNode2->next = tempNode->next;
            tempNode->next->prev = tempNode2;
            delete tempNode;
            tempNode = nullptr;
            return;
        }
        tempNode2 = tempNode2->next;
    }
    if (tempNode2->next->data == node || tempNode2->data->name == node->name){
        tempNode = tempNode2->next;
        delete tempNode;
        tempNode = nullptr;
        tempNode2->next = nullptr;
        return;
    }
}
template <class T>
void LinkedList<T>::removeAllNodes(){
    Node<T> *temp;
    while(head != nullptr) //while the list is not empty
    {
        temp = head; //store the current node.
        head = head->next; //visit the next node
        if(temp->prev){
            temp->prev = nullptr;
        }
        if(temp->next){
            temp->next = nullptr;
        }
    }
}
template <class T>
void LinkedList<T>::printlist(){
    Node<T> *temp = head;
    if(temp == nullptr){
        std::cout << "list is empty\n";
        return;
    }
    if(temp->next == nullptr){
        std::cout<< temp->data->name << std::endl;
        std::cout << temp->data->energy << std::endl;
        return;
    }
    else {
        while (temp != nullptr){
            std::cout<< temp->data->name << std::endl;
            std::cout << temp->data->energy << std::endl;
            temp = temp->next;

        }
    }
}
template <class T>
int LinkedList<T>::size(){
    if (head == nullptr){
        return 0;
    }
    Node<T> *tmp = head;
    int nodeCounter = 0;
    while (tmp != nullptr) {
        nodeCounter+=1;
        tmp = tmp->next;
    }
    return nodeCounter;
}
template <class T>
std::vector<std::string> LinkedList<T>::searchNodeByEnergy(double n_energy){
    Node<T> *pt;
    pt = head;
    std::vector <std::string> dishes;
    if(pt == nullptr){
        dishes.push_back("None");
        return(dishes);
    }
    else{
        while(pt!=nullptr){
            if(pt->data->energy == n_energy || (pt->data->energy >= (n_energy-100) && (pt->data->energy <= (n_energy))) ||
                    (pt->data->energy > (n_energy) && (pt->data->energy <= (n_energy+100)))){
                dishes.push_back(pt->data->name);
            }
            pt = pt->next;
        }return(dishes);
    }
}
template <class T>
std::vector<std::string> LinkedList<T>::assertionByNode(){
    Node<T> *pt;
    pt = head;
    std::vector <std::string> dishes;
    if(pt==nullptr){
        dishes.push_back("None");
    }
    while(pt!=nullptr){
        dishes.push_back(pt->data->name);
        pt = pt->next;
    }return dishes;
}
template<class T>
void LinkedList<T>::getdinner(double n_energy, std::string filename){
    Node<T> *tempNode;
    tempNode = head;
    double sumenergy;
    std::fstream finas;
    double a = n_energy*0.4;
    double b = n_energy*0.4;
    double c = n_energy*0.2;
    bool flag1 = true, flag2 = true, flag3 = true;
    finas.open(filename, std::fstream::out );
    if(tempNode == nullptr){
        finas << "No such dinner found";
    }

    else {
        while (tempNode != nullptr){
            if (tempNode->data->energy <= a && tempNode->data->type == 1 && flag1 == true){
                finas << tempNode->data->name<< "\n"<< tempNode->data->weight<< "\n"
                      << tempNode->data->energy<< "\n";
                sumenergy+=tempNode->data->energy;
                flag1 = false;
            }
            if (tempNode->data->energy <= b && ((tempNode->data->name).find("������") != std::string::npos) && flag2 == true){

                finas << tempNode->data->name<< "\n"<< tempNode->data->weight<< "\n"<< tempNode->data->energy<< "\n";
                sumenergy+=tempNode->data->energy;
                flag2 = false;
             }
            if (tempNode->data->energy <= c && ((tempNode->data->name).find("������") != std::string::npos) && flag3 == true){

                finas << tempNode->data->name<< "\n"<< tempNode->data->weight<< "\n"<< tempNode->data->energy<< "\n";
                sumenergy+=tempNode->data->energy;
                flag3 = false;
             }
            tempNode = tempNode->next;
        } finas << "��������� ��. �������� " << sumenergy;
    }
}
#endif // LINKEDLIST_H
