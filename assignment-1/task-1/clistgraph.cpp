#include <clistgraph.h>

using std::size_t;


CListGraph::CListGraph(unsigned int verticesNumber) :
    verticesNumber_(verticesNumber),
    in_(verticesNumber_),
    out_(verticesNumber_)
{}


CListGraph::CListGraph(const IGraph *graph) :
    verticesNumber_(graph->VerticesCount()),
    in_(verticesNumber_),
    out_(verticesNumber_)
{
    for (size_t i = 0; i < verticesNumber_; ++i) {
        vector<int> vertices;
        graph->GetNextVertices(i, vertices);
        for (size_t j : vertices)
            AddEdge(i, j);
    }
}


int CListGraph::VerticesCount() const
{
    return verticesNumber_;
}


void CListGraph::GetNextVertices(int vertex, vector<int> &vertices) const
{
    for (auto i : out_[vertex])
        vertices.push_back(i);
}


void CListGraph::GetPrevVertices(int vertex, vector<int> &vertices) const
{
    for (auto i: in_[vertex])
        vertices.push_back(i);
}


void CListGraph::AddEdge(int from, int to)
{
    if (in_.size() < out_.size()) {
        for (int i : in_[to])
            if (i == from)
                return;
    }
    else {
        for (int i : out_[from])
            if (i == to)
                return;
    }
    //откуда пришел
    in_[to].push_back(from);
     //куда пошел
    out_[from].push_back(to);
}




