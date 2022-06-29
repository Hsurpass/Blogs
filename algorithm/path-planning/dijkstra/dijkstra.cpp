#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <stdint.h>

using namespace std;

#define COSTINF UINT32_MAX
#define WEIGHTINF INT32_MAX

/*
    1->2: 1
    1->3: 12
    2->3: 9
    2->4: 3
    3->5: 5
    4->3: 4
    4->5: 13
    4->6: 15
    5->6: 4

       0  1  2  3  4  5
    0  0  1  12 &  &  &
    1  &  0  9  3  &  &
    2  &  &  0  &  5  &  
    3  &  &  4  0  13 15
    4  &  &  &  &  &  4
    5  &  &  &  &  &  0
*/

class Node
{
public:
    Node() : parent(NULL), cost(COSTINF) {}

    bool operator>(const Node& r) const { return this->cost > r.cost; }

    Node *parent;
    uint32_t cost;
    std::string name;
    int index;
};

class dijkstra
{
private:
    std::priority_queue<Node, vector<Node>, std::greater<Node> > openSet;
    std::unordered_map<string, Node*> closeSet;

public:
    dijkstra() {}
    ~dijkstra() {}

    void setOrigin(string name) 
    {
        for(int i = 0;i < )
        node.cost = 0;
        openSet.push(node); 
    }

    void dijkstraAlgo(const vector<vector<int>>& graph);

    void printPath(string nodeName);
};

void dijkstra::printPath(string nodeName)
{
    string path;
    const Node* node = closeSet[nodeName];
    while (node != NULL)
    {
        path += node->name;
        node = node->parent;
    }
    
    for (string::reverse_iterator itr = path.rbegin(); itr != path.rend(); ++itr)
    {
        cout << *itr << "->";
    }
    cout << endl;
}

void dijkstra::dijkstraAlgo(const vector<vector<int>>& graph, std::unordered_map<int, Node>& nodes)
{
    while (!openSet.empty())
    {
        const Node& minNode = openSet.top();
        openSet.pop();

        for (int i = 0; i < graph.size(); i++)
        {
            if (graph[minNode.index][i] != WEIGHTINF)
            {
                openSet.push(nodes[i]);
            }
        }
        
    }
}

void initGraph(vector<vector<int>>& graph)
{
    for (size_t i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            graph[i][j] = INT32_MAX;
        }
    }

    graph[0][1] = 1;
    graph[0][2] = 12;
    graph[1][2] = 9;
    graph[1][3] = 3;
    graph[2][4] = 5;
    graph[3][2] = 4;
    graph[3][4] = 13;
    graph[3][5] = 15;
    graph[4][5] = 4;
}

void initNode(std::unordered_map<int, Node> &nodes)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        Node node;
        node.name = 'A' + i;
        node.index = i;
        nodes[node.index] = node;
    }
}

void test_dijkstra()
{
    vector<vector<int>> graph;
    std::unordered_map<int, Node> nodes;
    std::priority_queue<Node> openSet;

    initGraph(graph);
    initNode(nodes);

    dijkstra dij;
    dij.setOrigin("A");
    dij.dijkstraAlgo(graph);
}

int main()
{

    return 0;
}