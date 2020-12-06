#ifndef ADS_RGR_FIRST_TASK_H
#define ADS_RGR_FIRST_TASK_H

#include "Graph.h"
#include <vector>

using namespace std;

template<class Vertex, class Edge>
class FirstTask {
    Graph<Vertex, Edge> *graph;
    vector<bool> visited;
    vector<int> path;
    bool res;

    bool hamilton(int cur) {
        path.push_back(cur);
        if (path.size() == graph->getVertexCount()) {
            if (graph->hasEdge(path.back(), path[0])) {
                return true;
            } else {
                path.pop_back();
                return false;
            }
        }
        visited[cur] = true;
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            if (graph->hasEdge(cur, i) && !visited[i]) {
                if (hamilton(i)) {
                    return true;
                }
            }
        }
        visited[cur] = false;
        path.pop_back();
        return false;
    }

public:

    FirstTask(Graph<Vertex, Edge> *g) : graph(g) {
        visited.resize(graph->getVertexCount());
        path.resize(graph->getVertexCount());
        restart();
    }

    FirstTask(FirstTask<Vertex, Edge> &firstTask) {
        graph = firstTask.graph;
        visited.resize(graph->getVertexCount());
        path.resize(graph->getVertexCount());
        restart();
    }

    ~FirstTask() {
        visited.clear();
        path.clear();
    }

    void set(Graph<Vertex, Edge> *g) {
        graph = g;
        visited.resize(graph->getVertexCount());
        path.resize(graph->getVertexCount());
        restart();
    }

    void restart() {
        visited.clear();
        path.clear();
        for (int i = 0; i < graph->getVertexCount(); ++i) {
            res = hamilton(i);
            if (res) return;
            visited.clear();
            path.clear();
        }
    }

    void result() {
        if (res) {
            cout << "Гамильтонов цикл найден!\n";
            for (int i = 0; i < graph->getVertexCount(); ++i) {
                cout << path[i] << " -> ";
            }
            cout << path[0] << endl;
        } else {
            cout << "Гамильтонов цикл не найден!\n";
        }
    }

};

#endif //ADS_RGR_FIRST_TASK_H
