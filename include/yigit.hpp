#ifndef YIGIT_HPP
#define YIGIT_HPP

#include <iostream>

class yigitDugum{
	public:
		int item;
		yigitDugum *next;
		
		yigitDugum(const int& item,yigitDugum *next);
};

class yigit 
{
	public:
		yigitDugum *topOfStack;
	
		yigit();
		bool isEmpty()const;
		void push(const int& item);
		void pop();
		const int& top()const;
		void makeEmpty();
		~yigit();
};

#endif