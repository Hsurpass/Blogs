#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <queue>
#include <unordered_map>
#include <set>
#include <stdint.h>
#include <unistd.h>

using namespace std;

#define INF 65535

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
    Node() : parent(NULL), cost(INF) {}
    Node(const Node &node)
    {
        parent = node.parent;
        cost = node.cost;
        name = node.name;
        index = node.index;
    }

    bool operator>(const Node &r) const { return this->cost > r.cost; }

    Node *parent;
    uint32_t cost;
    std::string name;
    int index;
};

class dijkstra
{
private:
    std::priority_queue<Node, vector<Node>, std::greater<Node>> openSet;
    std::unordered_map<string, Node*> closeSet;
    bool m_debug;

public:
    dijkstra() {}
    ~dijkstra() {}

    void enableDebug(bool enable) { m_debug = enable; }
    bool debugEnabled() { return m_debug; }

    void setOrigin(string originName, vector<Node> &nodes)
    {
        for (int i = 0; i < nodes.size(); i++)
        {
            if (nodes[i].name == originName)
            {
                nodes[i].cost = 0;
                nodes[i].parent = NULL;
                openSet.push(nodes[i]);
                cout << "set origin succ" << endl;
                break;
            }
        }
    }

    void dijkstraAlgo(const vector<vector<uint32_t>> &graph, std::vector<Node> &nodes);

    void printPath(string nodeName);
};

void dijkstra::printPath(string nodeName)
{
    string path;
    Node *node = closeSet[nodeName];
    while (node != NULL)
    {
        path += node->name;
        node = node->parent;
    }

    for (string::reverse_iterator itr = path.rbegin(); itr != path.rend(); ++itr)
    {
        cout << *itr << "->";
    }
    cout << "NULL" << endl;
}

void dijkstra::dijkstraAlgo(const vector<vector<uint32_t>> &graph, std::vector<Node> &nodes)
{
    while (!openSet.empty())
    {
        Node minNode(openSet.top());
        closeSet[minNode.name] = &nodes[minNode.index];
        cout << "minNode.index:" << minNode.index << endl;
        openSet.pop();

        set<int> indexs;
        while (!openSet.empty())
        {
            const Node &node = openSet.top();
            indexs.insert(node.index);
            openSet.pop();
        }

        for (int i = 0; i < graph.size(); i++)
        {
            if(debugEnabled())
            {
                printf("minNode.cost + graph[minNode.index][%d]: %d, nodes[%d].cost:%d\n", i, minNode.cost + graph[minNode.index][i], i, nodes[i].cost);
                // sleep(1);
            }

            if ((minNode.cost + graph[minNode.index][i]) < nodes[i].cost)
            {
                nodes[i].cost = minNode.cost + graph[minNode.index][i];
                nodes[i].parent = &nodes[minNode.index];

                indexs.insert(i);
            }
        }

        for (set<int>::iterator itr = indexs.begin(); itr != indexs.end(); ++itr)
        {
            openSet.push(nodes[*itr]);
        }
        
    }
}

void initGraph(vector<vector<uint32_t>> &graph)
{
    for (size_t i = 0; i < 6; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            graph[i].push_back(INF);
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

void initNode(std::vector<Node> &nodes)
{
    for (size_t i = 0; i < nodes.size(); i++)
    {
        Node &node = nodes[i];
        node.name = 'A' + i;
        node.index = i;
    }
}

void test_dijkstra()
{
    vector<vector<uint32_t>> graph;
    graph.resize(6);
    std::vector<Node> nodes;
    nodes.resize(6);

    initGraph(graph);
    initNode(nodes);

    dijkstra dij;
    dij.enableDebug(true);
    dij.setOrigin("A", nodes);
    dij.dijkstraAlgo(graph, nodes);
    
    // dij.printPath("F");
    // dij.printPath("E");
    // dij.printPath("D");
    // dij.printPath("C");
    // dij.printPath("B");
    dij.printPath("A");

}

int main()
{
    test_dijkstra();

    return 0;
}