/*
**  a4.cpp
**  Assignment 4, CMPT-225, Spring 2015
**  301215536 caz53 chenjian zhu
**/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

/************global variables*************************/
vector<int> list1(0);
vector<int> list2(0);

/***************function declaration******************/
void readFromFile();
void loadLists();



// read file from directory and load two lists
void loadLists()
{
	string file_path;
	fstream fs;
	while(true)
	{
		cout<<"please enter the file path:";
		cin>>file_path;
		// open file
		fs.open(file_path.c_str());
		if(fs.good())
			break;
		else
			cout<<"File "<<file_path<<" does not exist!"<<endl;
	}

	string input;
	bool start_read_list_2 = false;
	int element;
	while(!fs.eof())
	{
		// get input from next line
		getline(fs, input);
		try
		{
			// convert input element from string to int
			element = atoi(input.c_str());
		}
		catch(exception &e)
		{

		}
		// if read element 0, set start_read_list_2 to true
		if(element == 0)
		{
			start_read_list_2 = true;
			continue;
		}
		// insert into list1 if start_read_list_2 is false
		if(!start_read_list_2)
		{
			list1.push_back(element);
		}
		// insert into list2 if start_read_list_2 is true
		else
		{
			list2.push_back(element);
		}
	}
	// close file
	fs.close();
}


int main()
{
	// largest element meets requirements in assignment 4
	int largest_element = -1;
	loadLists();
	// use C++ STL heap algorithm
	make_heap(list1.begin(), list1.end());
	
	while(list1.size()!=0)
	{
		// get the largest element from the heap list1
		int current_element = list1.front();
		// pop the largest element from the heap
		pop_heap(list1.begin(), list1.end());
		// remove it from heap
		list1.pop_back();
		// if list2 contains current element
		if(find(list2.begin(), list2.end(), current_element) != list2.end())
		{
			//go to the next loop
			continue;
		}
		// if list2 does not contain current element
		else
		{
			// update the largest element and break the loop
			largest_element = current_element;
			break;
		}
	}
	/************************write to file**********************/
	ofstream os;
	os.open("output.txt");
	os<<"301215536 caz53 chenjian zhu\n";
	if(largest_element == -1)
	{
		os<<"None";
	}
	else
	{
		os<<largest_element;
	}
	os.close();
	return 0;
}

