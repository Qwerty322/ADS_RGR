#ifndef ADS_RGR_VERTEX_H
#define ADS_RGR_VERTEX_H

#include <iostream>

using namespace std;


//АТД «Дескриптор вершины графа»
template<class Name, class Data>
class Vertex {
    Name name;  //Имя вершины
    Data data;  //Данные, связанные с вершиной
public:
    bool isName, isData;
    int index;

    Vertex() :
            isName(false),
            isData(false) {}

    Vertex(Name name, Data data) :
            name(name),
            data(data),
            isName(true),
            isData(true) {}

    void setName(Name name) {
        this->name = name;
        isName = true;
    }

    void setData(Data data) {
        this->data = data;
        isData = true;
    }

    Name getName() {
        return name;
    }

    Data getData() {
        return data;
    }

    bool hasName() {
        return isName;
    }

    bool hasData() {
        return isData;
    }
};

#endif //ADS_RGR_VERTEX_H
