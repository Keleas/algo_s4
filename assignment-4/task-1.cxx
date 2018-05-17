/****************************************************************************

Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.

*Формат входных данных*
В первой строке заданы 2 числа: размер последовательности N и количество диапазонов M. Следующие N целых чисел задают последовательность. Далее вводятся M пар чисел - границ диапазонов.  Гарантируется, что каждый диапазон содержит как минимум 2 элемента.

*Формат выходных данных*
Для каждого из M диапазонов напечатать элемент последовательности - 2ю порядковую статистику. По одному числу в строке.

Для решения задачи используйте структуру данных **Sparse Table**. Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(n log n).

 |  in                 | out |
 |---------------------|-----|
 |10 3                 | 2   |
 |1 2 3 4 5 6 7 8 9 10 | 2   |
 |1 2                  | 3   |
 |1 10                 |     |
 |2 7                  |     |

****************************************************************************/

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <algorithm>

/**************************************************************************************************/

// Объект функции для поиска 2-й статистики по сегменту
class R2Q {
public:
    // Принимает последовательность int и выполняет предварительную обработку
    R2Q(const std::vector<int> & sequence)
        : _sequence(sequence)
        , _n(sequence.size())
        , _sparseTable((size_t)(ceil(log2(_n))),
                       std::vector<std::pair<int*, int*>>(_n, std::pair<int*, int*>(0, 0)))
    {
        // Предварительное подсчет двоичных логарифмов для каждого индекса в последовательности
        for (size_t i = 0; i < _n + 1; ++i)
            _log2.push_back((size_t)ceil(log2(i)));

        // Инициализация 1-й строки таблицы с элементами последовательности
        for (size_t i = 0; i < _n; ++i) {
            _sparseTable[0][i].first = &_sequence[i];
            _sparseTable[0][i].second = &_sequence[i];
        }

        // Инициализация других строк таблицы с помощью первых двух наименьших элементов сегмента
        for (size_t i = 1; i < _sparseTable.size(); ++i) {
            for (size_t j = 0; j < _n - (1 << i) + 1; ++j) {
                std::pair<int*, int*> mp = getMinPair(_sparseTable[i - 1][j],
                                                      _sparseTable[i - 1][j + (1 << (i - 1))]);
                _sparseTable[i][j].first = mp.first;
                _sparseTable[i][j].second = mp.second;
            }
        }
    }

    // Возвращает вторую статистику по сегменту [a, b]
    int operator()(size_t a, size_t b)
    {
        // Размер требуемого разреженного сегмента стола
        size_t k = _log2[b - a + 1] - 1;
        // Поиск второго наименьшего элемента из двух сегментов
        return *getMinPair(_sparseTable[k][a], _sparseTable[k][b - (1 << k) + 1]).second;
    }

private:
    // Возвращает пару из двух наименее уникальных элементов для двух пар, где
    // a.first <= a.second и b.first <= b.second
    std::pair<int*, int*> getMinPair(std::pair<int*, int*> a, std::pair<int*, int*> b)
    {
        std::pair<int*, int*> ans;
        // Инициализация и сортировка вектора элементов
        std::vector<int*> order{a.first, a.second, b.first, b.second};
        std::sort(order.begin(), order.end(), [](int* l, int* r){return *l < *r;});

        // Возьмем первый элемент и отдельный минимальный элемент из остальных
        ans.first = order[0];
        for (short i = 1; i < 4; ++i)
            if (order[i] != order[0]) {
                ans.second = order[i];
                break;
            }
        return ans;
    }

private:
    // Сохраняет последовательность int
    std::vector<int> _sequence;
    // Сохраняет размер последовательности
    size_t _n;
    // Сохраняет двоичные логарифмы
    std::vector<size_t> _log2;
    // Магазины редкой таблицы
    std::vector<std::vector<std::pair<int*, int*>>> _sparseTable;
};

/**************************************************************************************************/

int main() 
{
    size_t n = 0;
    size_t m = 0;
    std::cin >> n >> m;

    std::vector<int> sequence(n);
    for (size_t i = 0; i < n; i++) {
        int x = 0;
        std::cin >> x;
        sequence[i] = x;
    }

    R2Q r2q(sequence);
 
    for (size_t i = 0; i < m; i++) {
        size_t a = 0;
        size_t b = 0;
        std::cin >> a >> b;
        std::cout << r2q(a - 1, b - 1) << '\n';
    }

    return 0;
}
