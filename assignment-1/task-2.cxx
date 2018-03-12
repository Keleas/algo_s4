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

В данной задаче применена идея обхода графа в ширину (BFS). А именно -
совершаем выбор опорной вершины, с которой происходит запуск BFS, берем все
возможные вершины, в которые можно пойти из данной, помещаем в конец
очереди, помечаем данную вершину пройденной. Обрабатываем так каждуй вершину
пока очередь непуста, при этом отслеживая глубину каждой вершины. Для этого
создаем структуру Edge.

Граф реализован через предстваления массива с хэш-таблицей
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
    //стандартный конструктор
    Graph (unsigned int verticesNumber);

    //добавить ребро графа
    void AddEdge(int from, int to);

    //следующие вершины графа за исходным
    void GetNextVertices(int vertex, vector<int>& vertices) const;

    //количество врешин графа
    int VerticesCount() const;

    //поиск минимального цикла
    int minCycle();
private:
    struct Edge
    {
        Edge();
        int depth; //глубина данной вершины
        int father; //родитель
        bool visited; //проверка на посещение
    };

    //поиск минимального цикла в ширину
    int BFS(int vertex);

    //количество вершин графа
    unsigned int verticesNumber_;

    //граф через массив хэш-таблиц
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
    //перебор всех вершин
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
        vector<int> nextVertices; //следующие вершины для исходного
        int currentVertex = verticesQueue.front();
        verticesQueue.pop();
        GetNextVertices(currentVertex, nextVertices);
        //перебор вершин следующих за данной
        for (int i : nextVertices) {
            if (!verticesStates[i].visited) {
                verticesQueue.push(i); //добавляем в queue для послдующей проверки
                verticesStates[i].visited = true;
                verticesStates[i].depth = verticesStates[currentVertex].depth + 1; //глубина состоит из глубины отца + своя
                verticesStates[i].father = currentVertex;
            }
            else if (i != verticesStates[currentVertex].father)  //цикл
                return verticesStates[currentVertex].depth + verticesStates[i].depth + 1;

        }
    }
    //цикл не найден
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
