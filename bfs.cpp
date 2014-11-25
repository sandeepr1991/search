#include <iostream>
#include <fstream>
#include <deque>
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
bool is_Node_Queued(queue<struct node *>&queued,string& node)
{
    bool return_value = false;
    queue<struct node *>temp_queue;
    while(!(queued.empty())){
        if(queued.front()->node_Name.compare(node)==0)
            return_value = true;
        temp_queue.push(queued.front());
        queued.pop();
    }
    while(!(temp_queue.empty()))
    {
        queued.push(temp_queue.front());
        temp_queue.pop();
    }
    return return_value;
        
}


void sort_deque(deque<struct node *>& deque_Nodes,struct node * node)
{
     
//     deque<struct node *>temp_Queue;
     std::deque<struct node *>::iterator it = deque_Nodes.begin();
  //   struct node *temp_Node;
  //   while(!(deque_Nodes.empty()))
   //  {
    //     temp_Node = deque_Nodes.front();
     //    deque_Nodes.pop_front();
     //    it = temp_Queue.begin();
         while(it != deque_Nodes.end() && !((*it)->position == node->position && (node->node_Name.compare((*it)->node_Name)) < 0))
             it++;
         deque_Nodes.insert(it,node);
}

/*
bool is_Node_Queued(queue<struct node *> queued,string node){
    queue<struct node *> temp_queue;
    bool return_value = false; 
    while(!(queued.empty())){
        if((queued.front()->node_Name.compare(node))){
            return_value = true;
        }
        queued.pop();
    }
    return return_value;
}
*/
int get_Position(string node,string nodes[],int number_Of_Nodes)
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

bool is_Node_Present(deque<struct node *>& node_List,string& node)
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

int bfs(int distance[][MAX_NODES],deque<struct node *>& queued,deque<struct node *>& visited,int number_Of_Nodes,string destination,string nodes[]){
    int pos_Present;
    ofstream os;
    os.open("output.txt",std::fstream::out);
   // std::queue<struct node *>::iterator it = visited.begin();
    
    if(queued.empty())
    {
	deque<struct node *>::iterator it = visited.end();
            it--;
            while(it != visited.begin())
            {

                os << (*it)->node_Name;
                os << "-";
                it--;
            }
	os <<"\n";

        os<<"NoPathAvailable";
        return 0;
    }
    struct node *present_Node = queued.front();
    
    queued.pop_front();
    if(!(present_Node->node_Name.compare(destination))){
        deque<struct node *>::iterator it = visited.end();
            it--;
            while(it != visited.begin())
            {
                
                os << (*it)->node_Name; 
                os << "-";
                it--;
            }
            os << (*it)->node_Name << "-";
            os << destination;
            os << "\n";
            while(!(present_Node->Output.empty()))
            {
             //   string s = push_node->Output.front();
                os << present_Node->Output.front();
                if(present_Node->Output.front().compare(destination))
                    os << "-";
                present_Node->Output.pop_front();
            }
            os << "\n";
            os <<  present_Node->distance;
            return 0;

    }
    for(int i=0;i<number_Of_Nodes;i++)         {
        if(!(present_Node->node_Name.compare(nodes[i]))){
            pos_Present=i;
            break;
        }
    }
    present_Node->reached = true;
    visited.push_front(present_Node);
    
    int found=0;
    deque<struct node *> temp_queue;
    for(int i=0;i<number_Of_Nodes;i++){
        
        
       
        
        if(distance[pos_Present][i] && !(is_Node_Present(visited,nodes[i]) ) && !(is_Node_Present(queued,nodes[i])) ){
            struct node *push_node = new(struct node);
            push_node->distance=present_Node->distance + distance[pos_Present][i];
            push_node->position=present_Node->position+1;
            std::deque<string>::iterator it = present_Node->Output.begin();
            //it--;
            while(it != present_Node->Output.end())
            {
                string s1 = (*it);
                push_node->Output.push_back((*it));
                it++;
            }
            push_node->Output.push_back(nodes[i]);
            push_node->node_Name=nodes[i];
            
        
             found++;
             
             
             sort_deque(queued,push_node);
             
        }
    }
    // if(!(found==1 || found==0)) 
    // {
     //sort_deque(_queued);
     
    // }
     /*
    while(!temp_queue.empty()){
         queued.push_front(temp_queue.front());
         temp_queue.pop_front();
     }*/
    
    
    
    bfs(distance,queued,visited,number_Of_Nodes,destination,nodes);

}
