#ifndef ADS_RGR_GRAPH_H
#define ADS_RGR_GRAPH_H

#include <iostream>
#include "Graph_forms.h"
#include <iomanip>

using namespace std;

//АТД простой граф
template<class Vertex, class Edge>
class Graph {
    vector<Vertex *> vertexVector;//Вектор вставленных
    GraphForm<Edge> *data;       //Данные графа
    bool directed;                //Ориентация графа
    bool dense;                   //М-граф
    int edgeCounter;              //Число рёбер

    //обновление индексов вершин
    void refreshIndex(int startIndex) {
        if (startIndex < 0 || startIndex >= vertexVector.size())
            return;

        for (int i = startIndex; i < vertexVector.size(); i++)
            vertexVector[i]->index = i;
    }


    //Получение индекса вершины по дескриптору
    int getIndex(Vertex *v) {
        int i;
        for (i = 0; i < vertexVector.size(); ++i) {
            if (vertexVector[i] == v)
                break;
        }
        if (i == vertexVector.size())
            throw runtime_error("EXCEPTION!");
        return i;
    }


public:
    //Создать пустой L-граф с нулевым числом вершин и рёбер
    Graph() {
        data = new GraphListForm<Edge>(false);
        directed = false;
        dense = false;
        edgeCounter = 0;
    }

