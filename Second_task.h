#ifndef ADS_RGR_SECOND_TASK_H
#define ADS_RGR_SECOND_TASK_H

#include "Graph.h"
#include <vector>

using namespace std;

template<class Vertex, class Edge>
class SecondTask {
    Graph<Vertex, Edge> *graph;
    vector<int> vertex;
    vector<int> total;
    int min, index;
    const int INF = 10000000;

    int maxInVector() {
        int max = vertex[0];
        for (int i = 1; i < vertex.size(); ++i) {
            if (vertex[i] > max) max = vertex[i];
        }
        return max;
    }

    int minInVector() {
        min = total[0];
        for (int i = 1; i < vertex.size(); ++i) {
            if (total[i] < min) {
                min = total[i];
                index = i;
            }
        }
        return index;
    }


    void bellman_ford(int s) {
        for (int i = 0; i < graph->getVertexCount(); i++) {
            vertex[i] = INF;
        }
        vertex[s] = 0;

        for (int i = 1; i < graph->getVertexCount() - 1; i++) {
            for (int u = 0; u < graph->getVertexCount(); ++u) {
                for (int v = 0; v < graph->getVertexCount(); ++v) {
                    if (graph->hasEdge(u, v)) {
                        if (vertex[v] > vertex[u] + graph->getEdge(u, v)->getWeight()) {
                            vertex[v] = vertex[u] + graph->getEdge(u, v)->getWeight();

                        }
                    }
                }
            }
        }

//        for (int i = 0; i < graph->getVertexCount(); i++)
//            if (vertex[i] == INF)
//                cout << endl << s << "->" << i << "=" << "INF";
//            else cout << endl << s << "->" << i << "=" << vertex[i];
    }

public:

    SecondTask(Graph<Vertex, Edge> *g) : graph(g) {
        vertex.resize(graph->getVertexCount());
        total.resize(graph->getVertexCount());
        restart();
    }

    SecondTask(SecondTask<Vertex, Edge> &secondTask) {
        graph = secondTask.graph;
        vertex.resize(graph->getVertexCount());
        total.resize(graph->getVertexCount());
        restart();
    }

    ~SecondTask() {
        total.clear();
        vertex.clear();
    }

    void set(Graph<Vertex, Edge> *g) {
        graph = g;
        vertex.resize(graph->getVertexCount());
        total.resize(graph->getVertexCount());
        restart();
    }

    void restart() {
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            bellman_ford(i);
            total[i] = maxInVector();
        }
        index = minInVector();

    }

    void result() {
        if (!min) {
            cout << "Граф не является взвешенным! Укажите веса.\n";
            return;
        }
        if (min != INF) {
            cout << "Центр взвешенного орграфа: (i" << index << ")\n";
        } else {
            cout << "Центр взвешенного орграфа не найден!\n";
        }
    }

};

#endif //ADS_RGR_SECOND_TASK_H
