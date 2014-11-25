#include <iostream>
#include <fstream>
#include <queue>
#include <string>
using namespace std;
struct node 
{
        string node_Name;
        int distance;
        bool reached;
        int position;
};
#define MAX_NODES 2048
int bfs(int distance[][MAX_NODES],deque<struct node *> queued,deque<struct node *>  visited,int number_Of_Nodes,string destination,string nodes[])
{
    int pos_Present;
    std::deque<struct node *>::iterator it = visited.begin();
    if(!(queued.empty()))
    {
        return -1;
    }
    struct node *present_Node = queued.back();
    if(!(destination.compare(present_Node->node_Name))) {
                return 0;
    }
    queued.pop_back();
    present_Node->reached=true;
    visited.push_front(present_Node);
    for(int i=0;i<number_Of_Nodes;i++)         {
        if(!(present_Node->node_Name.compare(nodes[i]))){
            pos_Present=i;
            break;
        }
    }
    for(int i=0;i<number_Of_Nodes;i++)
    {
        int found=0;
        queue<struct node *> temp_queue;
        struct node *push_node = new(struct node);
        if(!(distance[pos_Present][i])){
             push_node->distance=present_Node->distance+1;
             push_node->node_Name=nodes[i];
             queued.push_front(push_node);
        }
    }
    bfs(distance,queued,visited,number_Of_Nodes,destination,nodes);

}
