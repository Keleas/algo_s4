/****************************************************************************

Задача в контесте - C.
Расстояние Хэмминга между двумя строками равной длины — это количество индексов, в которых символы этих строк не равны.
Определим расстояние от шаблона p до строки s как суммарное расстояние Хэмминга от p до всех подстрок s, имеющих длину |p|. В строке и в шаблоне некоторые символы стёрты. Нужно восстановить стёртые символы так, чтобы расстояние от p до s было минимально возможным.

Формат входного файла.
В первой строке дана строка s, во второй — шаблон p. Обе строки непусты, имеют длину не более 1000 и состоят из символов `0', `1' и `?'. `?' обозначает стёртые символы, которые нужно восстановить. Длина строки p не превосходит длины строки s.

Формат выходного файла.
В первой строке выведите минимальное расстояние от p до s после восстановления всех стёртых символов. Во второй и третьей строках соответственно выведите s и p, в которых символы '?' заменены на '0' и '1'.

| in   |out |
|------|----|
|00?   |2   |
|1?    |000 |
|      |10  |

****************************************************************************/

#include <iostream>
#include <ctime>
#include <vector>
#include <map>
#include <queue>
#include <climits>
#include <functional>

/******************************************************************************/

// Структура, сохраненная в матрице ребер
struct Edge {
    int capacity;
    int flow;
};

// Используется для хранения отношения - question <-> vertex
enum StringType {
    None = -1, //Еще не определено
    Pattern, // Вопрос в шаблоне
    Str, // Вопрос в str
    Special // 1 или 0 вершина
};

// Используется для хранения отношения vertex -> question
struct VertexInfo {
    StringType type;
    int index;
};

// Сеть магазинов, используемая для поиска расстояния от хамминга
struct Network {
    Network();

    // Увеличивает емкость на 1 для ребер from -> to и to -> from
    void increaseCapacity(int from, int to);

    // Матрица ребер
    std::vector<std::vector<Edge>> matrix;

    unsigned hammingDistance;
    unsigned numberOfVertices;
    unsigned source;
    unsigned drain;

    std::string pattern;
    std::string str;

    // Отношение vertex->question
    std::vector<std::vector<int>> vertexToQuestion;
    // Отношение question->vertex (0 для вопроса в шаблоне, 1 для str)
    std::vector<VertexInfo> questionToVertex;
};

/******************************************************************************/

// Находит и устанавливает максимальный поток в сети с использованием алгоритма Динича
unsigned FindMaxFlow(Network& net);

// Используется в FindMaxFlow. Находит самый короткий путь от источника к каждой вершине в сети
// Возвращает true, если дренаж доступен из источника.
// Самые короткие пути хранятся в векторах расстояний
bool FindMaxFlowBFS(Network& net, std::vector<int>& distances);

// Используется в FindMaxFlow. Находит блокирующий поток в сети.
// Возвращает значение найденного потока
// distances - кратчайшие пути к каждой вершине из источника
// (v, p[v]) - первый край для v, из которого может быть достигнут сток
// v - текущая вершина
// minC - максимальный поток в дополнительной сети
int FindMaxFlowDFS(Network& net, std::vector<int>& distances, std::vector<int>& p, int v, int minC);

/******************************************************************************/

// Возвращает минимальное расстояние Хэмминга и оптимально заполняет str и узор
unsigned hammingDistance(std::string& str, std::string& pattern);

// Создает сеть для поиска расстояния Хэмминга
void buildNetwork(Network &net);

// Находит вершины, достижимые из нулевой вершины, используя dfs
// и заполняет вопросы по str и шаблону
void FindZeros(Network &net, int v, std::vector<int> &visited);

/******************************************************************************/

int main()
{
    std::string pattern = "", str = "";
    std::cin >> str;
    std::cin >> pattern;


    std::cout << hammingDistance(str, pattern) << std::endl;
    std::cout << str << std::endl;
    std::cout << pattern << std::endl;

    return 0;
}

