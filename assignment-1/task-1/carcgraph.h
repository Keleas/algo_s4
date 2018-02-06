#ifndef CARCGRAPH_H
#define CARCGRAPH_H

#include <igraph.h>

class CArcGraph : public IGraph {
public:
    //стандартный конструктор
    CArcGraph(unsigned int verticesNumber);

    //преобразование формат графа к текущему
    CArcGraph(const IGraph* graph);

    //добавить ор. ребро графа
    //from - откуда, to - куда
    virtual void AddEdge(int from, int to) override;

    //вернуть количество вершин
    virtual int VerticesCount() const override;

    //перейти к следующей вершине
    virtual void GetNextVertices(int vertex, vector<int>& vertices) const override;

    //перейти к предыдущей вершине
    virtual void GetPrevVertices(int vertex, vector<int>& vertices) const override;

private:
    //количество вершин графа
    unsigned int verticesNumber_;

    //ориентированное ребро
    struct Edge
    {
        Edge(int from, int to);
        int from;
        int to;
    };

    //матрица смежности
    vector<Edge> edges_;
};

#endif // CARCGRAPH_H
