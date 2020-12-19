#include <iostream>
#include "Graph.h"
#include "Vertex_map.h"
#include "Vertex.h"
#include "Edge.h"
#include "First_task.h"
#include "Second_task.h"


using namespace std;


void vertexIteratorMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph,
                        MapVertex<string, Vertex<string, int> *> &mapVertex) {
    Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>::VertexIterator vertexIterator(*graph);
    int key;
    while (true) {
        cout << "_____Menu iteratora vershin______\n"
             << "1) Set begin                     |\n"
             << "2) Set end                       |\n"
             << "3) To next                       |\n"
             << "4) Get name                      |\n"
             << "5) Set name                      |\n"
             << "6) Get data                      |\n"
             << "7) Set data                      |\n"
             << "8) Get index                     |\n"
             << "0) Exit                          |\n"
             << "---------------------------------\n"
             << "Input: ";
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
                        cout << "Name: " << (*vertexIterator)->getName() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 5:
                try {
                    cout << "Enter name: ";
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
                        cout << "Data: " << (*vertexIterator)->getData() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 7: {
                cout << "Enter data: ";
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
        cout << "_____Menu iteratora reber______\n"
             << "1) Set begin                   |\n"
             << "2) Set end                     |\n"
             << "3) To next                     |\n"
             << "4) Get weight                  |\n"
             << "5) Set weight                  |\n"
             << "6) Get data                    |\n"
             << "7) Set data                    |\n"
             << "8) Get index                   |\n"
             << "0) Exit                        |\n"
             << "-------------------------------\n"
             << "Input: ";
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
                        cout << "Weight: " << (*edgeIterator)->getWeight() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 5: {
                cout << "Enter weight: ";
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
                        cout << "Data: " << (*edgeIterator)->getData() << endl;
                    else
                        cout << boolalpha << false << endl;
                }
                catch (runtime_error error) {
                    cout << error.what() << endl;
                }
                break;
            case 7: {
                cout << "Enter data: ";
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
        cout << "Enter vertex: ";
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
            cout << "_____Menu iteratora ishodyashih reber______\n"
                 << "1) Set begin                               |\n"
                 << "2) Set end                                 |\n"
                 << "3) To next                                 |\n"
                 << "4) Get weight                              |\n"
                 << "5) Set weight                              |\n"
                 << "6) Get data                                |\n"
                 << "7) Set data                                |\n"
                 << "8) Get index                               |\n"
                 << "9) Choose another vertex                   |\n"
                 << "0) Exit                                    |\n"
                 << "-------------------------------------------\n"
                 << "Input: ";
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
                            cout << "Weight: " << (*outputEdgeIterator)->getWeight() << endl;
                        else
                            cout << boolalpha << false << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }

                    break;
                case 5: {
                    cout << "Enter weight: ";
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
                            cout << "Data: " << (*outputEdgeIterator)->getData() << endl;
                        else
                            cout << boolalpha << false << endl;
                    }
                    catch (runtime_error error) {
                        cout << error.what() << endl;
                    }
                    break;
                case 7:
                    cout << "Enter data: ";
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
        cout << "__Menu first task__\n"
             << "1) Restart         |\n"
             << "2) Result          |\n"
             << "0) Exit            |\n"
             << "-------------------\n"
             << "Input: ";
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
void secondTaskMenu(Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> *graph) {
    SecondTask<Vertex<string, int>, Edge<Vertex<string, int>, int, int>> secondTask(graph);

    int key;
    while (true) {
        cout << "__Menu second task__\n"
             << "1) Restart         |\n"
             << "2) Result          |\n"
             << "0) Exit            |\n"
             << "-------------------\n"
             << "Input: ";
        cin >> key;
        switch (key) {
            case 1:
                secondTask.restart();
                break;
            case 2:
                secondTask.result();
                break;
            case 0:
                return;
        }
    }
}


int main() {
    srand(time(0));
    auto *graph =
            new Graph<Vertex<string, int>, Edge<Vertex<string, int>, int, int>>(5, 4, true, true);
    MapVertex<string, Vertex<string, int> *> mapVertex;
    bool exit = true;
    int key, index1, index2;
    string name1, name2;
    while (exit) {
        cout << "_______________Main menu________________\n"
             << "1)  Print graph as matrix               |\n"
             << "2)  Print graph as list                 |\n"
             << "3)  Set random weights                  |\n"
             << "4)  Get count of vertex                 |\n"
             << "5)  Get count of edges                  |\n"
             << "6)  Get type of graph                   |\n"
             << "7)  Get form of graph                   |\n"
             << "8)  Get koef nasishennosti              |\n"
             << "9)  Transform to M-graph                |\n"
             << "10) Transform to L-graph                |\n"
             << "11) Add vertex                          |\n"
             << "12) Remove vertex by name               |\n"
             << "13) Remove vertex by index              |\n"
             << "14) Add edge by names                   |\n"
             << "15) Add edge by index                   |\n"
             << "16) Remove edge by names                |\n"
             << "17) Remove edge by index                |\n"
             << "18) Menu iterator vertex                |\n"
             << "19) Menu iterator edges                 |\n"
             << "20) Menu iterator ishodyashih           |\n"
             << "21) Menu first task                     |\n"
             << "22) Menu second task                    |\n"
             << "0)  Exit                                |\n"
             << "----------------------------------------\n"
             << "Input: ";
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
                cout << "Enter interval of weight\n"
                        "Min: ";
                cin >> weightMin;
                cout << "Max: ";
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
                cout << "Count of vertex: " << graph->getVertexCount() << endl;
                break;

            case 5:
                cout << "Count of edges: " << graph->getEdgeCount() << endl;
                break;

            case 6:
                if (graph->isDirected())
                    cout << "Directed graph\n";
                else
                    cout << "Undirected graph\n";
                break;

            case 7:
                if (graph->isDense())
                    cout << "Form: matrix\n";
                else
                    cout << "Form: list\n";
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
                    cout << "Enter name: ";
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
                cout << "Enter index: ";
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
                    cout << "Enter names of vertex\n";
                    cout << "Name 1: ";
                    cin >> name1;
                    cout << "Name 2: ";
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
                cout << "Enter index of vertex\n";
                cout << "Vertex 1: ";
                cin >> index1;
                cout << "Vertex 2: ";
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
                    cout << "Enter names of vertex\n";
                    cout << "Name 1: ";
                    cin >> name1;
                    cout << "Name 2: ";
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
                cout << "Enter index of vertex\n";
                cout << "Vertex 1: ";
                cin >> index1;
                cout << "Vertex 2: ";
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

            case 22:
                secondTaskMenu(graph);
                break;
        }
    }
    return 0;
}