/******************************************************************************/

Network::Network() :
        numberOfVertices(2),
        source(0),
        drain(1),
        matrix(2007, std::vector<Edge>(2007, {0, 0})),
        vertexToQuestion(2, std::vector<int>(2007, -1)),
        questionToVertex(2007, {StringType::None, -1}),
        pattern(""),
        str("")
{
    questionToVertex[0] = {StringType::Special, 2};
    questionToVertex[1] = {StringType::Special, 2};
}



void Network::increaseCapacity(int from, int to)
{
    matrix[from][to].capacity += 1;
    matrix[to][from].capacity += 1;
}

/******************************************************************************/

unsigned FindMaxFlow(Network& net)
{
    unsigned maxFlow = 0;
    std::vector<int> distances(net.numberOfVertices);
    std::vector<int> p(net.numberOfVertices);

    // В то время как утечка достижима, увеличивая поток
    while (FindMaxFlowBFS(net, distances)) {
        // Инициализация массива указателей (см. Объявление FindMaxFlow DFS)
        for (int position = 0; position < net.numberOfVertices; position++)
            p[position] = 0;

        // Increasing flow
        int currentFlow;
        do {
            currentFlow = FindMaxFlowDFS(net, distances, p, net.source, INT_MAX);
            maxFlow += currentFlow;
        } while (currentFlow != 0);
    }

    return maxFlow;
}


bool FindMaxFlowBFS(Network& net, std::vector<int>& distances)
{
    // Поиск кратчайших путей из источника в каждую вершину с использованием BFS
    for (int i = 0; i < net.numberOfVertices; ++i)
        distances[i] = -1;

    std::queue<unsigned> verticesQueue;
    verticesQueue.push(net.source);
    distances[net.source] = 0;

    while (!verticesQueue.empty()) {
        unsigned v = verticesQueue.front();
        verticesQueue.pop();

        for (unsigned u = 0; u < net.numberOfVertices; ++u) {
            unsigned vertex = u;
            if (distances[vertex] == -1 &&
                net.matrix[v][u].flow < net.matrix[v][u].capacity) {
                distances[vertex] = distances[v] + 1;
                verticesQueue.push(vertex);
            }
        }
    }

    // Возвратите true, если дренаж достигнут
    return (distances[net.drain] != -1);
}



int FindMaxFlowDFS(Network& net, std::vector<int>& distances, std::vector<int>& p, int v, int minC)
{
    if (minC == 0 || v == net.drain)
        return minC;

    for (int u = p[v]; u < net.numberOfVertices; ++u) {
        p[v]++;

        // Если невозможно увеличить поиск остановки потока в этом направлении
        if (net.matrix[v][u].capacity <= net.matrix[v][u].flow)
            continue;

        // If u is related with v continue search
        if (distances[u] == distances[v] + 1) {
            int newMinC = std::min(minC, net.matrix[v][u].capacity - net.matrix[v][u].flow);
            int delta = FindMaxFlowDFS(net, distances, p, u, newMinC);
            if (delta > 0) {
                // Увеличение потока в найденном пути
                net.matrix[v][u].flow += delta;
                net.matrix[u][v].flow -= delta;
                return delta;
            }
        }
    }

    return 0;
}

/******************************************************************************/

unsigned hammingDistance(std::string& str, std::string& pattern)
{
    // Initializing network
    Network net;
    net.hammingDistance = 0;
    net.pattern = pattern;
    net.str = str;
    buildNetwork(net);

    // Увеличьте расстояние Хэмминга путем максимального потока в построенной сети и
    // разделить граф на две части
    net.hammingDistance += FindMaxFlow(net);

    // Найти вершины, достижимые из нулевой вершины в
    // вопросы остаточной сети и заполнения
    std::vector<int> visited(net.numberOfVertices, 0);
    FindZeros(net, 0, visited);
    // Заполните другие вопросы с помощью
    for (int i = 0; i < net.pattern.length(); ++i)
        if (net.pattern[i] == '?')
            net.pattern[i] = '1';
    for (int i = 0; i < net.str.length(); ++i)
        if (net.str[i] == '?')
            net.str[i] = '1';

    str = net.str;
    pattern = net.pattern;
    return net.hammingDistance;
}



