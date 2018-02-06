#ifndef CSETGRAPH_H
#define CSETGRAPH_H

#include<igraph.h>
#include <unordered_set>

using std::unordered_set;

class CSetGraph : public IGraph {
public:
    //стандартный конструктор
    CSetGraph(unsigned int verticesNumber);

    //преобразование формат графа к текущему
    CSetGraph(const IGraph* graph);

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
    vector<unordered_set<int>> in_;

    //ребра из вершины
    vector<unordered_set<int>> out_;

};

#endif // CSETGRAPH_H
