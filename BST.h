#ifndef BST_H
#define BST_H

#include <iostream>
#include <list>
#include <cmath>

using namespace std;

template <class T, class K>
using getKey = K (*)(const T&);

template <class K>
using cmpKey = int (*)(const K&, const K&);

template <class T, class K>
class BST{
	public:
	BST(getKey<T,K> gK, T data, cmpKey<K> cK);
	~BST();
	void setLeftChild(BST<T, K> *pBinTree){pLeft=pBinTree;}
	void setRightChild(BST<T, K> *pBinTree){pRight=pBinTree;}
	BST<T, K> *getLeftChild()const{return pLeft;}
	BST<T, K> *getRightChild()const{return pRight;}
	void insert(T newdata);
	void insert(list<T> dataList);
	T *find(K key);
	template <class U, class V>
	friend ostream &operator <<(ostream &OS, const BST<U, V> &bst);
	private:
	BST<T, K> *pLeft=NULL;
	BST<T, K> *pRight=NULL;
	T data;
	K m_key;
	getKey<T,K> gK; // function that takes data as an argument and returns its key
	cmpKey<K> cK; // function that compares two keys
};

template <class T, class K>
BST<T,K>::BST(getKey<T,K> gK, T data, cmpKey<K> cK):data{data}, m_key{(*gK)(data)}, cK{cK}, gK{gK}{
}

template <class T, class K>
BST<T,K>::~BST(){
	if (pLeft) delete pLeft;
	if (pRight) delete pRight;
}

template <class T, class K>
void BST<T, K>::insert(T newdata){
	if ((*cK)(m_key, (*gK)(newdata))<=0){
		if (pLeft) pLeft->insert(newdata);
		else{
			BST<T, K> *Tree = new BST<T, K>(gK, newdata, cK);
			pLeft = Tree;
		}
	}
	else{
		if (pRight) pRight->insert(newdata);
		else{
			BST<T, K> *Tree = new BST<T, K>(gK, newdata, cK);
			pRight = Tree;
		}
	}
}

template <class T, class K>
void BST<T,K>::insert(list<T> datalist){
	for (auto elem: datalist) insert(elem);
}

template <class T, class K>
T* BST<T, K>::find(K key){
	if ((*cK)(m_key, key)==0) return &data;
	else if((*cK)(m_key, key)<0){
		if (pLeft) pLeft->find(key);
		else return nullptr;
	}
	else {
		if (pRight) pRight->find(key);
		else return nullptr;
	}

}

template <class U, class V>
ostream &operator<<(ostream &OS, const BST<U, V> &bst){
	static int currentgeneration=0;
	static int printedItems=0;

	static list<BST<U, V>*> queue{};
	OS << bst.data << "\t";
	printedItems++;
	if (printedItems==pow(2,currentgeneration)){
		printedItems=0;
		currentgeneration++;
		cout << endl;
	}
	queue.push_back(bst.pLeft);
	queue.push_back(bst.pRight);
	while (!queue.empty()){
		BST<U, V> *tree = queue.front();
		queue.pop_front();
		if (tree) OS << *tree;
		else {
			OS << "NULL" << "\t";
			printedItems++;
		}
	}
	return OS;
}

#endif
