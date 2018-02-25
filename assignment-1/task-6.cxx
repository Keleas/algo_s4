/****************************************************************************

Дан ориентированный граф. Определите, какое минимальное количество ребер необходимо
добавить, чтобы граф стал сильносвязным. В графе возможны петли.

*Формат ввода*
В первой строке указывается число вершин графа V, во второй – число ребер E,
в последующих – E пар вершин, задающих ребра.

*Формат вывода*
Минимальное число ребер k.


 |  in  | out |
 |------|-----|
 | 4    | 1   |
 | 4    |     |
 | 1 2  |     |
 | 2 3  |     |
 | 3 1  |     |
 | 3 4  |     |

 |  in  | out |
 |------|-----|
 | 5    | 2   |
 | 4    |     |
 | 1 2  |     |
 | 3 4  |     |
 | 4 5  |     |
 | 5 3  |     |

****************************************************************************/

#include <iostream>
#include <vector>
#include <list>
#include <stack>

/***********************************************************/

using std::stack;
using std::vector;
using std::list;

/***********************************************************/

class Graph {
public:
    //стандартный конструктор
    Graph(unsigned int verticesNumber);

    //добавить ор. ребро графа
    //from - откуда, to - куда
    void AddEdge(int from, int to);

    //вернуть количество вершин
    int VerticesCount() const;

    //перейти к следующей вершине
    void GetNextVertices(int vertex, vector<int>& vertices) const;

    //перейти к предыдущей вершине
    void GetPrevVertices(int vertex, vector<int>& vertices) const;

private:
    //количество вершин графа
    unsigned int verticesNumber_;

    //ребра в вершину
    vector<list<int>> in_;

    //ребра из вершины
    vector<list<int>> out_;
};

/***********************************************************/

class Compress {
public:
    //сжать поданный граф
    Graph operator() (Graph* graph);

private:
    //поиск в глубину с обработкой
    void DFS(int vertex);

    //построить сжатый граф по компонентам и вернуть его
    Graph compress();

    //копия поданного графа
    Graph* graph_;

    //компоненты сильной-связности
    vector<int> components_;

    //количество компонент
    unsigned int componentsNumber_;

    //глубина каждой вершины
    vector<int> low_;

    //вспомогательный стэк для DFS
    stack<int> stack_;

    //пройденные вершины
    vector<bool> visited_;

    //время входа в вершину
    int time_;
};

/***********************************************************/

Graph Compress::operator ()(Graph* graph)
{
    // "Конструктор"
    graph_ = graph;
    time_ = 0;
    componentsNumber_ = 0;
    components_.assign(graph_->VerticesCount(), 0);
    low_.assign(graph_->VerticesCount(), 0);
    visited_.assign(graph_->VerticesCount(), false);

    // Формирование компонент сильной-связности
    for (int curVertex = 0; curVertex < graph_->VerticesCount(); ++curVertex) {
        if (!visited_[curVertex])
            DFS(curVertex);
    }
    return compress();
}


void Compress::DFS(int vertex)
{
    stack_.push(vertex);
    visited_[vertex] = true;
    low_[vertex] = time_++;
    bool isRoot = true; // корень компоненты

    vector<int> children;
    graph_->GetNextVertices(vertex, children);

    for (auto child : children) {
            if (!visited_[child])
                DFS(child);

            // т.е. ранее мы были в вершине child => vertex не может быть корнем компоненты
            if (low_[child] < low_[vertex]) {
                low_[vertex] = low_[child];
                isRoot = false;
            }
    }

    // Если это корень компоненты сильной-связности, зафиксируем все вершины
    // данной компоненты
    if (isRoot) {
        while (true) {
            int curVertex = stack_.top();
            stack_.pop();
            components_[curVertex] = componentsNumber_;
            low_[curVertex] = graph_->VerticesCount() + 1;
            if (curVertex == vertex)
                break;
        }
        ++componentsNumber_;
    }
}


Graph Compress::compress()
{
    Graph compressGraph(componentsNumber_);

    for (int curVertex = 0; curVertex < graph_->VerticesCount(); ++curVertex) {
        vector<int> vertices;
        graph_->GetNextVertices(curVertex, vertices);
        for (auto child : vertices)
            // Если ребенок вершины в другой компоненте, то между ними есть ребро
            if (components_[child] != components_[curVertex])
                compressGraph.AddEdge(components_[curVertex], components_[child]);
    }
    return compressGraph;
}

/***********************************************************/

Graph::Graph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber),
    in_(verticesNumber_),
    out_(verticesNumber_)
{}


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


void Graph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (auto i: in_[vertex])
        vertices.push_back(i);
}


void Graph::AddEdge(int from, int to)
{
        for (int i : out_[from])
            if (i == to)
                return;

    in_[to].push_back(from);
    out_[from].push_back(to);
}

/***********************************************************/

int main()
{
    unsigned int V = 0;
    std::cin >> V;
    Graph graph(V);

    int E;
    std::cin >> E;
    for (int i = 0; i < E; ++i) {
        int from, to;
        std::cin >> from >> to;
        graph.AddEdge(from - 1, to - 1);
    }

    Compress compress;
    Graph compress_graph = compress(&graph);

    int beginNumber{0}, endNumber{0};
    if (compress_graph.VerticesCount() > 1) {
        for (int curVertex = 0; curVertex < compress_graph.VerticesCount(); ++curVertex) {
            vector<int> vertices;

            compress_graph.GetNextVertices(curVertex, vertices);
            if (vertices.size() == 0)
                ++endNumber;
            compress_graph.GetPrevVertices(curVertex, vertices);
            if (vertices.size() == 0)
                ++beginNumber;
        }
    }

    std::cout << std::max(beginNumber, endNumber);
    return 0;
}
