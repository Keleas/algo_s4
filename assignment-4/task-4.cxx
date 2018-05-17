/****************************************************************************

Реализуйте структуру данных “массив строк” на основе **декартового дерева по неявному ключу** со следующими методами:

    // Добавление строки в позицию position.
    // Все последующие строки сдвигаются на одну позицию вперед.
    void InsertAt( int position, const std::string& value );
    // Удаление строки из позиции position.
    // Все последующие строки сдвигаются на одну позицию назад.
    void DeleteAt( int position );
    // Получение строки из позиции position.
    std::string GetAt( int position );

Все методы должны работать за O(log n) в среднем, где n – текущее количество строк в массиве.

*Формат входных данных*
Первая строка содержит количество команд k ≤ 106.
Последующие k строк содержат описания команд:
Команда “+ 10 hello”
означает добавление строки hello в позицию 10.
Команда “- 14”
означает удаление строки из позиции 14.
Команда “? 33”
означает запрос на вывод строки из массива в позиции 33.

*Формат выходных данных*
Выведите все строки, запрошенные командами “?”.

 |  in     | out |
 |---------|-----|
 |6        |krya |
 |+ 0 myau |gav  |
 |+ 0 krya |     |
 |? 0      |     |
 |+ 2 gav  |     |
 |- 1      |     |
 |? 1      |     |

****************************************************************************/

#include <iostream>
#include <iomanip>

// Treap с неявным ключом
class ImplicitTreap{
public:
    ImplicitTreap();
    ~ImplicitTreap();

    // Вставляет строку в положение
    void insert(size_t position, const std::string& value);
    // Удаляет строку по положению
    void remove(size_t position);
    // Очищает дерево
    void clear();
    // Возвращает строку по позиции
    std::string get(size_t position) const;

private:
    // Структура, реализующая узел
    struct Node{
        Node(const std::string& value);

        // Исправления treeSize
        void fix();

        // Сохраняет размер поддерева
        size_t treeSize;
        // Приоритет текущего узла
        int priority;
        // Значение для хранения
        std::string value;

        // Указатели для левых и правых детей
        Node* left;
        Node* right;
    };

private:
    // Разделяет дерево по положению, возвращает два дерева результатов
    std::pair<Node*, Node*> split(Node* node, size_t position);
    // Объединяет два дерева, возвращает дерево результатов
    Node* merge(Node* node1, Node* node2);
    // Рекурсивная функция для очистки дерева
    void clear(Node* node);

private:
    // Указатель на корень
    Node* _root;
};

/******************************************************************************/

int main() {
    size_t n = 0;
    std::cin >> n;
    ImplicitTreap stringArray;
    for (size_t i = 0; i < n; ++i) {
        char cmd;
        std::cin >> cmd;
        switch(cmd){
            case '+': {
                size_t position = 0;
                std::string val = "";
                std::cin >> position >> val;
                stringArray.insert(position, val);
                break;
            }
            case '?': {
                size_t position = 0;
                std::cin >> position;
                std::cout << stringArray.get(position) << '\n';
                break;
            }
            default: {
                size_t position = 0;
                std::cin >> position;
                stringArray.remove(position);
                break;
            }
        }
    }
    return 0;
}

/******************************************************************************/

ImplicitTreap::ImplicitTreap()
        : _root(nullptr)
{}



ImplicitTreap::~ImplicitTreap()
{
    clear();
}



void ImplicitTreap::clear()
{
    clear(_root);
    _root = nullptr;
}



void ImplicitTreap::clear(Node* node)
{
    if (node == nullptr)
        return;
    clear(node->left);
    clear(node->right);
    delete node;
}



void ImplicitTreap::insert(size_t position, const std::string& value)
{
    Node* current = new Node(value);
    // Разделить дерево по положению и объединить новый узел с правильным деревом, а затем слить результат с левым деревом
    std::pair<Node*, Node*> ans = split(_root, position);
    Node* right = merge(current, ans.second);
    _root = merge(ans.first, right);
}



void ImplicitTreap::remove(size_t position)
{
    // Разделить требуемый узел с обеих сторон и объединить два других дерева
    std::pair<Node*, Node*> ans1 = split(_root, position);
    std::pair<Node*, Node*> ans2 = split(ans1.second, 1);
    delete ans2.first;
    _root = merge(ans1.first, ans2.second);
}



std::string ImplicitTreap::get(size_t position) const
{
    // Спускаемся по дереву
    size_t l;
    Node* node = _root;
    do {
        l = (node->left != nullptr)?(node->left->treeSize):0;
        if (l == position)
            break;
        if (position < l) {
            node = node->left;
        }
        else {
            position -= l + 1;
            node = node->right;
        }
    } while (true);
    return node->value;
}



std::pair<ImplicitTreap::Node*, ImplicitTreap::Node*> ImplicitTreap::split(Node* node, size_t position)
{
    if (node == nullptr)
        return std::pair<Node*, Node*>(nullptr, nullptr);
    size_t l = (node->left != nullptr)?(node->left->treeSize) : 0;
    if (l >= position) {
        std::pair<Node*, Node*> ans = split(node->left, position);
        node->left = ans.second;
        node->fix();
        return std::make_pair(ans.first, node);
    }
    else {
        std::pair<Node*, Node*> ans = split(node->right, position - l - 1);
        node->right = ans.first;
        node->fix();
        return std::make_pair(node, ans.second);
    }
}



ImplicitTreap::Node* ImplicitTreap::merge(Node* node1, Node* node2)
{
    if (node2 == nullptr)
        return node1;
    if (node1 == nullptr)
        return node2;
    if (node1->priority > node2->priority) {
        node1->right = merge(node1->right, node2);
        node1->fix();
        return node1;
    }
    else {
        node2->left = merge(node1, node2->left);
        node2->fix();
        return node2;
    }
}

/******************************************************************************/

ImplicitTreap::Node::Node(const std::string& value)
        : value(value)
        , priority(rand())
        , left(nullptr)
        , right(nullptr)
        , treeSize(1)
{}



void ImplicitTreap::Node::fix()
{
    treeSize = 1;
    if (left != nullptr)
        treeSize += left->treeSize;
    if (right != nullptr)
        treeSize += right->treeSize;
}