void FindZeros(Network& net, int v, std::vector<int>& visited)
{
    // DFS
    visited[v] = 1;

    // Заполните вопросы, если вершина достижима
    if (net.questionToVertex[v].type == StringType::Pattern)
        net.pattern[net.questionToVertex[v].index] = '0';
    if (net.questionToVertex[v].type == StringType::Str)
        net.str[net.questionToVertex[v].index] = '0';

    // Запуск поиска из других вершин
    for (int u = 0; u < net.numberOfVertices; ++u)
        if (visited[u] == 0 &&
            net.matrix[v][u].capacity > net.matrix[v][u].flow)
            FindZeros(net, u, visited);
}



void buildNetwork(Network& net)
{
    // Создает сеть для поиска расстояния Хэмминга
    // Если 1 соответствует 0 - расстояние Хэмминга увеличивается на 1
    // Если ? соответствует 1 - емкость в краю <вершина для этого?> - <0> увеличивается на 1
    // Если ? соответствует 0 - емкость в краю <вершина для этого?> - <0> увеличивается на 1
    // Если ? соответствует ? - емкость в вершине <вершина для первого?> - <вершина для второго?> увеличивается на 1
    std::string &str = net.str;
    std::string &patt = net.pattern;
    int patternLength = (int) patt.length();
    for (int strPos = 0; strPos < str.length() - patt.length() + 1; ++strPos) {
        for (int pattPos = 0; pattPos < patternLength; ++pattPos) {

            // 1 соответствует 0
            if (patt[pattPos] == '1' && str[strPos + pattPos] == '0' ||
                patt[pattPos] == '0' && str[strPos + pattPos] == '1') {
                net.hammingDistance++;
            }

            // Если между этим вопросом и вершиной нет никакой связи, добавьте это соотношение
            if (patt[pattPos] == '?') {
                if (net.vertexToQuestion[StringType::Pattern][pattPos] == -1) {
                    net.numberOfVertices++;
                    VertexInfo temp = {StringType::Pattern, pattPos};
                    net.questionToVertex[net.numberOfVertices - 1] = temp;
                    net.vertexToQuestion[StringType::Pattern][pattPos] = net.numberOfVertices - 1;
                }
            }
            if (str[strPos + pattPos] == '?') {
                if (net.vertexToQuestion[StringType::Str][strPos + pattPos] == -1) {
                    net.numberOfVertices++;
                    VertexInfo temp = {StringType::Str, strPos + pattPos};
                    net.questionToVertex[net.numberOfVertices - 1] = temp;
                    net.vertexToQuestion[StringType::Str][pattPos + strPos] = net.numberOfVertices - 1;
                }
            }

            // Проверьте и обработайте все возможные комбинации
            if (patt[pattPos] == '?') {
                switch (str[strPos + pattPos]) {
                    case '0':
                        net.increaseCapacity(0, net.vertexToQuestion[StringType::Pattern][pattPos]);
                        break;
                    case '1':
                        net.increaseCapacity(
                                net.vertexToQuestion[StringType::Pattern][pattPos], 1);
                        break;
                    case '?':
                        net.increaseCapacity(
                                net.vertexToQuestion[StringType::Pattern][pattPos],
                                net.vertexToQuestion[StringType::Str][strPos + pattPos]);
                        break;
                }
            }
            if (str[strPos + pattPos] == '?') {
                switch (patt[pattPos]) {
                    case '0':
                        net.increaseCapacity(0, net.vertexToQuestion[StringType::Str][strPos + pattPos]);
                        break;
                    case '1':
                        net.increaseCapacity(1, net.vertexToQuestion[StringType::Str][strPos + pattPos]);
                        break;
                }
            }
        }
    }
}

