#ifndef HASHT_H
#define HASHT_H
#include "iostream"
#include <fstream>

/* THIS IS A HASHTABLE IMPLEM. FOR LAB 2 PART 1
 * MIND THE USAGE OF AUTO
 * MIND THAT typedef IS USED IN MAIN FILE
 2019 YURY BORODIN */

const int hashTableSize = 10;

template<typename K, typename V>
struct node{
    K *key;
    V *value;
    node *next;
};

template<typename K, typename V>
class HashT {
public:

    HashT(){
        for(int i = 0; i < hashTableSize; i++){
            hashTable[i] = nullptr;
        }
    }

    HashT(HashT &hasht){
        for(int i = 0; i < hashTableSize; i++){
            if(hasht.hashTable[i]){
                this->hashTable[i] = new node<K, V>;
                this->hashTable[i]->key = new
                        K(*(hasht.hashTable[i]->key));
                this->hashTable[i]->value = new
                        V(*(hasht.hashTable[i]->value));
                this->hashTable[i]->next = nullptr;
                node<K, V> *curr = hasht.hashTable[i]->next;
                node<K, V> *thcurr = this->hashTable[i];
                while (curr) {
                    node<K, V> *tmp = new node<K, V>;
                    tmp->key = new K(*(curr->key));
                    tmp->value = new V(*(curr->value));
                    tmp->next = nullptr;
                    thcurr->next = tmp;
                    thcurr = thcurr->next;
                    curr = curr->next;
                }
                if(curr == nullptr)
                    delete curr;
            }
            else
                this->hashTable[i] = nullptr;
        }

    }

    ~HashT(){
        this->delAll();
    }

    void delAll(){
        for(int i = 0; i < hashTableSize; i++){
            recDel(this->hashTable[i]);
            if (this->hashTable[i])
                this->hashTable[i] = nullptr;
        }
    }

    void del(const K &key){
        int h = getHash(key);
        node<K, V> *n = this->hashTable[h];
        node<K, V> *prev = nullptr;
        while(n){
            auto nk = *n->key;
            if(nk == key){
                delete(n->key);
                delete(n->value);
                if (prev)
                    prev->next = n->next;
                else {
                    hashTable[h] = n->next;
                }
                n = nullptr;
            }
            else{
                prev = n;
                n = n->next;
            }
        }
        if(n == nullptr && prev == nullptr){
            delete n;
            delete prev;
        }
    }

    int count() const{
        int res = 0;
        for(int i = 0; i < hashTableSize; i++){
            node<K, V> *curr = this->hashTable[i];
            while (curr) {
                res++;
                curr = curr->next;
            }
            if(curr == nullptr){
                delete curr;
            }
        }
        return res;
    }
    void input(const std::string path){
        std::ifstream in;
        in.open(path);
        if (in.is_open()) {
            try{
                while (!in.eof()) {
                    K key;
                    V value;
                    in >> key >> value;
                    this->add(key, value);
                }
            } catch(...){}
            in.close();
        }
    }

    bool operator == (const HashT &hasht) const{
        bool flag = true;
        for(int i = 0; i < hashTableSize; i++){
            node<K, V> *curr = this->hashTable[i];
            node<K, V> *hcurr = hasht.hashTable[i];
            if (!curr xor !hcurr)
                flag = false;
            while (curr && hcurr) {
                if (!(curr && hcurr && *curr->key == *hcurr->key
                      && *curr->value == *hcurr->value))
                    flag = false;
                curr = curr->next;
                hcurr = hcurr->next;
            }
            if(!curr && !hcurr){
                delete curr;
                delete hcurr;
            }
        }
        return flag;
    }

    V& operator[](const K &key){
        node<K, V> *n = this->hashTable[getHash(key)];
        V none;
        while(n){
            auto nk = *n->key;
            if (nk == key)
                return *n->value;
            else
                n = n->next;
        }
        if(n == nullptr)
            delete n;
        return none;
    }
    void returnKeysByValue(const V &value, const std::string path){
        std::ofstream out(path);
        if (out.is_open()) {
            bool f = true;
            for(int i = 0; i < hashTableSize; i++){
                node<K, V> *s = this->hashTable[i];
                while (s) {
                    auto sv = *s->value;
                    if(sv == value){
                        if (f)
                            f = false;
                        else
                            out << std::endl;
                        if (i != 0)
                            out << *s->key << " " << *s->value;
                        s = s->next;
                    }
                    else s = s->next;
                }
                if(s == nullptr) delete s;
            }
        }
        out.close();
    }


    bool isInTable(const K &key) const{
        int h = getHash(key);
        node<K, V> *n = this->hashTable[h];
        while(n){
            auto nk = *n->key;
            if (nk == key)
                return true;
            else
                n = n->next;
        }
        delete n;
        return false;
    }

    void output(const std::string path) const{
        std::ofstream out(path);
        if (out.is_open()) {
            bool f = true;
            for(int i = 0; i < hashTableSize; i++){
                node<K, V> *s = this->hashTable[i];
                while (s) {
                    if (f)
                        f = false;
                    else
                        out << std::endl;
                    if (i != 0)
                        out << *s->key << " " << *s->value;
                    s = s->next;
                }
                if (s == nullptr) delete s;
            }
        }
        out.close();
    }

    void add(const K &key, const V &value) {
        if (!isInTable(key)) {
            node<K, V> *curr = new node<K, V>;
            curr->key = new K(key);
            curr->value = new V(value);
            curr->next = nullptr;
            int h = getHash(key);
            if (hashTable[h] == nullptr) {
                hashTable[h] = curr;
            } else {
                node<K, V> *tmp = hashTable[h];
                while (tmp->next)
                    tmp = tmp->next;
                tmp->next = curr;
                if(tmp == nullptr) delete tmp;
            }
            if (curr == nullptr) delete curr;

        }
        else {
            int h = getHash(key);
            node<K, V> *n = this->hashTable[h];
            while(n){
                auto nk = *n->key;
                if (nk == key){
                    *n->value = value;
                    return;
                }
                else{
                    n = n->next;
                }
            }
            delete n;
        }
    }

private:
    node<K, V> *hashTable[hashTableSize];
    int getHash(const K &key) const{
        std::hash<K> hash_fn;
        int h = hash_fn(key);
        return abs(h % hashTableSize);
    }
    void recDel(node<K, V> *n){
        if (n) {
            if (n->next)
                recDel(n->next);
            delete(n->key);
            delete(n->value);
            delete(n);
        }
    }
};
#endif // HASHT_H
