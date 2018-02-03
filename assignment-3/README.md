# Задание №3 по курсу "Алгоритмы и стркутуры данных". Семестр 2.

Сдать задание нужно до 29 апреля.

Каждое решение проверить на https://contest.yandex.ru/contest/4314/ .

-----------------------------------------------------------

## Задача № 1. «Минимальное остовное дерево» (5 баллов)

Задача A в контесте.

Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
Вариант 1. С помощью алгоритма Прима.
Вариант 2. С помощью алгоритма Крускала.
Вариант 3. С помощью алгоритма Борувки.
Один вариант на всех не брать =)

*Формат входного файла*
Первая строка входного файла содержит два натуральных числа 𝑛 и 𝑚 — количество вершин и ребер графа соответственно (1 ≤ n ≤ 20000, 0 ≤ m ≤ 100000).
Следующие 𝑚 строк содержат описание ребер по одному на строке.
Ребро номер 𝑖 описывается тремя натуральными числами 𝑏𝑖, 𝑒𝑖 и 𝑤𝑖 — номера концов ребра и его вес соответственно (1 ≤ 𝑏𝑖, 𝑒𝑖 ≤ 𝑛, 0 ≤ 𝑤𝑖 ≤ 100000).

*Формат выходного файла*
Выведите единственное целое число - вес минимального остовного дерева.

 | in   | out |
 |------|-----|
 |4 4   | 7   |
 |1 2 1 |     |
 |2 3 2 |     |
 |3 4 5 |     |
 |4 1 4 |     |


-----------------------------------------------------------

## Задача № 2. Приближенное решение задачи коммивояжера. (5 баллов)

Задачи в контесте нет.
Найдите приближенное решение задачи коммивояжера в полном графе на плоскости с помощью минимального остовного дерева, построенного в первой задаче.
Оцените качество приближения на случайном наборе точек, нормально распределенном на плоскости с дисперсией 1. Нормально распределенный набор точек получайте с помощью преобразования Бокса-Мюллера.
При фиксированном N, количестве вершин графа, несколько раз запустите оценку качества приближения. Вычислите среднее значение и среднеквадратичное отклонение качества приближения для данного N.
Запустите данный эксперимент для всех N в некотором диапазоне, например, [2, 10].
Автоматизируйте запуск экспериментов.
В решении требуется разумно разделить код на файлы. Каждому классу - свой заголовочный файл и файл с реализацией.

-----------------------------------------------------------

## Задача № 3. Максимальный поток в неориентированном графе. (5 балла)

Задача в контесте - B.
Задан ориентированный граф, каждое ребро которого обладает целочисленной пропускной способностью. Найдите максимальный поток из вершины с номером 1 в вершину с номером 𝑛.

*Формат входного файла*
Первая строка входного файла содержит 𝑛 и 𝑚 — количество вершин и количество ребер графа (2 ≤ 𝑛 ≤ 100, 1 ≤ 𝑚 ≤ 1000). Следующие 𝑚 строк содержат по три числа: номера вершин, которые соединяет соответствующее ребро графа и его пропускную способность. Пропускные способности не превосходят 105.

*Формат выходного файла*
В выходной файл выведите одно число — величину максимального потока из вершины с номером 1 в вершину с номером n.

| in   |out |
|------|----|
|4 5   | 3  |
|1 2 1 |    |
|1 3 2 |    |
|3 2 1 |    |
|2 4 2 |    |
|3 4 1 |    |


-----------------------------------------------------------

## Задача № 4. Расстояние Хэмминга. (5 баллов)

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
