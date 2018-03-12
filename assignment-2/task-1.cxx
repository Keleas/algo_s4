/****************************************************************************

Требуется отыскать самый выгодный маршрут между городами. Требуемое время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Оптимизируйте ввод.
N ≤ 10000, M ≤ 250000.
Длина каждой дороги ≤ 10000.

*Формат входных данных*
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).

*Формат выходных данных*
Вывести длину самого выгодного маршрута.

 | in   | out |
 |------|-----|
 |6     | 9   |
 |9     |     |
 |0 3 1 |     |
 |0 4 2 |     |
 |1 2 7 |     |
 |1 3 2 |     |
 |1 4 3 |     |
 |1 5 3 |     |
 |2 5 3 |     |
 |3 4 4 |     |
 |3 5 6 |     |
 |0 2   |     |
****************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <list>

/******************************************************************************/

using std::vector;
using std::set;
using std::pair;
using std::make_pair;
using std::list;

typedef pair<unsigned, unsigned> pair_uu;

const unsigned INFINITY = 4294967295;

/******************************************************************************/

class Graph {
public:
    Graph(unsigned int verticesNumber);

    void AddEdge(unsigned from, unsigned to, unsigned weight);

    // Вершины - вектор пар <vertex, weight>
    void GetRelated(unsigned vertex, vector<pair_uu> &vertices) const;

    unsigned GetSize() const;

private:
    unsigned size_;
    vector<list<pair_uu>> edges_;
};

/******************************************************************************/

Graph::Graph(unsigned int size) :
        size_(size),
        edges_(size_, list<pair_uu>())
{}


void Graph::AddEdge(unsigned from, unsigned to, unsigned weight)
{
    edges_[from].push_back(make_pair(to, weight));
    edges_[to].push_back(make_pair(from, weight));
}


unsigned int Graph::GetSize() const
{
    return size_;
}


void Graph::GetRelated(unsigned vertex, vector<pair_uu> &vertices) const
{
    vertices.clear();
    for (const pair_uu &i : edges_[vertex])
        vertices.push_back(i);
}

/******************************************************************************/

int DijkstraAlgo(Graph const &graph, int from, int to) {
    // Помечаем факт того, что были в вершине
    vector<bool> isUsed(graph.GetSize(), false);
    // Строим пути до каждой вершины
    vector<unsigned int> path(graph.GetSize(), INFINITY);
    path[from] = 0;
    // Очередь с приоритетом
    set<pair_uu> queue;
    queue.emplace(make_pair(0, from));
    // Алгоритм Дийсктры
    while (!queue.empty()) {
        // Добавляем вершину с минимальным путем
        unsigned v = (queue.begin())->second;
        queue.erase(queue.begin());
        isUsed[v] = true;

        // Релаксируем вершины
        vector<pair_uu> paths;
        graph.GetRelated(v, paths);
        for (pair_uu c : paths) {
            if (path[c.first] > path[v] + c.second) {
                // Убираем старые вершины из очереди
                if (path[c.first] != INFINITY)
                    queue.erase(make_pair(path[c.first], c.first));
                // Обновляем пути и кидаем в очередь
                path[c.first] = path[v] + c.second;
                queue.emplace(pair<int, int>(path[c.first], c.first));
            }
        }
    }

    // Вернуть расстояние между исходными вершинами, если его нет, то вернуть -1
    return ((path[to] != INFINITY) ? (static_cast<int>(path[to])) : (-1));
}

/******************************************************************************/

int main()
{
    std::ios::sync_with_stdio(false);

    unsigned n = 0;
    unsigned m = 0;
    std::cin >> n >> m;
    Graph graph(n);
    for (unsigned i = 0; i < m; ++i) {
        unsigned s = 0;
        unsigned t = 0;
        unsigned w = 0;
        std::cin >> s >> t >> w;
        graph.AddEdge(s, t, w);
    }
    unsigned from = 0;
    unsigned to = 0;
    std::cin >> from >> to;

    std::cout << DijkstraAlgo(graph, from, to);

    return 0;
}

