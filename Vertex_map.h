#ifndef ADS_RGR_VERTEX_MAP_H
#define ADS_RGR_VERTEX_MAP_H

#include <map>

using namespace std;

template<class Name, class Data>
class MapVertex {
    map<Name, Data> mapVertex;

public:
    //если второе имя не занято то делаем замену
    bool replaceName(Name name1, Name name2) {
        if (mapVertex.find(name2) == mapVertex.end()) {
            Data data = mapVertex[name1];
            mapVertex.erase(name1);
            mapVertex[name2] = data;
            return true;
        }
        return false;
    }

    bool addPair(Name name, Data data) {
        if (mapVertex.find(name) == mapVertex.end()) {
            mapVertex[name] = data;
            return true;
        }
        return false;
    }

    Data getData(Name name) {
        if (mapVertex.find(name) != mapVertex.end())
            return mapVertex[name];
        else
            throw runtime_error("EXCEPTION!");
    }

    bool delPair(Name name) {
        return mapVertex.erase(name) == 1;
    }
};


#endif //ADS_RGR_VERTEX_MAP_H
