#include <carcgraph.h>
#include <iostream>

using std::size_t;

CArcGraph::Edge::Edge(int from, int to) :
    from(from),
    to(to)
{}


CArcGraph::CArcGraph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber)
{}


CArcGraph::CArcGraph(const IGraph *graph) :
    verticesNumber_(graph->VerticesCount())
{
    for (size_t i = 0; i < verticesNumber_; ++i) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (size_t j : vertices)
            AddEdge(i, j);
    }
}


int CArcGraph::VerticesCount() const
{
    return verticesNumber_;
}


void CArcGraph::AddEdge(int from, int to)
{
    // граф без петель
    for (const Edge& i : edges_)
        if (i.from == from && i.to == to)
            return;

    Edge edge(from, to);
    edges_.push_back(edge);
}


void CArcGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    for (const Edge& i : edges_)
        if (i.from == vertex)
            vertices.push_back(i.to);
}


void CArcGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    for (const Edge& i: edges_)
        if (i.to == vertex)
            vertices.push_back(i.from);
}
