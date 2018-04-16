/****************************************************************************

Задача A в контесте.

Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
Вариант 1. С помощью алгоритма Прима.
Вариант 2. С помощью алгоритма Крускала.
Вариант 3. С помощью алгоритма Борувки.
Один вариант на всех не брать =)

*Формат входного файла*
Первая строка входного файла содержит два натуральных числа 𝑛 и 𝑚 — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие 𝑚 строк содержат описание ребер по одному на строке.
Ребро номер 𝑖 описывается тремя натуральными числами 𝑏𝑖, 𝑒𝑖 и 𝑤𝑖 — номера концов ребра и его вес соответственно (1 ≤ 𝑏𝑖, 𝑒𝑖 ≤ 𝑛, 0 ≤ 𝑤𝑖 ≤ 100000).

*Формат выходного файла*
Выведите единственное целое число - вес минимального остовного дерева.

 | in   | out |
 |------|-----|
 |4 4   | 7   |
 |1 2 1 |     |
 |2 3 2 |     |
 |3 4 5 |     |
 |4 1 4 |     |

****************************************************************************/

#include <vector>
#include <set>
#include <list>
#include <iostream>


/**********************USED***************************/

using std::vector;
using std::list;
using std::pair;
using std::make_pair;
using std::set;
using std::swap;

const unsigned INFINITY = 4294967295;

typedef pair<unsigned, unsigned> pair_uu;


/*********************GRAPH***************************/

class Graph {
public:
    Graph(unsigned verticesNumber);

    void addEdge(unsigned from, unsigned to, unsigned weight);

    // Вершины - вектор пар <vertex, weight>
    void getRelated(unsigned vertex, vector<pair_uu> &vertices) const;

    unsigned getSize() const;

private:
    unsigned size_;
    vector<list<pair_uu>> edges_;
};

/*********************GRAPH***************************/

Graph::Graph(unsigned int size) :
        size_(size),
        edges_(size_, list<pair_uu>())
{}


void Graph::addEdge(unsigned from, unsigned to, unsigned weight)
{
    edges_[from].push_back(make_pair(to, weight));
    edges_[to].push_back(make_pair(from, weight));
}


unsigned Graph::getSize() const
{
    return size_;
}


void Graph::getRelated(unsigned vertex,
                                     vector<pair_uu> &vertices) const
{
    vertices.clear();
    for(const pair_uu & i : edges_[vertex])
        vertices.push_back(i);
}



/***********************PRIMS*************************/

unsigned MSTWeight(const Graph & graph){
    // Сторим массив с минимальными весами ребер от used до unused для i-ой вершины
    vector<unsigned> key(graph.getSize(), INFINITY);
    // i-ая вершина была в MST => true
    vector<bool> used(graph.getSize(), false);
    // Очередь с приоритетом
    set<pair_uu> queue;


    key[0] = 0;
    for (size_t i = 0; i < graph.getSize(); ++i)
        queue.emplace(make_pair(key[i], i));

    // Prim's algor
    while (!queue.empty()) {
        // Берем минимум
        unsigned cur_vertex = queue.begin()->second;
        queue.erase(queue.begin());
        used[cur_vertex] = true;
        // Релаксакция связанных вершин
        vector<pair_uu> related;
        graph.getRelated(cur_vertex, related);

        for (const pair_uu & u : related) {
            if (!used[u.first] && key[u.first] > u.second) {
                //Меньший ключ
                queue.erase(queue.find(make_pair(key[u.first], u.first)));
                key[u.first] = u.second;
                queue.emplace(key[u.first], u.first);
            }
        }
    }

    // Строим ответ. Key хранит веса ребер в MST
    unsigned answer = 0;
    for(unsigned weigth : key){
        answer += weigth;
    }
    return answer;
}


/************************MAIN*************************/

int main()
{
    unsigned n = 0;
    unsigned m = 0;
    std::cin >> n >> m;
    Graph graph(n);
    for(unsigned i = 0; i < m; ++i) {
        unsigned a = 0;
        unsigned b = 0;
        unsigned w = 0;
        std::cin  >> a >> b >> w;
        graph.addEdge(a - 1, b - 1, w);
    }

     std::cout << MSTWeight(graph);

     return 0;
}


