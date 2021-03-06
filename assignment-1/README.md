# Задание №1 по курсу "Алгоритмы и стркутуры данных". Семестр 2.

Сдать задание нужно до 11 марта.

Ссылка на контест: https://contest.yandex.ru/contest/3970/ .

-----------------------------------------------------------

## Задача № 1 «Представление графа».(4 балла)

Дан базовый интерфейс для представления графа:

    struct IGraph {
        virtual ~IGraph() {}

        // Добавление ребра от from к to.
        virtual void AddEdge(int from, int to) = 0;

        virtual int VerticesCount() const  = 0;

        virtual void GetNextVertices(int vertex, std::vector<int>& vertices) const = 0;
        virtual void GetPrevVertices(int vertex, std::vector<int>& vertices) const = 0;
    };


Необходимо написать несколько реализаций интерфейса:
- CListGraph, хранящий граф в виде массива списков смежности,
- CMatrixGraph, хранящий граф в виде матрицы смежности,
- CSetGraph, хранящий граф в виде массива хэш-таблиц,
- CArcGraph, хранящий граф в виде одного массива пар {from, to}.

Также необходимо реализовать конструктор, принимающий const IGraph*. Такой конструктор должен скопировать переданный граф в создаваемый объект.
Для каждого класса создавайте отдельные h и cpp файлы.
Число вершин графа задается в конструкторе каждой реализации.

-----------------------------------------------------------

## Задача №2 Цикл минимальной длины (2 балла)

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите цикл минимальной длины. Требуемая сложность O(VE), + 1 балл за O(V + E).

Ввод: В первой строке вводятся два натуральных числа N и M, не превосходящих 10000. Далее идут M строк по 2 числа (от 0 до N-1) - индексы вершин между которыми есть ребро.
Вывод: 1 целое число равное длине минимального цикла. Если цикла нет, то вывести -1.


  in  | out
 -----|-----
  6 6 |  4
  0 1 |
  0 2 |
  2 3 |
  2 4 |
  3 5 |
  4 5 |


-----------------------------------------------------------

## Задача № 3 Количество различных путей (2 балла)

Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).

Ввод: v:кол-во вершин(макс. 50000), n:кол-во ребер(макс. 200000), n пар реберных вершин, пара вершин v, w для запроса.
Вывод: количество кратчайших путей от v к w

 | in  | out |
 |-----|-----|
 |4    |  2  |
 |5    |     |
 |0 1  |     |
 |0 2  |     |
 |1 2  |     |
 |1 3  |     |
 |2 3  |     |
 |     |     |
 |0 3  |     |


-----------------------------------------------------------

## Задача №4 А есть ли сток? (2 балла)

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

 |   in   | out |
 |--------|-----|
 |4       | YES |
 |0 1 0 1 |     |
 |0 0 0 0 |     |
 |1 1 0 0 |     |
 |1 1 0 0 |     |

 |   in   | out |
 |--------|-----|
 |4       | NO  |
 |0 1 0 1 |     |
 |0 0 0 0 |     |
 |1 0 0 0 |     |
 |1 1 0 0 |     |


-----------------------------------------------------------

## Задача № 5 Зал круглых столов (5 баллов)

Единственный способ попасть в Зал Круглых Столов – пройти через Колонный Коридор.
Стены Коридора изображаются на карте прямыми линиями, которые параллельны осиOY системы координат.
Вход в Коридор находится снизу, а выход из Коридора в Зал – сверху.
В Коридоре есть цилиндрические (на карте круглые) Колонны одинакового радиуса R.
Разработайте алгоритм, который по информации о размерах Коридора, и размещения Колонн определяет диаметр наибольшего из Круглых Столов, который можно пронести через такой Коридор, сохраняя поверхность Стола горизонтальной.

