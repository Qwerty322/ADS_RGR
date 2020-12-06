#ifndef ADS_RGR_GRAPH_FORMS_H
#define ADS_RGR_GRAPH_FORMS_H

#include <iostream>
#include <vector>
#include <list>

using namespace std;

//форма представления
template<class Edge>
class GraphForm {
public:
    //Вставка и удаление вершин и рёбер
    virtual bool insertVertex(int index) = 0;

    virtual bool deleteVertex(int index) = 0;

    virtual bool insertEdge(int v1, int v2, Edge *t) = 0;

    virtual bool deleteEdge(int v1, int v2) = 0;

    //Удалить входящие и исходящие из вершины рёбра
    virtual int deleteEdgesFromVertex(int index) = 0;

    //Проверка и получение
    virtual bool hasEdge(int v1, int v2) = 0;

    virtual Edge *getEdge(int v1, int v2) = 0;
};

//форма представления матричная
template<class Edge>
class GraphMatrixForm : public GraphForm<Edge> {
    friend class EdgeIterator;
    bool directed;
public:
    vector<vector<Edge *>> matrix;        //Матрица смежности

    explicit GraphMatrixForm(bool directed) : directed(directed) {}

    //Вставка и удаление вершин и рёбер
    bool insertVertex(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index > size) return false;
        //Создаём новую пустую строку
        vector<Edge *> newLine;
        newLine.assign(size, NULL);
        //Вставляем новую строку:
        matrix.insert(matrix.begin() + index, newLine);
        ++size;
        //Вставляем новый столбец:
        for (int i = 0; i < size; ++i)
            matrix[i].insert(matrix[i].begin() + index, (Edge *) NULL);
        return true;
    }

    bool deleteVertex(int index) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (index < 0 || index >= size) return false;
        //Удаляем строку:
        matrix.erase(matrix.begin() + index);
        --size;
        //Удаляем столбец:
        for (int i = 0; i < size; i++)
            matrix[i].erase(matrix[i].begin() + index);
        return true;
    }

    bool insertEdge(int v1, int v2, Edge *t) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Петля или ребро уже есть
        if (v1 == v2 || matrix[v1][v2] != NULL) return false;
        //Вставляем ребро
        matrix[v1][v2] = t;
        return true;
    }

    bool deleteEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size) return false;
        //Ребра нет
        if (v1 == v2 || matrix[v1][v2] == NULL) return false;
        matrix[v1][v2] = NULL;
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int deleteEdgesFromVertex(int index) {
        int size = matrix.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size) return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; i++) {
            if (matrix[i][index] != NULL) {
                delete matrix[i][index];
                matrix[i][index] = NULL;
                ++deleted;
                //Стираем симметричное ребро
                if (!directed)
                    matrix[index][i] = NULL;
            }
            if (matrix[index][i] != NULL) {
                delete matrix[index][i];
                matrix[index][i] = NULL;
                ++deleted;
            }
        }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        if (v1 == v2) //Петля
            return false;
        if (matrix[v1][v2] != NULL)
            return true;
        return false;
    }

    Edge *getEdge(int v1, int v2) {
        int size = matrix.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw runtime_error("EXCEPTION!");
        if (v1 == v2 || matrix[v1][v2] == NULL)//Петля
            throw runtime_error("EXCEPTION!");
        return matrix[v1][v2];
    }

    //Итератор рёбер
    class EdgeIterator {
        bool end;
        GraphMatrixForm *f;
    public:
        int currentI, currentJ;

        EdgeIterator(GraphMatrixForm *f) {
            this->f = f;
            toBegin();
        }

        bool toBegin() {
            for (int i = 0; i < f->matrix.size(); ++i)
                for (int j = 0; j < f->matrix.size(); ++j)
                    if (f->matrix[i][j]) {
                        currentI = i;
                        currentJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        bool toEnd() {
            for (int i = f->matrix.size() - 1; i >= 0; --i)
                for (int j = f->matrix.size() - 1; j >= 0; --j)
                    if (f->matrix[i][j]) {
                        currentI = i;
                        currentJ = j;
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool next() {
            if (end)
                return false;
            ++currentJ;
            while (currentI < f->matrix.size()) {
                while (currentJ < f->matrix.size()) {
                    if (f->matrix[currentI][currentJ])
                        return true;
                    ++currentJ;
                }
                ++currentI;
                currentJ = (f->directed ? 0 : currentI + 1);
            }
            end = true;
            return false;
        }

        Edge *getEdge() {
            if (end)
                throw runtime_error("EXCEPTION!");
            if (!(f->matrix[currentI][currentJ]))
                throw runtime_error("EXCEPTION!");
            return f->matrix[currentI][currentJ];
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        int currentI, currentJ;
        bool end;
        GraphMatrixForm *f;
    public:
        OutputEdgeIterator(GraphMatrixForm *f, int index) {
            this->f = f;
            currentI = index;
            toBegin();
        }

        bool toBegin() {
            for (currentJ = 0; currentJ < f->matrix.size(); ++currentJ)
                if (f->matrix[currentI][currentJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool toEnd() {
            for (currentJ = f->matrix.size() - 1; currentJ >= 0; --currentJ)
                if (f->matrix[currentI][currentJ]) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        bool next() {
            if (end)
                return false;
            ++currentJ;
            while (currentJ < f->matrix.size()) {
                if (f->matrix[currentI][currentJ])
                    return true;
                ++currentJ;
            }
            end = true;
            return false;
        }

        Edge *getEdge() {
            if (end)
                throw runtime_error("EXCEPTION!");
            return f->matrix[currentI][currentJ];
        }
    };
};

//форма представления список
template<class Edge>
class GraphListForm : public GraphForm<Edge> {
    //Элемент списка
    class Node {
    public:
        Edge *edge; //Само ребро
        int v2;      //Вторая вершина, которую ребро соединяет
    };

    bool directed;
    vector<list<Node>> edgeList; //Списки смежности
public:
    explicit GraphListForm(bool directed) : directed(directed) {}

    //Вставка и удаление вершин и рёбер
    bool insertVertex(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index > size) //Неверный номер вершины
            return false;
        //Создаём новый список смежности
        list<Node> newList;
        //Вставляем
        edgeList.insert(edgeList.begin() + index, newList);
        ++size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 >= index)//если текущая вершина имеет больший номер, чем вставляемая,
                    ++((*j).v2);//то увеличиваем этот номер
        return true;
    }

    bool deleteVertex(int index) {
        int size = edgeList.size(); //Число вершин
        if (index < 0 || index >= size)  //Неверный номер вершины
            return false;
        //Удаляем из списков записи о рёбрах
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    edgeList[i].erase(j);
                    break;
                }
        //Удаляем список смежности
        edgeList.erase(edgeList.begin() + index);
        --size;
        //Обновляем дескрипторы
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 > index)//если текущая вершина имеет больший номер, чем удаляемая,
                    --((*j).v2);//то уменьшить этот номер
        return true;
    }

    bool insertEdge(int v1, int v2, Edge *t) {
        int size = edgeList.size(); //Число вершин
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)//Неверный номер вершины
            return false;
        if (v1 == v2 || hasEdge(v1, v2))  //Петля или ребро уже есть
            return false;
        //Вставляем ребро
        Node node;
        node.edge = t;
        node.v2 = v2;
        edgeList[v1].push_front(node);
        return true;
    }

    bool deleteEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Ребра нет
        if (v1 == v2 || hasEdge(v1, v2) == false)
            return false;
        //Удаляем ребро
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2) {
                edgeList[v1].erase(j);
                break;
            }
        return true;
    }

    //Удалить входящие и исходящие из вершины рёбра
    int deleteEdgesFromVertex(int index) {
        int size = edgeList.size(); //Число вершин
        int deleted = 0;
        //Неверный номер вершины
        if (index < 0 || index >= size)
            return 0;
        //Удаляем связанные с вершиной рёбра
        for (int i = 0; i < size; ++i)
            for (typename list<Node>::iterator j = edgeList[i].begin(); j != edgeList[i].end(); ++j)
                if ((*j).v2 == index) {
                    delete (*j).edge;
                    edgeList[i].erase(j);
                    ++deleted;
                    //Стираем симметричное ребро
                    if (!directed)
                        for (typename list<Node>::iterator k = edgeList[index].begin(); k != edgeList[index].end(); ++k)
                            if ((*k).v2 == i) {
                                edgeList[index].erase(k);
                                break;
                            }
                    break;
                }
        if (directed) {
            for (typename list<Node>::iterator z = edgeList[index].begin(); z != edgeList[index].end(); ++z) {
                delete (*z).edge;
                deleted++;
            }
        }
        return deleted;
    }

    //Проверка и получение
    bool hasEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            return false;
        //Петля
        if (v1 == v2)
            return false;
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return true;
        return false;
    }

    Edge *getEdge(int v1, int v2) {
        int size = edgeList.size(); //Число вершин
        //Неверный номер вершины
        if (v1 < 0 || v2 < 0 || v1 >= size || v2 >= size)
            throw runtime_error("EXCEPTION!");
        //Петля
        if (v1 == v2)
            throw runtime_error("EXCEPTION!");
        for (typename list<Node>::iterator j = edgeList[v1].begin(); j != edgeList[v1].end(); ++j)
            if ((*j).v2 == v2)
                return (*j).edge;
        throw runtime_error("EXCEPTION!");
    }

    //Итератор рёбер
    class EdgeIterator {
        int currentI;
        typename list<typename GraphListForm<Edge>::Node>::iterator currentJ;
        bool end;
        GraphListForm *f;
    public:
        EdgeIterator(GraphListForm *f) {
            this->f = f;
        }

        //Установить итератор рёбер на начальное ребро
        bool toBegin() {
            for (currentI = 0; currentI < f->edgeList.size(); ++currentI)
                for (currentJ = f->edgeList[currentI].begin(); currentJ != f->edgeList[currentI].end(); ++currentJ)
                    if ((*currentJ).edge) {
                        end = false;
                        return true;
                    }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        //Установить итератор рёбер на конечное ребро
        bool toEnd() {
            typename list<typename GraphListForm<Edge>::Node>::iterator prev_curJ;
            for (currentI = 0; currentI < f->edgeList.size(); ++currentI) {
                for (currentJ = f->edgeList[currentI].begin(); currentJ != f->edgeList[currentI].end(); ++currentJ) {
                    if ((*currentJ).edge)
                        prev_curJ = currentJ;
                    if (!(*prev_curJ).edge) {
                        end = true;
                        return false;
                    } else {
                        end = false;
                        currentJ = prev_curJ;
                        return true;
                    }
                }
            }
        };

        //Переход к следующей позиции
        bool next() {
            if (end)
                return false;
            ++currentJ;
            while (currentI < f->edgeList.size()) {
                while (currentJ != f->edgeList[currentI].end()) {
                    if ((*currentJ).edge && (f->directed || !f->directed && (*currentJ).v2 > currentI))
                        return true;
                    ++currentJ;
                }
                ++currentI;
                if (currentI < f->edgeList.size())
                    currentJ = f->edgeList[currentI].begin();
            }
            end = true;
            return true;
        }

        Edge *getEdge() {
            if (end)
                throw runtime_error("EXCEPTION!");
            return (*currentJ).edge;
        }
    };

    //Итератор исходящих рёбер
    class OutputEdgeIterator {
        int currentI;
        typename list<typename GraphListForm<Edge>::Node>::iterator currentJ;
        bool end;
        GraphListForm *f;
    public:
        OutputEdgeIterator(GraphListForm *f, int vIndex) {
            this->f = f;
            currentI = vIndex;
            toBegin();
        }

        bool toBegin() {
            for (currentJ = f->edgeList[currentI].begin(); currentJ != f->edgeList[currentI].end(); ++currentJ)
                if ((*currentJ).edge) {
                    end = false;
                    return true;
                }
            end = true;
            return false;
        }

        bool onEnd() {
            return end;
        }

        bool toEnd() {
            typename list<typename GraphListForm<Edge>::Node>::iterator prev_curJ;
            for (currentJ = f->edgeList[currentI].begin(); currentJ != f->edgeList[currentI].end(); ++currentJ)
                if ((*currentJ).edge)
                    prev_curJ = currentJ;
            if (!(*prev_curJ).edge) {
                end = true;
                return false;
            } else {
                end = false;
                currentJ = prev_curJ;
                return true;
            };
        }

        bool next() {
            if (end)
                return false;
            ++currentJ;
            while (currentJ != f->edgeList[currentI].end()) {
                if ((*currentJ).edge)
                    return true;
                ++currentJ;
            }
            end = true;
            return true;
        }

        Edge *getEdge() {
            if (end)
                throw runtime_error("EXCEPTION!");
            return (*currentJ).edge;
        }
    };

};


#endif //ADS_RGR_GRAPH_FORMS_H
