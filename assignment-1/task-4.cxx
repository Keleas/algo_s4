/****************************************************************************

Дана матрица смежности ориентированного графа. Проверьте, содержит ли граф вершину-сток.
То есть вершину, в которую ведут ребра из всех вершин, и из которой не выходит ни одного ребра. Требуемая сложность O(V).

Ввод: n:размерность матрицы, n строк матрицы.
Вывод: "YES" или "NO"

 |   in   | out |
 |--------|-----|
 |3       | NO  |
 |0 1 1   |     |
 |0 0 1   |     |
 |1 0 0   |     |
 |--------|-----|
 |4       | YES |
 |0 1 0 1 |     |
 |0 0 0 0 |     |
 |1 1 0 0 |     |
 |1 1 0 0 |     |
 |--------|-----|
 |4       | NO  |
 |0 1 0 1 |     |
 |0 0 0 0 |     |
 |1 0 0 0 |     |
 |1 1 0 0 |     |

****************************************************************************/

#include <iostream>
#include <vector>

using std::vector;
using std::size_t;

bool isThereStok(vector<vector<int>> graph)
{
    unsigned int n = graph.size();
    vector<bool> isVertexStock(n, true); //возможность вершин быть стеком

    for (size_t curVertex = 0; curVertex < n; ++curVertex) {
        if (!isVertexStock[curVertex])
            continue;

        if (graph[curVertex][curVertex] == 0) {
            size_t nextLineVertex = (curVertex + 1) % n;

            //проверяем таблицу
            while (nextLineVertex != curVertex) {
                if (graph[curVertex][nextLineVertex] == 0)
                    //т.е. из данной нельзя пойти в следущую => следущая не может быть стоком
                    isVertexStock[nextLineVertex] = false;
                else {
                    //из данной вершины можно куда-то пойти
                    isVertexStock[curVertex] = false;
                    break;
                }
                nextLineVertex = (nextLineVertex + 1) % n;
            }

            //осталcя вариант, если это изолированная вершина или в нее входят не все
            //пользуемся единственностью стока
            if (curVertex == nextLineVertex) {
                for (size_t nextColumnVertex = 0; nextColumnVertex < n; ++nextColumnVertex) {
                    if (graph[nextColumnVertex][curVertex] == 0 && curVertex != nextColumnVertex)
                        return false;
                }
                //в противном случае это сток
                return true;
            }
        }
        else
            isVertexStock[curVertex] = false; //петля
    }
    //сток не удалось найти
    return false;
}


int main()
{
    unsigned int n = 0;
    std::cin >> n;
    vector<vector<int>> graph(n, vector<int>(n, 0));

    for (size_t i  = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            std::cin >> graph[i][j];
    }

    if (isThereStok(graph))
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;

    return 0;
}

