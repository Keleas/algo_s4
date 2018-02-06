#ifndef CLISTGRAPH_H
#define CLISTGRAPH_H

#include <igraph.h>
#include <list>

using std::list;

class CListGraph : public IGraph {
public:
    //стандартный конструктор
    CListGraph(unsigned int verticesNumber);

    //преобразование формат графа к текущему
    CListGraph(const IGraph* graph);

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

    //ребра в вершину
    vector<list<int>> in_;

    //ребра из вершины
    vector<list<int>> out_;
};

#endif // CLISTGRAPH_H
