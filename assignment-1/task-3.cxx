/****************************************************************************

Дан невзвешенный неориентированный граф. В графе может быть несколько
кратчайших путей между какими-то вершинами. Найдите цикл минимальной длины.
Требуемая сложность O(VE), + 1 балл за O(V + E).

Ввод: В первой строке вводятся два натуральных числа N и M, не превосходящих 10000.
Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.
Вывод: 1 целое число равное длине минимального цикла. Если цикла нет, то вывести -1.


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
Идея:

Схожа с идеей в задача 1.2
В данной задаче применена идея обхода графа в ширину (BFS). А именно -
совершаем выбор опорной вершины, с которой происходит запуск BFS, берем все
возможные вершины, в которые можно пойти из данной, помещаем в конец
очереди, помечаем данную вершину пройденной. Обрабатываем так каждуй вершину
пока очередь непуста, при этом отслеживая глубину каждой вершины. Для этого
создаем структуру Edge.

Граф реализован через масив списков смежности. Занимает меньшего всего места.
****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <list>

/*************************************************************/

using std::vector;
using std::size_t;
using std::queue;
using std::list;

/*************************************************************/

class Graph {
public:
    //стандартный конструктор
    Graph (unsigned int verticesNumber);

    //добавить ребро графа
    void AddEdge(int from, int to);

    //следующие вершины графа за исходным
    void GetNextVertices(int vertex, vector<int>& vertices) const;

    //количество вершин графа
    int VerticesCount() const;

    //количество кратчайших путей из from в to
    int countMinPaths(int from, int to);

private:
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
};

/*************************************************************/

Graph::Graph(unsigned int verticesNumber) :
    verticesNumber_{verticesNumber},
    out_{verticesNumber_}
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


int Graph::countMinPaths(int from, int to) {
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
                verticesQueue.push(i); //добавляем в queue для последующей проверки
                verticesStates[i].depth = verticesStates[currentVertex].depth + 1; //глубина состоит из глубины отца + своя
                verticesStates[i].path = verticesStates[currentVertex].path; //количество путей совпадает с отцом
            }
            else if (verticesStates[i].depth ==
                           verticesStates[currentVertex].depth + 1) // найден другой путь к этой вершине
                verticesStates[i].path += verticesStates[currentVertex].path;
        }
    }

    return verticesStates[to].path;
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

    int from = 0;
    int to = 0;
    std::cin >> from >> to;
    std::cout << graph.countMinPaths(from, to);

    return 0;
}
