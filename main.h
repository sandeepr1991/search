/* 
 * File:   main.h
 * Author: sandeep
 *
 * Created on September 4, 2014, 9:27 AM
 */

#ifndef MAIN_H
using namespace std;
#include<string>
#include<deque>
#include<queue>
#define	MAIN_H
#define MAX_NODES 1000   //Maximum number of intermediate nodes
#define MAX_LINE    2048//Maximum number of characters in a line
struct node 
{
    string node_Name;
    int distance;
    bool reached;
    int position;
    deque<string> Output;
};


#endif	/* MAIN_H */

