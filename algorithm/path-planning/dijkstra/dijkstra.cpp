#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <stdint.h>

using namespace std;

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
    Node() : parent(NULL), cost(UINT32_MAX) {}

    bool operator<(const Node& r) { return this->cost < r.cost; }
    Node *parent;
    uint32_t cost;
    std::string name;
};

class dijkstra
{
private:
    int graph[6][6];
    std::unordered_map<std::string, Node> nodes;
    std::priority_queue<Node> openSet;

public:
    dijkstra() {}
    ~dijkstra() {}

    void setOrigin(Node& node)
    {
        openSet.push(node);
    }

    void setDestination()
    {

    }
};

void initGraph(int (*graph)[6])
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

void initNode(std::unordered_map<std::string, Node> &nodes)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        Node node;
        node.name = 'A' + i;
        nodes[node.name] = node;
    }
}

void test_dijkstra()
{
    int graph[6][6];
    std::unordered_map<std::string, Node> nodes;
    std::priority_queue<Node> openSet;

    initGraph(graph);
    while (1)
    {
        const Node& minNode = openSet.top();
        openSet.pop();
    }
    
}

int main()
{

    return 0;
}