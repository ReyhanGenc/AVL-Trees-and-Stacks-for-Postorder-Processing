#include "agac.hpp"
#include <iostream>
#include <cmath>

using namespace std;
	
agacDugum::agacDugum(const int& vr,agacDugum *sl=NULL,agacDugum *sg=NULL){
	data = vr;
	left = sl;
	right = sg;
	height=0;
}
	
agacDugum* agac::SearchAndAdd(agacDugum *subNode,const int& item){
	if(subNode == NULL) subNode = new agacDugum(item);
	else if(item < subNode->data){
		subNode->left = SearchAndAdd(subNode->left,item);
				
		if(Height(subNode->left) == Height(subNode->right)+2){
			if(item < subNode->left->data)
				subNode = SwapWithLeftChild(subNode);
			else{
				subNode->left = SwapWithRightChild(subNode->left);
				subNode = SwapWithLeftChild(subNode);
			}
		}
	}
	else if(item > subNode->data){
		subNode->right = SearchAndAdd(subNode->right,item);
				
		if(Height(subNode->right) == Height(subNode->left)+2){
			if(item > subNode->right->data)
				subNode = SwapWithRightChild(subNode);
			else{
				subNode->right = SwapWithLeftChild(subNode->right);
				subNode = SwapWithRightChild(subNode);
			}
		}
	}
	else;	
		subNode->height = Height(subNode);
			return subNode;
}


agacDugum* agac::SwapWithLeftChild(agacDugum *subNode){
	agacDugum *tmp = subNode->left;
	subNode->left = tmp->right;
	tmp->right = subNode;
			
	subNode->height = Height(subNode);
	tmp->height = 1+max(Height(tmp->left),subNode->height);
	
	return tmp;
}


agacDugum* agac::SwapWithRightChild(agacDugum *subNode){
	agacDugum *tmp = subNode->right;
	subNode->right = tmp->left;
	tmp->left = subNode;
			
	subNode->height = Height(subNode);
	tmp->height = 1+max(Height(tmp->right),subNode->height);
			
	return tmp;

}
bool agac::DeleteNode(agacDugum *&subNode){
	agacDugum *delNode = subNode;
			
	if(subNode->right == NULL) subNode = subNode->left;
	else if(subNode->left == NULL) subNode = subNode->right;
	else{
		delNode = subNode->left;
		agacDugum *parentNode = subNode;
		while(delNode->right != NULL){
			parentNode = delNode;
			delNode = delNode->right;
		}
		subNode->data = delNode->data;
		if(parentNode == subNode) subNode->left = delNode->left;
		else parentNode->right = delNode->left;
		}
	delete delNode;
	return true;
}

int agac::Height(agacDugum* subNode){
	if(subNode == NULL) return -1;
	return 1+max(Height(subNode->left),Height(subNode->right));
}
		
bool agac::Search(agacDugum *subNode,const int& item){
	if(subNode == NULL) return false;
	if(subNode->data == item) return true;
	if(item < subNode->data) return Search(subNode->left,item);
	else return Search(subNode->right,item);
}

agac::agac(){
	root = NULL;
	AVLToplamDugumDeger=0;
}

bool agac::isEmpty()const{
	return root == NULL;
}

void agac::Add(const int& item){
	root = SearchAndAdd(root,item);
}

int agac::Height(){
	return Height(root);
}

bool agac::Search(const int& item){
	return Search(root,item);
}

void agac::Clear(){
	while(!isEmpty()) DeleteNode(root);
}

agac::~agac(){
	Clear();
}

void agac::yaprakmi(agacDugum* subNode, yigit* Yigit){
	if(subNode!= NULL) {
       
		// Eğer bir yapraksa bu düğüm döndürülür.
		if (subNode->left == NULL && subNode->right == NULL) {
			Yigit->push(subNode->data);
		}
	
		// Yaprak olmayan elemanların toplamları hesaplanır.
		else  AVLToplamDugumDeger+=subNode->data;
	
		yaprakmi(subNode->left, Yigit);
		yaprakmi(subNode->right, Yigit);
	}
}
void agac::yaprakmi(yigit* Yigit){
	yaprakmi(root,Yigit);
}