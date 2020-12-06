#ifndef ADS_RGR_EDGE_H
#define ADS_RGR_EDGE_H

#include <iostream>
using namespace std;



//АТД «Дескриптор ребра графа»
template<class Vertex, class Weight, class Data>
class Edge {
    Vertex *v1, *v2;   //Вершины, которые соединяет ребро
    Weight weight;     //Вес
    Data data;         //Данные ребра
    bool isWeight, isData;
public:
    Edge(Vertex *v1, Vertex *v2) :
            v1(v1),
            v2(v2),
            isWeight(false),
            weight(0),
            isData(false) {}

    Edge(Vertex *v1, Vertex *v2, Weight weight) :
            v1(v1),
            v2(v2),
            weight(weight),
            isWeight(true),
            isData(false) {}

    Edge(Vertex *v1, Vertex *v2, Weight weight, Data data) :
            v1(v1),
            v2(v2),
            weight(weight),
            data(data),
            isWeight(true),
            isData(true) {}

    void setWeight(Weight weight) {
        this->weight = weight;
        isWeight = true;
    }

    void setData(Data data) {
        this->data = data;
        isData = true;
    }

    Weight getWeight() {
        return weight;
    }

    Data getData() {
        return data;
    }

    Vertex *getVertex1() {
        return v1;
    };

    Vertex *getVertex2() {
        return v2;
    };

    bool hasWeight() {
        return isWeight;
    }

    bool hasData() {
        return isData;
    }
};


#endif //ADS_RGR_EDGE_H
