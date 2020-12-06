#include <iostream>
#include "Graph.h"
#include "Vertex_map.h"
#include "Vertex.h"
#include "Edge.h"
#include "First_task.h"
#include "Graph_forms.h"
#include <string>
#include <iomanip>

using namespace std;


void vertexIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph,
                        MapVertex<string, Vertex<string, int> *> &mapVertex) {
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator vertexIterator(*graph);
    int key;
    while (true) {
        cout << "_____Меню итератора вершин______\n"
             << "1) Установка на начало         |\n"
             << "2) Установка на конец          |\n"
             << "3) Переход к следующему        |\n"
             << "4) Получить имя                |\n"
             << "5) Установить имя              |\n"
             << "6) Получить данные             |\n"
             << "7) Установить данные           |\n"
             << "8) Получить индекс             |\n"
             << "0) Выход                       |\n"
             << "-------------------------------\n"
             << "Ввод: ";
        cin >> key;
        switch (key) {
            case 1:
                cout << boolalpha << vertexIterator.toBegin() << endl;
                break;
            case 2:
                cout << boolalpha << vertexIterator.toEnd() << endl;
                break;
            case 3:
                cout << boolalpha << ++vertexIterator << endl;
                break;

            case 4:
                try {
                    if ((*vertexIterator)->hasName())
                        cout << "Имя: " << (*vertexIterator)->getName() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 5:
                try {
                    cout << "Введите имя: ";
                    string name;
                    cin >> name;
                    bool success;
                    if (!(*vertexIterator)->hasName())
                        success = mapVertex.addPair(name, (*vertexIterator));
                    else
                        success = mapVertex.replaceName((*vertexIterator)->getName(), name);

                    if (success) {
                        (*vertexIterator)->setName(name);
                        cout << boolalpha << true << endl;
                    } else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 6:
                try {
                    if ((*vertexIterator)->hasData())
                        cout << "Данные: " << (*vertexIterator)->getData() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 7: {
                cout << "Введите данные: ";
                int data;
                cin >> data;
                try {
                    (*vertexIterator)->setData(data);
                    cout << boolalpha << true << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }

            }
                break;
            case 8:
                try {
                    cout << (*vertexIterator)->index << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 0:
                return;
        }
    }

}

void edgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph) {
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::EdgeIterator edgeIterator(*graph);
    int key;
    while (true) {
        cout << "_____Меню итератора ребер______\n"
             << "1) Установка на начало         |\n"
             << "2) Установка на конец          |\n"
             << "3) Переход к следующему        |\n"
             << "4) Получить вес                |\n"
             << "5) Установить вес              |\n"
             << "6) Получить данные             |\n"
             << "7) Установить данные           |\n"
             << "8) Получить индекс             |\n"
             << "0) Выход                       |\n"
             << "-------------------------------\n"
             << "Ввод: ";
        cin >> key;
        switch (key) {
            case 0:
                return;

            case 1:
                cout << boolalpha << edgeIterator.toBegin() << endl;
                break;
            case 2:
                cout << boolalpha << edgeIterator.toEnd() << endl;
                break;
            case 3:
                cout << boolalpha << ++edgeIterator << endl;
                break;
            case 4:
                try {
                    if ((*edgeIterator)->hasWeight())
                        cout << "Вес: " << (*edgeIterator)->getWeight() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 5: {
                cout << "Введите вес: ";
                int weight;
                cin >> weight;
                try {
                    (*edgeIterator)->setWeight(weight);
                    cout << boolalpha << true << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
            }
                break;
            case 6:
                try {
                    if ((*edgeIterator)->hasData())
                        cout << "Данные: " << (*edgeIterator)->getData() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 7: {
                cout << "Введите данные: ";
                int data;
                cin >> data;
                try {
                    (*edgeIterator)->setData(data);
                    cout << boolalpha << true << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
            }
                break;
            case 8: {
                try {
                    cout << (*edgeIterator)->getVertex1()->index << " "
                         << (*edgeIterator)->getVertex2()->index << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
            }
                break;
            case 9:
                return;
        }
    }
}


void outputEdgeIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph) {
    int vertexIndex;
    while (true) {
        cout << "Введите вершину: ";
        cin >> vertexIndex;
        if (vertexIndex >= graph->getVertexCount() || graph->getVertexCount() < 0) continue;
        Vertex<string, int> *vertex;
        try {
            vertex = graph->getVertex(vertexIndex);
        }
        catch (runtime_error error) {
            cout << error.what() << endl;
            continue;
        }
        Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::OutputEdgeIterator outputEdgeIterator(
                *graph,
                *vertex);
        int key;
        bool work = true;
        while (work) {
            cout << "_____Меню итератора исходящих ребер______\n"
                 << "1) Установка на начало                   |\n"
                 << "2) Установка на конец                    |\n"
                 << "3) Переход к следующему                  |\n"
                 << "4) Получить вес                          |\n"
                 << "5) Установить вес                        |\n"
                 << "6) Получить данные                       |\n"
                 << "7) Установить данные                     |\n"
                 << "8) Получить индекс                       |\n"
                 << "9) Выбрать другую вершину                |\n"
                 << "0) Выход                                 |\n"
                 << "-----------------------------------------\n"
                 << "Ввод: ";
            cin >> key;
            switch (key) {
                case 1:
                    cout << boolalpha << outputEdgeIterator.toBegin() << endl;
                    break;
                case 2:
                    cout << boolalpha << outputEdgeIterator.toEnd() << endl;
                    break;
                case 3:
                    cout << boolalpha << ++outputEdgeIterator << endl;
                    break;
                case 4:
                    try {
                        if ((*outputEdgeIterator)->hasWeight())
                            cout << "Вес: " << (*outputEdgeIterator)->getWeight() << endl;
                        else
                            cout << boolalpha << false << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }

                    break;
                case 5: {
                    cout << "Введите вес: ";
                    int weight;
                    cin >> weight;
                    try {
                        (*outputEdgeIterator)->setWeight(weight);
                        cout << boolalpha << true << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                }
                    break;
                case 6:
                    try {
                        if ((*outputEdgeIterator)->hasData())
                            cout << "Данные: " << (*outputEdgeIterator)->getData() << endl;
                        else
                            cout << boolalpha << false << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                    break;
                case 7:
                    cout << "Введите данные: ";
                    int data;
                    cin >> data;
                    try {
                        (*outputEdgeIterator)->setData(data);
                        cout << boolalpha << true << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                    break;
                case 8: {
                    try {
                        cout << endl << (*outputEdgeIterator)->getVertex1()->index << " "
                             << (*outputEdgeIterator)->getVertex2()->index
                             << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                }
                    break;
                case 9 :
                    work = false;
                    break;
                case 0:
                    return;
            }
        }
    }
}

void firstTaskMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph) {

    FirstTask<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> firstTask(graph);

    int key;
    while (true) {
        cout << "__Меню первого задания__\n"
             << "1) Рестарт              |\n"
             << "2) Результат            |\n"
             << "0) Выход                |\n"
             << "------------------------\n"
             << "Ввод: ";
        cin >> key;
        switch (key) {
            case 1:
                firstTask.restart();
                break;
            case 2:
                firstTask.result();
                break;
            case 0:
                return;
        }
    }
}
//
//void taskTwoMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph) {
//    cout << "введите d";
//    int d;
//    cin >> d;
//    //taskOneMenu edge iterator
//    cout << "\nменю второго задания"
//         << "\n1 restart"
//         << "\n2 новое d"
//         << "\n3 result"
//         << "\n4 выход"
//         << "\n";
//
//    TaskTwo <Vertex<string, int>, Edge<Vertex<string, int>, int, int>> taskTwo(graph, d);
//
//    int key;
//    while (true) {
//        cin >> key;
//        switch (key) {
//            case 1:
//                taskTwo.restart();
//                break;
//            case 2: {
//                cout << "\nвведите новое d" << "\n";
//                cin >> d;
//                taskTwo.setD(d);
//            }
//
//                break;
//            case 3: {
//                vector<vector<bool>> result = taskTwo.getResult();
//
//                //выводим заголовок
//                cout << setw(6) << "";
//                for (int i = 0; i < graph->getVertexCount(); i++) {
//                    if (graph->getVertex(i)->isNameSet() == true)
//                        cout << setw(6) << graph->getVertex(i)->getName();
//                    else
//                        cout << setw(6) << "ind " << i;
//                }
//                cout << "\n\n\n";
//
//                for (int i = 0; i < graph->getVertexCount(); i++) {
//                    if (graph->getVertex(i)->isNameSet() == true)
//                        cout << setw(6) << graph->getVertex(i)->getName();
//                    else
//                        cout << setw(6) << "ind " << i;
//
//                    for (int j = 0; j < graph->getVertexCount(); j++) {
//                        if (result[i][j]) {
//                            if (graph->getEdge(i, j)->isWeightSet())
//                                cout << setw(6) << graph->getEdge(i, j)->getWeight();
//                            else
//                                cout << setw(6) << "+ ";
//                        } else
//                            cout << setw(6) << "- ";
//                    }
//                    cout << "\n\n\n";
//                }
//
//            }
//                break;
//            case 4:
//                return;
//
//        }
//    }
//}


int main() {
    srand(time(0));
    auto *graph =
            new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(5, 12, true, true);
    MapVertex<string, Vertex<string, int> *> mapVertex;
    setlocale(LC_ALL, "rus");
    bool exit = true;
    int key, index1, index2;
    string name1, name2;
    while (exit) {
        cout << "_______________Главное меню________________\n"
             << "1)  Вывести граф в виде матрицы           |\n"
             << "2)  Вывести граф в виде списков           |\n"
             << "3)  Задать случайные веса ребрам          |\n"
             << "4)  Получить число вершин                 |\n"
             << "5)  Получить число ребер                  |\n"
             << "6)  Получить тип графа                    |\n"
             << "7)  Получить форму представления графа    |\n"
             << "8)  Получить коэффицент насыщености       |\n"
             << "9)  Преобразовать к M-графу               |\n"
             << "10) Преобразовать к L-графу               |\n"
             << "11) Добавить вершину                      |\n"
             << "12) Удалить вершину по имени              |\n"
             << "13) Удалить вершину по индексу            |\n"
             << "14) Добавить ребро по именам              |\n"
             << "15) Добавить ребро по индексам            |\n"
             << "16) Удалить ребро по именамм              |\n"
             << "17) Удалить ребро по индексам             |\n"
             << "18) Меню итератора вершинм                |\n"
             << "19) Меню итератора ребер                  |\n"
             << "20) Меню итератора исходящих              |\n"
             << "21) Меню первого задания                  |\n"
             << "22) Меню второго задания                  |\n"
             << "0)  Выход                                 |\n"
             << "------------------------------------------\n"
             << "Ввод: ";
        cin >> key;
        switch (key) {
            case 0:
                exit = false;
                break;

            case 1:
                graph->printGraph();
                break;

            case 2:
                graph->printGraph(false);
                break;

            case 3:
                int weightMax;
                int weightMin;
                cout << "Введите диапазон весов\n"
                        "Минимум: ";
                cin >> weightMin;
                cout << "Максимум: ";
                cin >> weightMax;

                for (int i = 0; i < graph->getVertexCount(); i++) {
                    for (int j = 0; j < graph->getVertexCount(); j++) {
                        if (graph->hasEdge(i, j)) {
                            int weight = rand() % (weightMax - weightMin) + weightMin;
                            graph->getEdge(i, j)->setWeight(weight);
                        }
                    }
                }
                break;

            case 4:
                cout << "Число вершин: " << graph->getVertexCount() << endl;
                break;

            case 5:
                cout << "Число ребер: " << graph->getEdgeCount() << endl;
                break;

            case 6:
                if (graph->isDirected())
                    cout << "Ориентированный граф\n";
                else
                    cout << "Неориентированный граф\n";
                break;

            case 7:
                if (graph->isDense())
                    cout << "Форма: матрица\n";
                else
                    cout << "Форма: список\n";
                break;

            case 8:
                cout << graph->getRatio() << endl;
                break;

            case 9:
                graph->toDenseGraph();
                break;

            case 10:
                graph->toSparseGraph();
                break;

            case 11:
                try {
                    graph->insertVertex();
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 12:
                try {
                    cout << "Введите имя: ";
                    string name;
                    cin >> name;
                    int index = mapVertex.getData(name)->index;
                    mapVertex.delPair(name);
                    cout << boolalpha << graph->deleteVertex(index) << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 13:
                cout << "Введите индекс: ";
                int index;
                cin >> index;
                try {
                    if (graph->getVertex(index)->hasName()) {
                        mapVertex.delPair(graph->getVertex(index)->getName());
                    }
                    cout << boolalpha << graph->deleteVertex(index) << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 14:
                try {
                    cout << "Введите имена вершин\n";
                    cout << "Имя 1: ";
                    cin >> name1;
                    cout << "Имя 2: ";
                    cin >> name2;
                    index1 = mapVertex.getData(name1)->index;
                    index2 = mapVertex.getData(name2)->index;

                    graph->insertEdge(index1, index2);
                    cout << boolalpha << true << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 15:
                cout << "Введите индексы вершин\n";
                cout << "Индекс 1: ";
                cin >> index1;
                cout << "Индекс 2: ";
                cin >> index2;
                try {
                    graph->insertEdge(index1, index2);
                    cout << boolalpha << true << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 16:
                try {
                    cout << "Введите имена вершин\n";
                    cout << "Имя 1: ";
                    cin >> name1;
                    cout << "Имя 2: ";
                    cin >> name2;
                    index1 = mapVertex.getData(name1)->index;
                    index2 = mapVertex.getData(name2)->index;

                    cout << boolalpha << graph->deleteEdge(index1, index2) << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;

            case 17:
                cout << "Введите индексы вершин\n";
                cout << "Индекс 1: ";
                cin >> index1;
                cout << "Индекс 2: ";
                cin >> index2;
                cout << boolalpha << graph->deleteEdge(index1, index2) << endl;
                break;

            case 18:
                vertexIteratorMenu(graph, mapVertex);
                break;

            case 19:
                edgeIteratorMenu(graph);
                break;

            case 20:
                outputEdgeIteratorMenu(graph);
                break;

            case 21:
                firstTaskMenu(graph);
                break;
//
//            case 22:
//                taskTwoMenu(graph);
//                break;


        }
    }
    return 0;
}

