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
    bool hasWeight = false;
    const int INF = 10000000;

    int maxInVector();

    int minInVector();

    void bellman_ford(int s);

public:
    explicit SecondTask(Graph<Vertex, Edge> *g);

    SecondTask(SecondTask<Vertex, Edge> &secondTask);

    ~SecondTask();

    void set(Graph<Vertex, Edge> *g);

    void restart();

    void result();

};

template<class Vertex, class Edge>
int SecondTask<Vertex, Edge>::maxInVector() {
    int max = vertex[0];
    for (int i = 1; i < vertex.size(); ++i) {
        if (vertex[i] > max) max = vertex[i];
    }
    return max;
}

template<class Vertex, class Edge>
int SecondTask<Vertex, Edge>::minInVector() {
    min = total[0];
    index = 0;
    for (int i = 1; i < vertex.size(); ++i) {
        if (total[i] < min) {
            min = total[i];
            index = i;
        }
    }
    return index;
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::bellman_ford(int s) {
    for (int i = 0; i < graph->getVertexCount(); i++) {
        vertex[i] = INF;
    }
    vertex[s] = 0;

    for (int i = 1; i < graph->getVertexCount() - 1; i++) {
        for (int u = 0; u < graph->getVertexCount(); ++u) {
            for (int v = 0; v < graph->getVertexCount(); ++v) {
                if (graph->hasEdge(u, v)) {
                    if (!hasWeight) {
                        hasWeight = graph->getEdge(u, v)->hasWeight();
                        if (!hasWeight) return;
                    }
                    if (vertex[v] > vertex[u] + graph->getEdge(u, v)->getWeight()) {
                        vertex[v] = vertex[u] + graph->getEdge(u, v)->getWeight();

                    }
                }
            }
        }
    }
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(Graph<Vertex, Edge> *g) {
    graph = g;
    vertex.resize(graph->getVertexCount());
    total.resize(graph->getVertexCount());
    restart();
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::SecondTask(SecondTask<Vertex, Edge> &secondTask) {
    graph = secondTask.graph;
    vertex.resize(graph->getVertexCount());
    total.resize(graph->getVertexCount());
    restart();
}

template<class Vertex, class Edge>
SecondTask<Vertex, Edge>::~SecondTask() {
    total.clear();
    vertex.clear();
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::set(Graph<Vertex, Edge> *g) {
    graph = g;
    vertex.resize(graph->getVertexCount());
    total.resize(graph->getVertexCount());
    restart();
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::restart() {
    for (int i = 0; i < graph->getVertexCount(); ++i) {
        bellman_ford(i);
        total[i] = maxInVector();
    }
    index = minInVector();
}

template<class Vertex, class Edge>
void SecondTask<Vertex, Edge>::result() {
    if (!hasWeight) {
        cout << "Граф не является взвешенным! Укажите веса.\n";
        return;
    }
    if (min != INF) {
        cout << "Центр взвешенного орграфа: (i" << index << ")\n";
        cout << "Эксцентриситеты графа:\n";
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            cout << "(" << i << ") = " << total[i] << endl;
        }
    } else {
        cout << "Центр взвешенного орграфа не найден!\n";
    }
}

#endif //ADS_RGR_SECOND_TASK_H
