/****************************************************************************

��� ������������ ����������������� ����. � ����� ����� ���� ���������
���������� ����� ����� ������-�� ���������. ������� ���� ����������� �����.
��������� ��������� O(VE), + 1 ���� �� O(V + E).

����: � ������ ������ �������� ��� ����������� ����� N � M, �� ������������� 10000.
����� ���� M ����� �� 2 ����� (�� 0 �� N-1) - ������� ������ ����� �������� ���� �����.
�����: 1 ����� ����� ������ ����� ������������ �����. ���� ����� ���, �� ������� -1.


  in  | out
 -----|-----
  6 6 |  4
  0 1 |
  0 2 |
  2 3 |
  2 4 |
  3 5 |
  4 5 |

****************************************************************************/

/****************************************************************************
����:

� ������ ������ ��������� ���� ������ ����� � ������ (BFS). � ������ -
��������� ����� ������� �������, � ������� ���������� ������ BFS, ����� ���
��������� �������, � ������� ����� ����� �� ������, �������� � �����
�������, �������� ������ ������� ����������. ������������ ��� ������ �������
���� ������� �������, ��� ���� ���������� ������� ������ �������. ��� �����
������� ��������� Edge.

���� ���������� ����� ������������� ������� � ���-��������
****************************************************************************/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <queue>

/*************************************************************/

using std::vector;
using std::unordered_set;
using std::size_t;
using std::queue;

/*************************************************************/

class Graph {
public:
    //����������� �����������
    Graph (unsigned int verticesNumber);

    //�������� ����� �����
    void AddEdge(int from, int to);

    //��������� ������� ����� �� ��������
    void GetNextVertices(int vertex, vector<int>& vertices) const;

    //���������� ������ �����
    int VerticesCount() const;

    //����� ������������ �����
    int minCycle();
private:
    struct Edge
    {
        Edge();
        int depth; //������� ������ �������
        int father; //��������
        bool visited; //�������� �� ���������
    };

    //����� ������������ ����� � ������
    int BFS(int vertex);

    //���������� ������ �����
    unsigned int verticesNumber_;

    //���� ����� ������ ���-������
    vector<unordered_set<int>> out_;
};

/*************************************************************/

Graph::Graph(unsigned int verticesNumber) :
    verticesNumber_{verticesNumber},
    out_{verticesNumber_}
{}


Graph::Edge::Edge() :
    depth{0},
    visited{false}
{}

/*************************************************************/

void Graph::AddEdge(int from, int to)
{
    out_[from].insert(to);
    out_[to].insert(from);
}


int Graph::VerticesCount() const
{
    return verticesNumber_;
}


void Graph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    for (auto i : out_[vertex])
        vertices.push_back(i);
}


int Graph::minCycle()
{
    int minCycle = verticesNumber_ + 1;
    //������� ���� ������
    for (size_t i =  0; i < verticesNumber_; ++i) {
        int curCycleCount = BFS(i);
        if (curCycleCount < minCycle)
            minCycle = curCycleCount;
    }
    return minCycle;
}


int Graph::BFS(int vertex) {
    vector<Edge> verticesStates(verticesNumber_);
    queue<int> verticesQueue;
    verticesStates[vertex].visited = true;
    verticesQueue.push(vertex);


    while (!verticesQueue.empty()) {
        vector<int> nextVertices; //��������� ������� ��� ���������
        int currentVertex = verticesQueue.front();
        verticesQueue.pop();
        GetNextVertices(currentVertex, nextVertices);
        //������� ������ ��������� �� ������
        for (int i : nextVertices) {
            if (!verticesStates[i].visited) {
                verticesQueue.push(i); //��������� � queue ��� ���������� ��������
                verticesStates[i].visited = true;
                verticesStates[i].depth = verticesStates[currentVertex].depth + 1; //������� ������� �� ������� ���� + ����
                verticesStates[i].father = currentVertex;
            }
            else if (i != verticesStates[currentVertex].father)  //����
                return verticesStates[currentVertex].depth + verticesStates[i].depth + 1;

        }
    }
    //���� �� ������
    return verticesNumber_ + 1;
}

/*************************************************************/


int main()
{
    unsigned int n = 0;
    std::cin >> n;
    Graph graph(n);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++ i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from, to);
    }

    int minCycle = graph.minCycle();
    if (minCycle == graph.VerticesCount() + 1)
       minCycle = -1;
    std::cout << minCycle;

    return 0;
}
