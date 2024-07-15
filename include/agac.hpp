#ifndef AGAC_HPP
#define AGAC_HPP

#include <iostream>
#include <cmath>
#include "yigit.hpp"

class agacDugum{
	public:
		int data;
		agacDugum *left;
		agacDugum *right;
		int height;
	
		agacDugum(const int& vr,agacDugum *sl,agacDugum *sg);
};

class agac
{
	public:
		agacDugum *root;
		int  AVLToplamDugumDeger;
	
		agac();	
		~agac();
		int Height();
		void Clear();
		bool isEmpty()const;	
		bool Search(const int& item);
		bool Search(agacDugum *subNode,const int& item);
		agacDugum* SearchAndAdd(agacDugum *subNode,const int& item);
		agacDugum* SwapWithLeftChild(agacDugum *subNode);
		agacDugum* SwapWithRightChild(agacDugum *subNode);
		bool DeleteNode(agacDugum *&subNode);
		int Height(agacDugum*subNode);
		void Add(const int& item);
		void yaprakmi(agacDugum* subNode, yigit* Yigit);
		void yaprakmi(yigit* Yigit);
};

#endif