    //Создать граф с V вершинами, без ребер, типа D, формы представления F
    Graph(int vertexCount, bool directed, bool dense) {
        if (dense)
            data = new GraphMatrixForm<Edge>(directed);
        else
            data = new GraphListForm<Edge>(directed);
        for (int i = 0; i < vertexCount; ++i) {
            auto *v = new Vertex();
            vertexVector.push_back(v);
            data->insertVertex(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;

        refreshIndex(0);
    }


    //Создать граф с V вершинами, с E случайными ребрами, типа D , формы F
    Graph(int vertexCount, int edgeCount, bool directed, bool dense) {
        if (dense)
            data = new GraphMatrixForm<Edge>(directed);
        else
            data = new GraphListForm<Edge>(directed);

        for (int i = 0; i < vertexCount; ++i) {
            auto *v = new Vertex();
            vertexVector.push_back(v);
            data->insertVertex(i);
        }
        this->directed = directed;
        this->dense = dense;
        edgeCounter = 0;

        //Вставляем рёбра
        if (edgeCount <= 0) return;
        //Корректируем число рёбер, чтобы не превышало максимумы
        if (directed) {
            if (edgeCount > vertexCount * (vertexCount - 1))
                edgeCount = vertexCount * (vertexCount - 1);

        } else {
            if (edgeCount > (vertexCount * (vertexCount - 1)) / 2)
                edgeCount = (vertexCount * (vertexCount - 1)) / 2;
        }
        //Вставляем
        int v1, v2;

        refreshIndex(0);

        srand(time(0));
        while (edgeCounter < edgeCount) {
            v1 = rand() % vertexCount;
            v2 = rand() % vertexCount;
            if (v1 == v2)
                continue;
            if (data->hasEdge(v1, v2))
                continue;
            Edge *t = new Edge(vertexVector[v1], vertexVector[v2]);
            data->insertEdge(v1, v2, t);
            if (!directed)
                data->insertEdge(v2, v1, t);
            ++edgeCounter;
        }
    }


    //конструктор копирования
    Graph(const Graph<Vertex, Edge> &G) {
        delete data;
        if (G.Dense())
            data = new GraphMatrixForm<Edge>(*(G.data));
        else
            data = new GraphListForm<Edge>(*(G.data));
        directed = G.directed;
        dense = G.dense;
    }

    //деструктор
    ~Graph() {
        while (vertexVector.size() != 0)
            deleteVertex(vertexVector.size() - 1);
        delete data;
    }

    //Информация о графе
    //Число вершин, рёбер, насыщенность
    int getVertexCount() { return vertexVector.size(); }

    int getEdgeCount() { return edgeCounter; }

    double getRatio() {
        int max = vertexVector.size() * (vertexVector.size() - 1);
        if (!directed)
            max /= 2;
        return (double) edgeCounter / (double) max;
    }

    //Тип графа
    bool isDirected() { return directed; }

    bool isDense() { return dense; }

    //Преобразования
    void toDenseGraph() {
        //Создаём структуру хранения М-графа
        GraphForm<Edge> *newData = new GraphMatrixForm<Edge>(directed);

        //Создаём вершины
        for (int i = 0; i < vertexVector.size(); ++i)
            newData->insertVertex(i);

        //Переносим рёбра
        for (int i = 0; i < vertexVector.size(); ++i)
            for (int j = 0; j < vertexVector.size(); ++j)
                if (data->hasEdge(i, j))
                    newData->insertEdge(i, j, data->getEdge(i, j));
        delete data;
        data = newData;
        dense = true;
    }

    void toSparseGraph() {
        //Создаём структуру хранения L-графа
        GraphForm<Edge> *newData = new GraphListForm<Edge>(directed);

        //Создаём вершины
        for (int i = 0; i < vertexVector.size(); ++i)
            newData->insertVertex(i);

        //Переносим рёбра
        for (int i = 0; i < vertexVector.size(); ++i)
            for (int j = 0; j < vertexVector.size(); ++j)
                if (data->hasEdge(i, j))
                    newData->insertEdge(i, j, data->getEdge(i, j));
        delete data;
        data = newData;
        dense = false;
    }


    //Данные
    //Вершины
    Vertex *insertVertex() {
        auto *v = new Vertex;
        if (!data->insertVertex(vertexVector.size()))
            throw runtime_error("EXCEPTION!");
        vertexVector.push_back(v);
        refreshIndex(vertexVector.size() - 1);
        return v;
    }

    Vertex *insertVertex(int index) {
        auto *v = new Vertex;
        if (data->insertVertex(index) == false)
            throw runtime_error("EXCEPTION!");
        vertexVector.insert(vertexVector.begin() + index, v);
        refreshIndex(index);
        return v;
    }

    bool deleteVertex(Vertex *v) {
        int index = getIndex(v);
        edgeCounter -= data->deleteEdgesFromVertex(index);
        if (data->deleteVertex(index)) {
            vertexVector.erase(vertexVector.begin() + index);
            refreshIndex(index);
            return true;
        }
        return false;
    }

    bool deleteVertex(int index) {
        if (index < 0 || index >= vertexVector.size())
            return false;
        edgeCounter -= data->deleteEdgesFromVertex(index);
        if (data->deleteVertex(index)) {
            vertexVector.erase(vertexVector.begin() + index);
            refreshIndex(index);
            return true;
        }
        return false;
    }

    Vertex *getVertex(int index) {
        if (index < 0 || index >= vertexVector.size())
            throw runtime_error("EXCEPTION!");
        return vertexVector[index];
    }

    //Рёбра
    Edge *insertEdge(Vertex *v1, Vertex *v2) {
        Edge *e = new Edge(v1, v2);
        bool success = data->insertEdge(getIndex(v1), getIndex(v2), e);
        if (!directed)
            data->insertEdge(getIndex(v2), getIndex(v1), e);
        if (success) {
            ++edgeCounter;
            return e;
        } else {
            delete e;
            throw runtime_error("EXCEPTION!");
        }

    }

    Edge *insertEdge(int index1, int index2) {
        if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
            throw runtime_error("EXCEPTION!");
        Edge *e = new Edge(vertexVector[index1], vertexVector[index2]);
        bool success = data->insertEdge(index1, index2, e);
        if (!directed)
            data->insertEdge(index2, index1, e);
        if (success) {
            ++edgeCounter;
            return e;
        } else {
            delete e;
            throw runtime_error("EXCEPTION!");
        }

    }


    bool deleteEdge(Vertex *v1, Vertex *v2) {
        if (data->deleteEdge(getIndex(v1), getIndex(v2))) {
            --edgeCounter;
            if (!directed)
                data->deleteEdge(getIndex(v2), getIndex(v1));
            return true;
        } else
            return false;
    }

    bool deleteEdge(int index1, int index2) {
        if (index1 < 0 || index2 < 0 || index1 >= vertexVector.size() || index2 >= vertexVector.size())
            return false;
        if (data->deleteEdge(index1, index2)) {
            --edgeCounter;
            if (!directed)
                data->deleteEdge(index2, index1);
            return true;
        } else
            return false;
    }

    bool hasEdge(Vertex *v1, Vertex *v2) {
        int ind1, ind2;
        try { ind1 = getIndex(v1); } catch (runtime_error error) {
            cout << error.what() << endl;
            return false;
        }
        try { ind2 = getIndex(v2); } catch (runtime_error error) {
            cout << error.what() << endl;
            return false;
        }
        return data->hasEdge(getIndex(v1), getIndex(v2));
    }

    bool hasEdge(int v1, int v2) {
        if (v1 < 0 || v1 >= vertexVector.size()) return false;
        if (v2 < 0 || v2 >= vertexVector.size()) return false;
        return data->hasEdge(v1, v2);
    }

    Edge *getEdge(Vertex *v1, Vertex *v2) {
        return data->getEdge(getIndex(v1), getIndex(v2));
    }

    Edge *getEdge(int v1, int v2) {
        return data->getEdge(v1, v2);
    }

    void printGraph(bool isMatrix = true) {
        if (isMatrix) {
            cout << setw(6) << "";
            for (int i = 0; i < getVertexCount(); i++) {

                cout << setw(6) << "(i" << i;
                if (getVertex(i)->hasName())
                    cout << "," << getVertex(i)->getName();
                cout << ")";

            }
            cout << "\n\n\n";

            for (int i = 0; i < getVertexCount(); i++) {
                cout << setw(6) << "(i" << i;
                if (getVertex(i)->hasName())
                    cout << "," << getVertex(i)->getName();
                cout << ")";

                for (int j = 0; j < getVertexCount(); j++) {
                    if (hasEdge(i, j)) {
                        if (getEdge(i, j)->hasWeight())
                            cout << setw(7) << getEdge(i, j)->getWeight();
                        else
                            cout << setw(7) << "+ ";

                    } else
                        cout << setw(7) << "- ";
                }
                cout << "\n\n\n";
            }
        } else {
            for (int i = 0; i < getVertexCount(); i++) {
                cout << setw(10) << "(i" << i;
                if (getVertex(i)->hasName())
                    cout << "," << getVertex(i)->getName();
                cout << ")   ";

                OutputEdgeIterator
                        outputEdgeIterator(*this, *(getVertex(i)));

                outputEdgeIterator.toBegin();
                while (!outputEdgeIterator.onEnd()) {
                    int index = 0;
                    if ((*outputEdgeIterator)->getVertex1()->index != i)
                        index = (*outputEdgeIterator)->getVertex1()->index;
                    else
                        index = (*outputEdgeIterator)->getVertex2()->index;

                    cout << setw(6) << "->(";
                    cout << "i" << getVertex(index)->index;
                    if (getVertex(index)->hasName())
                        cout << "," << getVertex(index)->getName();
                    if ((*outputEdgeIterator)->hasWeight())
                        cout << "|" << (*outputEdgeIterator)->getWeight();

                    cout << ") ";

                    ++outputEdgeIterator;
                }
                cout << "\n\n\n";
            }
        }
    }


    //Итератор вершин
    class VertexIterator {
        Graph<Vertex, Edge> *graph;
        bool end;
        int current;
    public:
        VertexIterator(Graph<Vertex, Edge> &g) {
            graph = &g;
            toBegin();
        }

        //возвращает итератор, установленный на первую вершину графа
        bool toBegin() {
            if (graph->vertexVector.size() == 0) {
                end = true;
                return true;
            }
            current = 0;
            end = false;
            return true;
        }

        //Переход к следующей позиции
        bool operator++() {
            if (end)
                return false;
            ++current;
            if (graph->vertexVector.size() == current) {
                end = true;
                return false;
            }
            return true;
        }

        bool operator++(int) {
            if (end)
                return false;
            ++current;
            if (graph->vertexVector.size() == current) {
                end = true;
                return false;
            }
            return true;
        }


        //Установить итератор вершин на конечную вершину
        bool toEnd() {
            current = graph->vertexVector.size() - 1;
            end = true;
            return true;
        }

        //Проверка на выход
        bool onEnd() {
            return end;
        }

        //Получение вершины
        Vertex *operator*() {
            if (current >= graph->vertexVector.size() || current == -1)
                throw runtime_error("EXCEPTION!");
            return graph->vertexVector[current];
        }

    };

    //Итератор рёбер
    class EdgeIterator {
        Graph<Vertex, Edge> *graph; //Обрабатываемый граф
        typename GraphMatrixForm<Edge>::EdgeIterator *matrixIter;
        typename GraphListForm<Edge>::EdgeIterator *listIter;
        bool isMatrix;
    public:
        string str1, str2, str3, str4;
        bool end;

        EdgeIterator(Graph<Vertex, Edge> &g) {
            graph = &g;
            if (graph->isDense()) {
                matrixIter = new typename GraphMatrixForm<Edge>::EdgeIterator(static_cast<GraphMatrixForm<Edge> *>(g.data));
                isMatrix = true;
            } else {
                listIter = new typename GraphListForm<Edge>::EdgeIterator(static_cast<GraphListForm<Edge> *>(g.data));
                isMatrix = false;
            }
            toBegin();
        }

        //Установка в начало
        bool toBegin() {
            if (isMatrix)
                return
                        matrixIter->toBegin();
            else
                return listIter->toBegin();
        }

        //Сдвиг на следующий элемент
        bool operator++() {
            if (isMatrix)
                return matrixIter->next();
            else
                return listIter->next();
        }

        bool operator++(int) {
            if (isMatrix)
                return matrixIter->next();
            else
                return listIter->next();
        }

        //Проверка на выход
        bool onEnd() {
            if (isMatrix)
                return matrixIter->onEnd();
            else
                return listIter->onEnd();
        }

        //Установить итератор рёбер на конечное ребро
        bool toEnd() {
            if (isMatrix)
                return matrixIter->toEnd();
            else
                return listIter->toEnd();
        }

        //Получение ребра
        Edge *operator*() {
            if (onEnd())
                throw runtime_error("EXCEPTION!");
            if (isMatrix)
                return matrixIter->getEdge();
            else
                return listIter->getEdge();
        }

        //Прочитать вершины ребра и вес по текущей позиции итератора
        string read_edge() {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *) {
                throw runtime_error("EXCEPTION!");
            }
            Vertex *_v1, *_v2;
            _v1 = e->getVertex1();
            _v2 = e->getVertex2();
            if (_v1->nameSet == false)
                str1 = "#data not available";
            else
                str1 = _v1->getName();
            if (_v2->nameSet == false)
                str2 = "#data not available";
            else
                str2 = _v2->getName();
            if (e->isWeightSet() == false)
                str3 = "#data not available";
            else
                str3 = i_to_s(e->getWeight());
            str4 = "Исходящая вершина: " + str1 + ". Входящая вершина: " + str2 + ". Вес ребра: " + str3;
            return str4;
        }

        //Прочитать данные ребра по текущей позиции итератора
        int read_data_edge() {
            Edge *f;
            try {
                f = operator*();
            }
            catch (char *e) {
                throw "Exeption#";
            }
            if (f->isDataSet())
                return f->getData();
            else
                throw "#data not available";
        };

        bool write_data_edge(int d) {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *e) {
                return false;
            }
            e->setData(d);
            return true;
        };

        bool write_weight_edge(int w) {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *Error) {
                return false;
            }
            e->setWeight(w);
            return true;
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        Graph<Vertex, Edge> *graph; //Обрабатываемый граф
        typename GraphMatrixForm<Edge>::OutputEdgeIterator *matrixIter;
        typename GraphListForm<Edge>::OutputEdgeIterator *listIter;
        bool isMatrix;
    public:
        string str1, str2, str3, str4;
        int curV1, curV2;
        bool end;

        OutputEdgeIterator(Graph<Vertex, Edge> &g, Vertex &v) {
            graph = &g;
            curV1 = graph->getIndex(&v);
            if (graph->isDense()) {
                matrixIter = new typename GraphMatrixForm<Edge>::OutputEdgeIterator(
                        static_cast<GraphMatrixForm<Edge> *>(g.data),
                        curV1);
                isMatrix = true;
            } else {
                listIter = new typename GraphListForm<Edge>::OutputEdgeIterator(static_cast<GraphListForm<Edge> *>(g.data),
                                                                           curV1);
                isMatrix = false;
            }
        }

        //Установка в начало
        bool toBegin() {
            if (isMatrix)
                return matrixIter->toBegin();
            else
                return listIter->toBegin();
        }

        //Сдвиг на следующий элемент
        bool operator++() {
            if (isMatrix)
                return matrixIter->next();
            else
                return listIter->next();
        }

        bool operator++(int) {
            if (isMatrix)
                return matrixIter->next();
            else
                return listIter->next();
        }

        bool toEnd() {
            if (isMatrix)
                return matrixIter->toEnd();
            else
                return listIter->toEnd();
        }

        //Проверка на выход
        bool onEnd() {
            if (isMatrix)
                return matrixIter->onEnd();
            else
                return listIter->onEnd();
        }

        //Получение ребра
        Edge *operator*() {
            if (onEnd())
                throw runtime_error("EXCEPTION!");
            if (isMatrix)
                return matrixIter->getEdge();
            else
                return listIter->getEdge();
        }

        string read_edge() {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *f) {
                throw "Exeption#";
            }
            Vertex *_v1, *_v2;
            _v1 = e->getVertex1();
            _v2 = e->getVertex2();
            if (_v1->nameSet == false)
                str1 = "#data not available";
            else
                str1 = _v1->getName();
            if (_v2->nameSet == false)
                str2 = "#data not available";
            else
                str2 = _v2->getName();
            if (e->isWeightSet() == false)
                str3 = "#data not available";
            else
                str3 = i_to_s(e->getWeight());
            str4 = "Исходящая вершина: " + str1 + ". Входящая вершина: " + str2 + ". Вес ребра: " + str3;
            return str4;
        }

        int read_data_edge() {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *f) {
                throw "Exeption#";
            }
            int a;
            if (e->isDataSet())
                return e->getData();
            else
                throw "#data not available";
        };

        bool write_data_edge(int d) {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *Error) {
                return false;
            }
            e->setData(d);
            return true;
        };

        bool write_weight_edge(int w) {
            Edge *e;
            try {
                e = operator*();
            }
            catch (char *Error) {
                return false;
            }
            e->setWeight(w);
            return true;
        }
    };
};


#endif
