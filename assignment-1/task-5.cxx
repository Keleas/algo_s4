#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <iomanip>
#include <cmath>

/*************************************************************/

#define EPSILON 5e-5

/*************************************************************/

using std::vector;
using std::size_t;
using std::queue;
using std::list;
using std::pair;
using std::sqrt;
using std::pow;

/*************************************************************/

class Graph {
public:
    //стандартный конструктор
    Graph (unsigned int verticesNumber);

    //добавить ребро графа
    void AddEdge(int from, int to);

    //слдеующие вершины графа за исходным
    void GetNextVertices(int vertex, vector<int>& vertices) const;

    //количество вершин графа
    int VerticesCount() const;

    //количество кратчайших путей из from в to
    int countPaths(int from, int to);

private:
    //ребро
    struct Edge
    {
        Edge();
        int depth; //глубина данной вершины
        int path; //количество путей к данному графу
    };

    //количество вершин графа
    unsigned int verticesNumber_;

    //граф через массив списоков смежности
    vector<list<int>> out_;
    vector<list<int>> in_;
};

double getMaxDiametrTable(vector<pair<int, int> > columnCoords, int leftWallCoord, int rightWallCoord, int columnRadius);

/*************************************************************/

Graph::Graph(unsigned int verticesNumber) :
    verticesNumber_{verticesNumber},
    out_{verticesNumber_},
    in_{verticesNumber_}
{}


Graph::Edge::Edge() :
    depth{0},
    path{0}
{}

/*************************************************************/

void Graph::AddEdge(int from, int to)
{
        for(int i : out_[from])
            if(i == to)
                return;

    out_[to].push_back(from);
    out_[from].push_back(to);
    in_[to].push_back(from);
    in_[from].push_back(to);
}


int Graph::VerticesCount() const
{
    return verticesNumber_;
}


void Graph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (auto i : out_[vertex])
        vertices.push_back(i);
}


int Graph::countPaths(int from, int to) {
    vector<Edge> verticesStates(verticesNumber_);
    queue<int> verticesQueue;
    verticesQueue.push(from);
    verticesStates[from].path = 1;


    while (!verticesQueue.empty()) {
        vector<int> nextVertices; //следующие вершины для исходного
        int currentVertex = verticesQueue.front();
        verticesQueue.pop();
        GetNextVertices(currentVertex, nextVertices);
        //перебор вершин следующих за данной
        for (int i : nextVertices) {
            if (verticesStates[i].path == 0) {
                verticesQueue.push(i); //добавляем в queue для послдующей проверки
                verticesStates[i].depth = verticesStates[currentVertex].depth + 1; //глубина состоит из глубины отца + своя
                verticesStates[i].path = verticesStates[currentVertex].path; //количество путей совпадает с отцом
            }
            else if (verticesStates[i].depth == verticesStates[currentVertex].depth + 1) //круг
                verticesStates[i].path += verticesStates[currentVertex].path;
        }
    }

    return verticesStates[to].path;
}

/*************************************************************/

double getMaxDiametrTable(vector<pair<int, int>> columnCoords, int leftWallCoord, int rightWallCoord, int columnRadius)
{
    unsigned int n = columnCoords.size();
    double right_iterator = rightWallCoord - leftWallCoord; //правая граница радиуса
    double left_iterator = 0; //левая граница радиуса

    while (right_iterator - left_iterator > EPSILON) {
        Graph graph(n+2);
        double curRadius = (right_iterator + left_iterator) / 2;

        //составляем граф из вершин, через которые нельзя пронести стол текущего радиуса
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < n; ++j)
                if (sqrt( pow(columnCoords[i].first - columnCoords[j].first, 2) +
                     pow(columnCoords[i].second - columnCoords[j].second,2) ) -
                     2 * columnRadius < curRadius)
                    graph.AddEdge(i,j);
        }

        //проверка проноса стола у стенок
        for (size_t i = 0; i < n; ++i)
            if (columnCoords[i].first - leftWallCoord - columnRadius < curRadius)
                graph.AddEdge(i, n);
        for (size_t i = 0; i < n; ++i)
            if (rightWallCoord - columnCoords[i].first - columnRadius < curRadius)
                graph.AddEdge(i, n+1);

        if (graph.countPaths(n, n+1) != 0)
            right_iterator = curRadius;
        else
            left_iterator = curRadius;
    }

    return left_iterator;
}

/*************************************************************/

int main()
{
    int leftWallCoord = 0;
    int rightWallCoord = 0;
    std::cin >> leftWallCoord >> rightWallCoord;
    int columnRadius = 0;
    std::cin >> columnRadius;
    unsigned int n;
    std::cin >> n;
    vector<pair<int, int>> columnCoords(n, pair<int, int>(0, 0));
    for (size_t i = 0; i < n; ++i)
        std::cin >> columnCoords[i].first >> columnCoords[i].second;

    std::cout << std::fixed << std::setprecision(3)
                       <<  getMaxDiametrTable(columnCoords, leftWallCoord, rightWallCoord, columnRadius);


    return 0;
}
