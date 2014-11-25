
#include <iostream>
#include <fstream>
#include <deque>
#include <stack>
#include <string>
#include "main.h"

/*
int get_Priority_Node_Position(deque<struct node *>& node_list)
{
    struct node *temp_node,*temp_node1;
    int position=0,i=0;
    temp_node = node_list->front();
    while(!(node_list->empty()))
    {
        temp_node1=node_list->front();
        
        if((temp_node->node_Name.compare(temp_node->node_Name)) < 0){
            position=i;
        }
        node_list->pop_front();
        i++;
    }
    return position;
}
*/
/*int get_Position(string node,string nodes[],int number_Of_Nodes)
{
    int pos_Present;
    
    for(int i=0;i<number_Of_Nodes;i++)         {
        if(!(node.compare(nodes[i]))){
            pos_Present=i;
            break;
        }
    }
    return pos_Present;
}
*/
int is_Node_Stacked(stack <struct node *>& stacked,string& node)
{
    bool return_value = false;
    stack <struct node *> temp1;
    while(!stacked.empty())
    {
        if(!(stacked.top()->node_Name.compare(node)))
        {
            return_value = true;
            //stacked.pop();
            break;
        }
        temp1.push(stacked.top());
        stacked.pop();
    }
    while(!temp1.empty())
    {
        stacked.push(temp1.top());
        temp1.pop();
    }
    return return_value;
}

int is_Node_Present_dfs(deque<struct node *>& node_List,string& node)
{
    deque<struct node *>::iterator it = node_List.begin();
 //   cout << it->node_Name;
   
    //cout<<it._M_cur->node_Name;
    if(!(node_List.empty()))
    {
    while (it != node_List.end())
    {
        if(!(((*it)->node_Name).compare(node)))
            return true;
        it++;
    }
    }
    
    return false;
}

int dfs(int distance[][MAX_NODES],stack<struct node *>& stacked,deque<struct node *>& visited,int number_Of_Nodes,string destination,string nodes[]){
    int pos_Present;
    ofstream os;
    os.open("output.txt",std::fstream::out);
   // std::queue<struct node *>::iterator it = visited.begin();
    
    if(stacked.empty())
    {
	deque<struct node *>::iterator it = visited.end();
            it--;
            while(it != visited.begin())
            {

                os << (*it)->node_Name;
                os << "-";
                it--;
            }
         os << (*it)->node_Name;
	 os << "\n";
        os<<"NoPathAvailable";
        return 0;
    }
    struct node *present_Node = stacked.top();
    
    
    if(!(present_Node->node_Name.compare(destination)))
    {
       
            deque<struct node *>::iterator it = visited.end();
            it--;
            while(it != visited.begin())
            {
                
                os << (*it)->node_Name; 
                os << "-";
                it--;
            }
            os << (*it)->node_Name;
            os << "-";
            os << destination;
            os << "\n";
            while(!(present_Node->Output.empty()))
            {
             //   string s = push_node->Output.front();
                os << present_Node->Output.front();
                if((present_Node->Output.front().compare(destination)))
                    os << "-";
                present_Node->Output.pop_front();
            }
            os << "\n";
            os << present_Node->distance;
            return 0;
    }
    
    stacked.pop();
    
    
        present_Node->reached=true;
    visited.push_front(present_Node);
    
    for(int i=0;i<number_Of_Nodes;i++)         {
        if(!(present_Node->node_Name.compare(nodes[i]))){
            pos_Present=i;
            break;
        }
    }
    int found=0;
    for(int i=0;i<number_Of_Nodes;i++){
        
        queue<struct node *> temp_queue;
       
        
        if(distance[pos_Present][i] && !(is_Node_Present_dfs(visited,nodes[i])) && !(is_Node_Stacked(stacked,nodes[i]))){
            struct node *push_node = new(struct node);
            std::deque<string>::iterator it = present_Node->Output.begin();
            //it--;
            while(it != present_Node->Output.end())
            {
                string s1 = (*it);
                push_node->Output.push_back((*it));
                it++;
            }
            push_node->distance=present_Node->distance + distance[pos_Present][i];
            push_node->Output.push_back(nodes[i]);
            push_node->node_Name=nodes[i];
       /*     if(!(destination.compare(nodes[i]))) {
            
            
            
            
    }*/
            
             found++;
             
             if(found == 1)
             stacked.push(push_node);
             else{
                 struct node * temp_node1;
                 stack<struct node *> temp_stack;
                 temp_node1= stacked.top();
                 
                     int j=1;
                     while(j < found && (push_node->node_Name.compare(temp_node1->node_Name))>0 )
                     {
                         
                         
                         
                         temp_stack.push(temp_node1);
                         stacked.pop();
                         j++;
                         if(!(stacked.empty()))
                         temp_node1=stacked.top();
                         
                     }
                     stacked.push(push_node);
                     while(!(temp_stack.empty()))
                     {
                         temp_node1=temp_stack.top();
                         
                         stacked.push(temp_node1);
                         temp_stack.pop();
                     }
                     
                 }
                 
             
        
        }
    }
    
    dfs(distance,stacked,visited,number_Of_Nodes,destination,nodes);

}