![Tables image](task5_tables.png)

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

 |      in        |    out    |
 |----------------|-----------|
 |211612 250570   | 29486.000 |
 |136             |           |
 |186             |           |
 |404204 255391   |           |
 |-80571 333985   |           |
 |962298 567403   |           |
 |-67165 -705435  |           |
 |-859260 94426   |           |
 |-161761 -607280 |           |
 |-539481 768804  |           |
 |-835303 -781894 |           |
 |-56991 454609   |           |
 |-335757 834039  |           |
 |746 852626      |           |
 |-327464 838553  |           |
 |178460 731771   |           |
 |397212 -455091  |           |
 |450929 31418    |           |
 |54126 762695    |           |
 |-495447 -169107 |           |
 |-11413 214728   |           |
 |-615156 77306   |           |
 |380495 745920   |           |
 |-17403 -791924  |           |
 |470445 -583066  |           |
 |145307 -431098  |           |
 |-530942 55693   |           |
 |729660 73006    |           |
 |-397778 -147214 |           |
 |256116 -254773  |           |
 |241234 -292994  |           |
 |-555161 -708839 |           |
 |-278974 573808  |           |
 |375152 53250    |           |
 |-695388 -560348 |           |
 |177801 491673   |           |
 |-275575 -952358 |           |
 |-733791 655879  |           |
 |931891 -718674  |           |
 |172609 63880    |           |
 |944788 -835992  |           |
 |-607322 -278077 |           |
 |-218901 -158900 |           |
 |869586 972873   |           |
 |357582 -486017  |           |
 |-388280 486969  |           |
 |522059 48444    |           |
 |778154 -907405  |           |
 |893247 -903464  |           |
 |-301258 127111  |           |
 |354600 -680656  |           |
 |518681 277329   |           |
 |300778 -894925  |           |
 |624502 -550100  |           |
 |-587929 791248  |           |
 |91141 -353933   |           |
 |-542704 948758  |           |
 |-931103 -742472 |           |
 |945556 644424   |           |
 |705832 87299    |           |
 |264978 -661700  |           |
 |-332546 224675  |           |
 |625157 484323   |           |
 |68963 587209    |           |
 |-488345 -610815 |           |
 |-599658 480335  |           |
 |-874719 189930  |           |
 |-727180 -147844 |           |
 |387438 610651   |           |
 |212874 -487230  |           |
 |989508 783405   |           |
 |-146906 667946  |           |
 |-866358 854500  |           |
 |326703 767370   |           |
 |931779 -849894  |           |
 |156885 29415    |           |
 |168825 101788   |           |
 |-629855 -858582 |           |
 |-603062 769245  |           |
 |891717 340191   |           |
 |-239897 106803  |           |
 |-633897 -680049 |           |
 |-618209 -524342 |           |
 |690134 373352   |           |
 |44915 346559    |           |
 |316793 -997502  |           |
 |669233 803768   |           |
 |-849776 3584    |           |
 |241796 870849   |           |
 |-997533 645500  |           |
 |-224621 43167   |           |
 |791709 -937634  |           |
 |714000 103006   |           |
 |758133 -840830  |           |
 |-502224 -509190 |           |
 |545318 -500991  |           |
 |942923 307952   |           |
 |79012 -882151   |           |
 |-982558 423246  |           |
 |119001 -753245  |           |
 |930741 -105385  |           |
 |-432313 551422  |           |
 |426125 110678   |           |
 |-341587 174600  |           |
 |-967467 -574032 |           |
 |455903 451233   |           |
 |492744 39028    |           |
 |453058 232481   |           |
 |248324 654012   |           |
 |-846270 629128  |           |
 |286615 57188    |           |
 |61435 -504147   |           |
 |-989923 490483  |           |
 |448591 99548    |           |
 |-245902 746050  |           |
 |-541400 184684  |           |
 |-143102 -688409 |           |
 |-836858 594600  |           |
 |-633975 -639632 |           |
 |761339 839044   |           |
 |288696 154464   |           |
 |-929827 230976  |           |
 |320786 -251576  |           |
 |903848 391738   |           |
 |-784897 -808214 |           |
 |-709384 873971  |           |
 |15357 -485139   |           |
 |-350786 61100   |           |
 |53387 955720    |           |
 |-865103 529268  |           |
 |-732060 191639  |           |
 |-91728 -28047   |           |
 |201640 213604   |           |
 |27019 206494    |           |
 |24903 547355    |           |
 |85180 -927461   |           |
 |-590015 42528   |           |
 |581611 104904   |           |
 |812253 -404787  |           |
 |631596 -236914  |           |
 |-423882 810672  |           |
 |740744 225236   |           |
 |706445 -940304  |           |
 |329019 65948    |           |
 |-609997 -288818 |           |
 |752375 -892540  |           |
 |-725552 -425516 |           |
 |-567959 822100  |           |
 |650788 -562364  |           |
 |877945 974914   |           |
 |-411755 61365   |           |
 |-851594 -531296 |           |
 |264131 -285925  |           |
 |136173 -661583  |           |
 |830103 919137   |           |
 |-754767 -502653 |           |
 |324080 -296836  |           |
 |-506191 -245292 |           |
 |701845 -220439  |           |
 |902852 -112588  |           |
 |612192 530444   |           |
 |157089 -750681  |           |
 |915577 239649   |           |
 |-943836 465372  |           |
 |-210560 22236   |           |
 |-730945 581346  |           |
 |-179016 828892  |           |
 |-923551 450561  |           |
 |-433429 -815877 |           |
 |-497902 453343  |           |
 |-248812 365987  |           |
 |-627965 -393292 |           |
 |-195462 -711449 |           |
 |1547 173098     |           |
 |-842725 381798  |           |
 |-214192 692666  |           |
 |806641 217997   |           |
 |929747 372433   |           |
 |-276271 686578  |           |
 |-952277 -177311 |           |
 |-297419 646963  |           |
 |385293 804937   |           |
 |-311821 -887005 |           |
 |-568756 635414  |           |
 |555596 -27804   |           |
 |678043 -788448  |           |
 |-825596 -385923 |           |
 |-370715 167035  |           |
 |11245 701453    |           |

 |      in        |    out    |
 |----------------|-----------|
 |51324 120819    | 39075.000 |
 |99              |           |
 |96              |           |
 |682351 229192   |           |
 |660584 -987923  |           |
 |-245875 -153164 |           |
 |998370 -402896  |           |
 |-78408 -907113  |           |
 |760974 -877607  |           |
 |-971942 -544458 |           |
 |747147 423698   |           |
 |684278 884962   |           |
 |774919 -8546    |           |
 |325310 626851   |           |
 |-885059 913200  |           |
 |711542 -552560  |           |
 |-531524 602213  |           |
 |-638569 -510125 |           |
 |-18993 118352   |           |
 |-854269 -44631  |           |
 |-96498 89455    |           |
 |510137 -259667  |           |
 |337794 144929   |           |
 |-753643 875070  |           |
 |843163 245769   |           |
 |-399648 -742603 |           |
 |939126 351312   |           |
 |-721364 332945  |           |
 |-493736 40349   |           |
 |-673321 -79237  |           |
 |185481 -344752  |           |
 |810701 -515765  |           |
 |311609 584214   |           |
 |-825842 787519  |           |
 |885375 -676538  |           |
 |726660 -12263   |           |
 |780050 902580   |           |
 |-565836 -43198  |           |
 |987247 159183   |           |
 |-67821 -675714  |           |
 |253416 922812   |           |
 |-620556 195677  |           |
 |438379 -606602  |           |
 |59183 -171372   |           |
 |-809120 -378907 |           |
 |191337 -347240  |           |
 |-351488 646637  |           |
 |-605054 -961820 |           |
 |-695015 707758  |           |
 |-786837 -446787 |           |
 |142370 -297900  |           |
 |782344 -725765  |           |
 |234724 -841760  |           |
 |287522 199121   |           |
 |352639 850007   |           |
 |-668403 -234516 |           |
 |500149 -879487  |           |
 |398167 -434140  |           |
 |-252806 -331474 |           |
 |-440424 -122850 |           |
 |-253792 580219  |           |
 |125185 -721266  |           |
 |-259287 -853079 |           |
 |-566216 -558155 |           |
 |-487314 30509   |           |
 |-738635 637919  |           |
 |-309687 -263634 |           |
 |799816 69742    |           |
 |-682333 -201528 |           |
 |-135057 -582233 |           |
 |-275081 611686  |           |
 |-871589 6053    |           |
 |350375 874296   |           |
 |-912817 -383769 |           |
 |767645 825424   |           |
 |-462941 594039  |           |
 |583692 306160   |           |
 |966005 613218   |           |
 |-271810 880681  |           |
 |-653320 -665046 |           |
 |409323 962019   |           |
 |-508757 -691762 |           |
 |648541 125519   |           |
 |-461286 963569  |           |
 |866455 -137055  |           |
 |-539103 853750  |           |
 |-998322 -120024 |           |
 |60893 909157    |           |
 |450262 -488970  |           |
 |-516991 -788991 |           |
 |219366 -748377  |           |
 |90498 84412     |           |
 |586749 8400     |           |
 |172352 -26925   |           |
 |774605 -326151  |           |
 |580010 -322664  |           |
 |249893 -486625  |           |
 |752424 918139   |           |
 |357288 -424286  |           |


-----------------------------------------------------------

## Задача № 6 Дополнение до сильносвязного (5 баллов)

Дан ориентированный граф. Определите, какое минимальное количество ребер необходимо добавить, чтобы граф стал сильносвязным. В графе возможны петли.

*Формат ввода*
В первой строке указывается число вершин графа V, во второй – число ребер E, в последующих – E пар вершин, задающих ребра.

*Формат вывода*
Минимальное число ребер k.


 |  in  | out |
 |------|-----|
 | 4    | 1   |
 | 4    |     |
 | 1 2  |     |
 | 2 3  |     |
 | 3 1  |     |
 | 3 4  |     |

 |  in  | out |
 |------|-----|
 | 5    | 2   |
 | 4    |     |
 | 1 2  |     |
 | 3 4  |     |
 | 4 5  |     |
 | 5 3  |     |


