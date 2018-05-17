/****************************************************************************

Задача в контесте - B.
Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером 𝑛.

*Формат входного файла*
Первая строка входного файла содержит 𝑛 и 𝑚 — количество вершин и количество ребер графа (2 ≤ 𝑛 ≤ 100, 1 ≤ 𝑚 ≤ 1000). Следующие 𝑚 строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 105.

*Формат выходного файла*
В выходной файл выведите одно число — величину максимального потока из вершины с номером 1 в вершину с номером n.

| in   |out |
|------|----|
|4 5   | 3  |
|1 2 1 |    |
|1 3 2 |    |
|3 2 1 |    |
|2 4 2 |    |
|3 4 1 |    |

****************************************************************************/

#include <vector>
#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>

/******************************************************************************/

using std::ifstream;
using std::ofstream;
using std::vector;
using std::pair;
using std::make_pair;
using std::min;
using std::queue;

typedef pair<unsigned, unsigned> pair_uu;

const unsigned INFINITY = 2147483647;

/******************************************************************************/

class Graph {
public:
    Graph(unsigned verticesNumber);

    void increaseEdge(unsigned from, unsigned to, int weight);

    // выершины - вектор пар <vertex, weight>
    void getRelated(unsigned vertex, vector<pair_uu> &vertices) const;

    unsigned getSize() const;

private:
    unsigned size_;
    vector<vector<unsigned>> matrix_;
};

/******************************************************************************/

// Функциональный объект для поиска максимального потока
class MaxFlow{
public:
    MaxFlow():
            net_(0){}

    // Вернуть maxiamal flow
    unsigned operator()(const Graph & graph, unsigned s, unsigned t){
        // Edmonds-Karp algorithm
        // Остаточная сеть
        net_ = graph;
        // Целевая вершина
        t_ = t;
        // Дельта в потоке в текущей итерации
        unsigned delta = 0;
        // Финальный поток
        unsigned flow = 0;

        // Увеличение итеративного потока
        do{
            delta = IncreaseFlow(s);
            flow += delta;
        }while(delta != 0);

        return flow;
    }

private:
    // Находит путь и снижает пропускную способность в остаточной сети
    unsigned IncreaseFlow(unsigned s){
        // Делаем pair <parent vertex, weight of edge from parent>
        vector<pair_uu> parents(net_.getSize());
        for(unsigned i = 0; i < net_.getSize(); ++i){
            parents[i].first = INFINITY;
            parents[i].second = INFINITY;
        }
        parents[s].first = s;
        parents[s].second = 0;

        // Поиск пути  BFS
        queue<unsigned> q;
        q.emplace(s);
        while(!q.empty()){
            unsigned v = q.front();
            q.pop();
            if(v == t_)
                break;
            vector<pair_uu> related;
            net_.getRelated(v, related);
            for(pair_uu & edge : related){
                if(parents[edge.first].first == INFINITY){
                    parents[edge.first].first = v;
                    parents[edge.first].second = edge.second;
                    q.push(edge.first);
                }
            }
        }

        // Если целевая вершина не достижима, то дельта равна 0
        if(parents[t_].first == INFINITY)
            return 0;

        // Поиск минимальной пропускной способности
        unsigned delta = INFINITY;
        unsigned u = t_;
        while(u != s){
            if(parents[u].second < delta)
                delta = parents[u].second;
            u = parents[u].first;
        }

        // Уменьшение пропускной способности в остаточной сети
        u = t_;
        while(u != s){
            net_.increaseEdge(parents[u].first, u, -delta);
            net_.increaseEdge(u, parents[u].first, delta);
            u = parents[u].first;
        }

        return delta;
    }

    unsigned t_;
    Graph net_;
};

/******************************************************************************/

int main() {
    ifstream fin("maxflow.in");
    ofstream fout("maxflow.out");

    // Initializing graph
    unsigned n = 0;
    unsigned m = 0;
    fin >> n >> m;
    Graph graph(n);
    for(int i = 0; i < m; ++i){
        unsigned v = 0;
        unsigned u = 0;
        unsigned w = 0;
        fin >> v >> u >> w;
        graph.increaseEdge(v - 1, u - 1, w);
    }

    // Counting maximal flow
    MaxFlow maxFlow;
    fout << maxFlow(graph, 0, n - 1) << '\n';

    fin.close();
    fout.close();
}

/****************************GRAPH*********************************************/

Graph::Graph(unsigned int size) :
        size_(size),
        matrix_(size_, vector<unsigned>(size_, 0)) {}



void Graph::increaseEdge(unsigned from, unsigned to, int weight)
{
    assert(static_cast<int>(matrix_[from][to]) + weight >= 0);
    matrix_[from][to] += weight;
}



unsigned Graph::getSize() const
{
    return size_;
}



void Graph::getRelated(unsigned vertex, vector<pair_uu> &vertices) const
{
    vertices.clear();
    for(unsigned i = 0; i < size_; ++i){
        if(matrix_[vertex][i] != 0)
            vertices.push_back(make_pair(i, matrix_[vertex][i]));
    }
}
