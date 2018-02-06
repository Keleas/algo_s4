#include <cmatrixgraph.h>
#include <iostream>

using std::size_t;

CMatrixGraph::CMatrixGraph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber),
    edges_(verticesNumber_)
{
    for (vector<bool>& i : edges_)
        i.assign(verticesNumber_, false);
}


CMatrixGraph::CMatrixGraph(const IGraph *graph) :
    verticesNumber_(graph->VerticesCount()),
    edges_(verticesNumber_)
{
    for (vector<bool>& i : edges_)
        i.assign(verticesNumber_, false);

    for (size_t i =  0; i < verticesNumber_; ++ i) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (size_t j : vertices)
            AddEdge(i, j);

    }
}


int CMatrixGraph::VerticesCount() const
{
    return verticesNumber_;
}


void CMatrixGraph::AddEdge(int from, int to)
{
    edges_[from][to] = true;
}


void CMatrixGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear(); // на случай предыдущего использования
    for (size_t i =  0; i < verticesNumber_; ++i)
        if (edges_[vertex][i])
            vertices.push_back(i);
}


void CMatrixGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear(); // на слуйчай предыдущего использования
    for (size_t i  = 0; i < verticesNumber_; ++i)
        if (edges_[i][vertex])
            vertices.push_back(i);
}
