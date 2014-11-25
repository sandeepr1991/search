#include <iostream>
#include <fstream>
#include "main.h"
#include <queue>

int stage=0;

int get_Position_ucs(string node,string nodes[],int number_Of_Nodes)
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


int is_Node_Present_ucs(deque<struct node *>& node_List,string& node)
{
    deque<struct node *>::iterator it = node_List.begin();
 //   cout << it->node_Name;
   
    //cout<<it._M_cur->node_Name;
    while (it != node_List.end())
    {
        if(!(((*it)->node_Name).compare(node)))
            return true;
        it++;
    }
    
    return false;
}

class get_Highest{
public:
    bool operator()(struct node *& node1,struct node *& node2)
    {
      /*  if(!(node1->node_Name.compare(node2->node_Name)))
        {
            if(node1->distance <= node2->distance)
                return false;
            else
                return true;
        }*/
        if(node1->distance > node2->distance)
            return true;
        else if (node1->distance < node2->distance)
            return false;
        else
        {
            if(node1->node_Name.compare(node2->node_Name)<=0)
                return false;
            else
                return true;
        }
        /*
        if(node1->distance <= node2->distance)
            return false;
        else if(node1->distance == node2->distance && !(node1->node_Name.compare(node2->node_Name)))
                return false;
        else if(!(node1->node_Name.compare(node2->node_Name)) && node1->distance > node2->distance){
            node1->distance = -1;
            return false;
        }
        else return true;
    */}
};

int ucs_run(int distance[][MAX_NODES],priority_queue<struct node *, vector<struct node *>,get_Highest>& priority_queued,deque<struct node *>& visited,int number_Of_Nodes,string destination,string nodes[]){
    int pos_Present;
    ofstream os;
    std::deque<string>::iterator it; 
    os.open("output.txt",std::fstream::out);
   // std::queue<struct node *>::iterator it = visited.begin();
    
    if(priority_queued.empty())
    {
	 deque<struct node *>::iterator it1 = visited.end();
            it1--;
            while(it1 != visited.begin())
            {

                os << (*it1)->node_Name;
                os << "-";
                it1--;
            }
            os << (*it1)->node_Name;
	os << "\n";
        os<<"NoPathAvailable";
        return 0;
    }
    struct node *present_Node = priority_queued.top();
    
    if(!(present_Node->node_Name.compare(destination)) && present_Node->distance != -1)
    {
        deque<struct node *>::iterator it1 = visited.end();
            it1--;
            while(it1 != visited.begin())
            {
                
                os << (*it1)->node_Name; 
                os << "-";
                it1--;
            }
            os << (*it1)->node_Name;
            os << "-";
            os << destination;
            os << "\n";
            
            while(!(present_Node->Output.empty()))
            {
             //   string s = push_node->Output.front();
                os << present_Node->Output.back();
                if(present_Node->Output.back().compare(destination))
                    os << "-";
                       
                present_Node->Output.pop_back();
            }
            
            os << "\n";
            os << present_Node->distance;
            return 0;
    }
    priority_queued.pop();
    if(present_Node->distance !=-1)
    {
    present_Node->reached=true;
    if(!(is_Node_Present_ucs(visited,present_Node->node_Name)))
    visited.push_front(present_Node);
    pos_Present=get_Position_ucs(present_Node->node_Name,nodes,number_Of_Nodes);
    int found=0;
    stage++;
    for(int i=0;i<number_Of_Nodes;i++){
        
        queue<struct node *> temp_queue;
       
        
        if(distance[pos_Present][i]){
            
            
            struct node *push_node = new(struct node);
            push_node->distance=present_Node->distance + distance[pos_Present][i];
            push_node->node_Name = nodes[i];
           
            it= present_Node->Output.begin();
            while(it != present_Node->Output.end())
            {
                string s1 = (*it);
                push_node->Output.push_back((*it));
                it++;
            }
            push_node->Output.push_front(nodes[i]);
            push_node->position = stage;
             
            //it--;
 /*            if(!(destination.compare(nodes[i]))) {
            
            
            
            visited.push_front(push_node);
            
    }*/
           
             //push_node->Output.push_back(present_Node->node_Name);
            if(!(is_Node_Present_ucs(visited,push_node->node_Name))){
               
                priority_queued.push(push_node);
                
            }
            else
            {
                deque<struct node *>::iterator it_visited =  visited.begin();
                
                int node_position=0;
                while( (it_visited!=visited.end()) && (*it_visited)->node_Name.compare(push_node->node_Name))
                {
                    node_position++;
                    it_visited++;
                }
                if(((*it_visited)->distance) > push_node->distance)
                {
                     
                visited.erase(it_visited);
                
                priority_queued.push(push_node);
            }
            }
        }
    }
    }   
    
 ucs_run(distance,priority_queued,visited,number_Of_Nodes,destination,nodes);   
}

int ucs(int distance[][MAX_NODES],deque<struct node *>& visited,int number_Of_Nodes,string source_name,string destination,string nodes[]){
    
priority_queue<struct node *, vector<struct node *>,get_Highest> priority_queued;
struct node * source = new(struct node);
source->node_Name.assign(source_name);
source->distance=0;
source->reached=true;
source->Output.push_front(source_name);
priority_queued.push(source);
return(ucs_run(distance,priority_queued,visited,number_Of_Nodes,destination,nodes));
}
