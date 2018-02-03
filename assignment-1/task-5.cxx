/****************************************************************************

Единственный способ попасть в Зал Круглых Столов – пройти через Колонный Коридор.
Стены Коридора изображаются на карте прямыми линиями, которые параллельны осиOY системы координат.
Вход в Коридор находится снизу, а выход из Коридора в Зал – сверху.
В Коридоре есть цилиндрические (на карте круглые) Колонны одинакового радиуса R.
Разработайте алгоритм, который по информации о размерах Коридора, и размещения Колонн определяет диаметр наибольшего из Круглых Столов, который можно пронести через такой Коридор, сохраняя поверхность Стола горизонтальной.

*Формат ввода*
В первой строке задано два целых числа XL и XR - x-координаты левой и правой стен Коридора.
Во второй строке находится целое число R (1≤R≤1000000) - радиус всех Колон.
В третьей - целое число N (1≤N≤200), задающее количество Колон.
Далее идут N строк, в каждой из которых по два целых числа – x- и y-координаты центра соответствующей Колоны.
Все входные координаты – целые числа, не превышающие по модулю 1000000.

*Формат вывода*
Вывести одно число - искомый диаметр наибольшего Стола.
Диаметр нужно выводить с точностью 3 знака после десятичной точки (даже в случае, если он окажется целым).
Если нельзя пронести ни одного Стола, то ответ должен быть: 0.000

Точность 3 знака после точки, по обычнам правилам округления, означает, что ответ, который выводится в выходной файл, должен отличатся от точного не более чем на 5×10−4 (то есть на 0.0005). Например, если точный ответ 1.234567, то в файле должно находится число 1.235. Если точный ответ 5.0005, то необходимо округлять в большую сторону, то есть в файл необходимо вывести 5.001.

 |   in   | out    |
 |--------|--------|
 |0 90    | 47.000 |
 |3       |        |
 |4       |        |
 |10 10   |        |
 |70 10   |        |
 |50 50   |        |
 |10 90   |        |

 (см еще два тестовых случая в README.md или на контесте)

****************************************************************************/

#include <iostream>

int main()
{
    return 0;
}
