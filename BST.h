// Binary Search Tree
#ifndef BST_H
#define BST_H

#include <iostream>
#include <list>

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

#endif