#include "yigit.hpp"

yigitDugum::yigitDugum(const int& item,yigitDugum *next=NULL){
	this->item = item;
	this->next = next;
}

yigit::yigit(){
	topOfStack=NULL;
}

bool yigit::isEmpty()const{
	return topOfStack == NULL;
}

void yigit::push(const int& item){
	topOfStack	= new yigitDugum(item,topOfStack);
}

void yigit::pop(){
	if(isEmpty()) throw "Stack is Empty";
	yigitDugum *tmp = topOfStack;
	topOfStack = topOfStack->next;
	delete tmp;
}

const int& yigit::top()const{
	if(isEmpty()) throw "Stack is Empty";
	return topOfStack->item;
}

void yigit::makeEmpty(){
	while(!isEmpty()) pop();
}

yigit::~yigit(){
	makeEmpty();
}