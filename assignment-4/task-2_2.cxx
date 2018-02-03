/****************************************************************************

**2\_2. Художник и фотограф.** У художника-авангардиста есть полоска разноцветного холста. За один раз он перекрашивает некоторый отрезок полоски в некоторый цвет. После каждого перекрашивания специально обученный фотограф делает снимок части получившегося творения для музея современного искусства. Для правильного экспонирования требуется знать яркость самого темного цвета на выбранном фотографом отрезке. Напишите программу для определения яркости самого темного цвета на отрезке. Требуемая скорость определения яркости - O(log N).
Цвет задается тремя числами R, G и B (0 ≤ R, G, B ≤ 255), его яркость = R + G + B. Цвет (R1, G1, B1) темнее цвета (R2, G2, B2), если R1 + G1 + B1 < R2 + G2 + B2.

*Формат входных данных*
Первая строка содержит число N – длина отрезка (координаты [0...N-1]). Затем следует N строк по 3 числа – цвета отрезка.
Следующая строка содержит число K – количество перекрашиваний и фотографирований. Затем задано K строк, описывающих перекрашивание и фотографирование. В каждой такой строке 7 натуральных чисел: C, D, R, G, B, E, F, где [C, D] – координаты перекрашиваемого отрезка, (R, G, B) – цвет покраски, [E, F] – фотографируемый отрезок.

*Формат выходных данных*
Требуется вывести K строк. В каждой строке – яркость самого темного цвета на отрезке [E, F] после соответствующего окрашивания.

 |  in             | out |
 |-----------------|-----|
 |5                |30   |
 |7 40 3           |181  |
 |54 90 255        |     |
 |44 230 8         |     |
 |33 57 132        |     |
 |17 8 5           |     |
 |2                |     |
 |0 3 100 40 41 2 4|     |
 |2 4 0 200 57 1 3 |     |

****************************************************************************/


#include <iostream>

int main()
{
    return 0;
}

