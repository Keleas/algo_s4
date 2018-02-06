#ifndef CMATRIXGRAPH_H
#define CMATRIXGRAPH_H

#include <igraph.h>

class CMatrixGraph : public IGraph {
public:
    //стандартный конструктор
    CMatrixGraph(unsigned int verticesNumber);

    //преобразование формат графа к текущему
    CMatrixGraph(const IGraph* graph);

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

    //матрица смежности
    vector<vector<bool>> edges_;
};

#endif // CMATRIXGRAPH_H
