#include <csetgraph.h>
#include <iostream>

using std::size_t;

CSetGraph::CSetGraph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber),
    in_(verticesNumber_),
    out_(verticesNumber_)
{}


CSetGraph::CSetGraph(const IGraph *graph) :
    verticesNumber_(graph->VerticesCount()),
    in_(verticesNumber_),
    out_(verticesNumber_)
{
    for (size_t i = 0; i < verticesNumber_; ++ i) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (size_t j : vertices)
            AddEdge(i, j);
    }
}


int CSetGraph::VerticesCount() const
{
    return verticesNumber_;
}


void CSetGraph::AddEdge(int from, int to)
{
    out_[from].insert(to);
    in_[to].insert(from);
}


void CSetGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (auto i : out_[vertex])
        vertices.push_back(i);
}


void CSetGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    vertices.clear();
    for (auto i : in_[vertex])
        vertices.push_back(i);
}

