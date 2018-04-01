/****************************************************************************

Необходимо написать торгового советника для поиска арбитража.

Определение
Арбитраж - это торговля по цепочке различных валют в надежде заработать на небольших различиях в коэффициентах. Например, есть следующие курсы валют (на 03.05.2015):
GBP/USD: 0.67
RUB/GBP: 78.66
USD/RUB: 0.02

Имея 1$ и совершив цикл USD->GBP->RUB->USD, получим 1.054$. Таким образом заработав 5.4%.
Время работы – O(VE).

*Формат входных данных*
Первая строка содержит число N – количество возможных валют (размер таблицы котировок)
Далее следует построчное представление таблицы. Диагональные элементы (i, i) пропущены (подразумевается, что курс валюты к себе же 1.0).
В элементе таблицы (i, j) содержится обменный курс i->j.
Если обмен в данном направлении не производится, то -1.

*Формат выходных данных*
Выведите YES, если арбитраж есть, и NO, иначе.

 |  in       | out |
 |-----------|-----|
 |2          | NO  |
 |      10.0 |     |
 |0.09       |     |


 |  in                    | out |
 |------------------------|-----|
 |4                       | YES |
 |      32.1  1.50 78.66  |     |
 |0.03        0.04  2.43  |     |
 |0.67 21.22       51.89  |     |
 |0.01    -1  0.02        |     |


 |  in            | out |
 |----------------|-----|
 |3               | YES |
 |     0.67    -1 |     |
 |-1        78.66 |     |
 |0.02   -1       |     |

****************************************************************************/

#include <iostream>
#include <vector>

/*****************************************************************/

using std::vector;
using std::cin;
using std::cout;

/*****************************************************************/

class Graph {
public:
    Graph(unsigned verticesNumber);

    void addEdge(int from, int to, double weight);

    unsigned getSize() const;

    void getNext(int vertex, vector<int> &vertices) const;
    void getPrev(int vertex, vector<int> &vertices) const;

    double getWeight(int v, int u) const;

private:
    size_t size_;
    vector<vector<double>> matr_;
};

/****************************GRAPH********************************/

Graph::Graph(unsigned int size) :
        size_(size),
        matr_(size_, vector<double>(size_, -1)) {}


void Graph::addEdge(int from, int to, double weight)
{
    matr_[from][to] = weight;
}


unsigned Graph::getSize() const
{
    return size_;
}


void Graph::getNext(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (size_t i = 0; i < size_; i++)
        if (matr_[vertex][i] != -1)
            vertices.push_back(i);
}


void Graph::getPrev(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (size_t i = 0; i < size_; i++)
        if (matr_[i][vertex] != -1)
            vertices.push_back(i);
}


double Graph::getWeight(int v, int u) const
{
    return matr_[v][u];
}

/*****************************************************************/

// Вренуть true, если существвует арбитраж
// T = O(|E||V|^2) (O(|V|^4) для графа на матрице
// Алгоритм Беллмана-Форда обнаруживает только отрицательные циклы
// который может быть достигнут из начальной вершины,
// поэтому он запускается для каждой вершины графика
bool arbitrage(const Graph &graph) {
    // Запуск алгоритма Б.Ф. для каждой вершины
    for (size_t k = 0; k < graph.getSize(); ++k) {
        // Инициализация вектора стоимости i-ых валют
        // в начальной валюте
        vector<double> d(graph.getSize(), -1.0);
        // Начальная валюта
        d[k] = 1.0;
        vector<int> vertices(graph.getSize());
        // Реалаксирование вершин
        for (size_t i = 0; i < graph.getSize() - 1; ++i) {
            for (size_t v = 0; v < graph.getSize(); ++v) {
                graph.getPrev(v, vertices);
                for (int u : vertices)
                    if (d[u] != -1.0 && d[v] < d[u] * graph.getWeight(u, v))
                        d[v] = d[u] * graph.getWeight(u, v);
            }
        }
        // Поиск отрицательного цикла
        for (size_t v = 0; v < graph.getSize(); ++v) {
            graph.getPrev(v, vertices);
            for (int u : vertices)
                if (d[u] != -1.0 && d[v] < d[u] * graph.getWeight(u, v))
                    return true; // Вернуть true в случае успеха
        }
    }
    // Вернуть false, если отрицательный цикл не найден
    return false;
}

/******************************************************************************/

int main() {
    size_t n = 0;
    cin >> n;
    Graph graph(n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j) {
            if (i == j)
                continue;
            double x;
            cin >> x;
            graph.addEdge(i, j, x);
        }
    }

    cout << ((arbitrage(graph))?"YES":"NO");
    return 0;
}

