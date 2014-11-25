/* 
 * File:   main.cpp
 * Author: sandeep
 *
 * Created on September 3, 2014, 7:21 PM
 */


#include <iostream>
#include <fstream>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include "main.h"

#define MAX_NODES 1000   //Maximum number of intermediate nodes
#define MAX_LINE    2048//Maximum number of characters in a line

int bfs(int distance[][MAX_NODES],deque <struct node *>& queued,deque <struct node *>& visited,int number_Of_nodes,string destination,string nodes[]);
int dfs(int distance[][MAX_NODES],stack<struct node *>& stacked,deque<struct node *>& visited,int number_Of_Nodes,string destination,string nodes[]);
int ucs(int distance[][MAX_NODES],deque<struct node *>& visited,int number_Of_Nodes,string source_name,string destination,string nodes[]);
/*
 * 
 */
int main(int argc, char** argv) {
    
    
    int input_type=1,tmp,tmp1;
    int distance[MAX_NODES][MAX_NODES];    
    char temp[150];
    ifstream is;
    ofstream os;
    string source;
    string destination;
    string nodes[MAX_NODES];
    deque <struct node *> queued;
    stack <struct node *> stacked;
    deque <struct node *> visited;
    int number_Of_Nodes;
    int task;
    os.open("output.txt",std::fstream::out);
    
    if((access("input.txt",F_OK))!=0){
        os.close();
        return 0;
    }
    is.open("input.txt",std::fstream::in);
    while(!(is.eof()) && input_type <7)
    {
        is.getline(temp,MAX_LINE);
        switch(input_type){
                case 1:task=atoi(temp);
                if(!(task==1 || task==2 || task==3))
                {
                    os << "Invalid task id,resetting to default:1";
                    task = 1;
                }
                input_type++;
                break;
                case 2 :source.assign(temp);
                if(source.empty())
                {
                    os << "Source is empty, can not continue execution";
                    is.close();
                    os.close();
                    return 0;
                }
                input_type++;
                break;
                case 3 :destination.assign(temp);
                if(destination.empty())
                {
                    os << "Destination is empty, can not continue execution";
                    is.close();
                    os.close();
                    return 0;
                }
                 input_type++;
                 break;
                 case 4:number_Of_Nodes=atoi(temp);
                 if(number_Of_Nodes<1 || number_Of_Nodes>MAX_NODES)
                 {
                     os<<"Wrong number of nodes,can not continue with execution";
                     is.close();
                     os.close();
                     return 0;
                 }
                 input_type++;
                 
                 case 5 :tmp=0;
                 
                 
                 while(tmp<number_Of_Nodes)
                 {
                     
                     is.getline(temp,MAX_LINE);
                     nodes[tmp++].assign(temp);
                     
                 }
                 input_type++;
               
                 //break;
                 case 6: for(tmp=0;tmp<number_Of_Nodes;tmp++){
                            for(tmp1=0;tmp1<number_Of_Nodes;tmp1++)
                            {
                                if(tmp1+1 != number_Of_Nodes)
                                is.getline(temp,MAX_LINE,' ');
                                else
                                   is.getline(temp,MAX_LINE); 
                                distance[tmp][tmp1]=atoi(temp);
                                
                                if( distance[tmp][tmp1]<0){
                                    os << "Negative distances are not allowed";
                                    is.close();
                                    os.close();
                                    return 0;
                                }
                                
                                
                            }
                            
                 }
                 input_type++;
                 break;
            default:os << "Wrong option";
           // return 0;
        }
    }
    int des_Pos,sou_Pos;
    for(int i=0;i<number_Of_Nodes;i++)
    {
        if(!(destination.compare(nodes[i])))
            des_Pos=i;
        if(!(source.compare(nodes[i])))
            sou_Pos=i;
    }
    if(!(source.compare(destination)))
    {
        os <<source<<"\n";
	os <<source<<"\n";
	os << "0";
        return 0;
    }
    struct node *source_Node;
    source_Node=new(struct node);
    source_Node->node_Name.assign(source);
    source_Node->distance=0;
    source_Node->reached=true;
    source_Node->Output.push_front(source);
   
    if(task == 1)
    {
        queued.push_front(source_Node);
        bfs(distance,queued,visited,number_Of_Nodes,destination,nodes);
         
    }
    else if(task == 2){
        stacked.push(source_Node);
        dfs(distance,stacked,visited,number_Of_Nodes,destination,nodes);
        
    }
    else if(task == 3){
        ucs(distance,visited,number_Of_Nodes,source,destination,nodes);
    }
    return 0;
}

