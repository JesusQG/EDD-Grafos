#pragma once
#include <iostream>
#include "node.cpp"
#include <limits>
using namespace std;
struct Adyacente
{
    int destino;
    int peso;
    Adyacente *next;
    Adyacente(int d, int p, Adyacente *n = nullptr) : destino(d), peso(p), next(n) {}
};
class Vertice
{
public:
    int id;
    Adyacente *ady;
    Vertice *next;
    Vertice() : id(-1), ady(nullptr), next(nullptr) {}
    Vertice(int id) : id(id), ady(nullptr), next(nullptr) {}
};

class Grafo
{
private:
    Node<Vertice *> *vertices;
    int numVertices;

    Vertice *buscarVertice(int id)
    {
        Node<Vertice *> *v = vertices;
        while (v)
        {
            if (v->getData()->id == id)
                return v->getData();
            v = v->getNext();
        }
        return nullptr;
    }

public:
    Grafo() : vertices(nullptr), numVertices(0) {}

    void agregarVertice(int id)
    {
        if (!buscarVertice(id))
        {
            Vertice *nuevo = new Vertice(id);
            Node<Vertice *> *nuevoNodo = new Node<Vertice *>(nuevo, vertices);
            vertices = nuevoNodo;
            numVertices++;
        }
    }

    void agregarArista(int origen, int destino, int peso)
    {
        Vertice *v = buscarVertice(origen);
        if (!v)
            return;
        v->ady = new Adyacente(destino, peso, v->ady);
    }

    void imprimir()
    {
        Node<Vertice *> *v = vertices;
        while (v)
        {
            cout << "Vertice " << v->getData()->id << ": ";
            Adyacente *a = v->getData()->ady;
            while (a)
            {
                cout << "-> (" << a->destino << ", peso " << a->peso << ") ";
                a = a->next;
            }
            cout << endl;
            v = v->getNext();
        }
    }

    void dijkstra(int origen, int destino)
    {
        const int INF = std::numeric_limits<int>::max();
        int dist[100];
        int prev[100];
        bool visitado[100] = {false};
        int ids[100];
        int n = 0;
        Node<Vertice *> *v = vertices;
        while (v)
        {
            int vid = v->getData()->id;
            ids[n++] = vid;
            v = v->getNext();
        }
        for (int i = 0; i < 100; ++i)
        {
            dist[i] = INF;
            prev[i] = -1;
        }
        for (int i = 0; i < n; ++i)
        {
            dist[ids[i]] = INF;
            prev[ids[i]] = -1;
            visitado[ids[i]] = false;
        }
        dist[origen] = 0;

        for (int i = 0; i < n; ++i)
        {
            int u = -1, minDist = INF;
            for (int j = 0; j < n; ++j)
            {
                int vid = ids[j];
                if (!visitado[vid] && dist[vid] < minDist)
                {
                    minDist = dist[vid];
                    u = vid;
                }
            }
            if (u == -1)
                break;
            visitado[u] = true;

            Vertice *vert = buscarVertice(u);
            Adyacente *a = vert->ady;
            while (a)
            {
                if (dist[u] != INF && dist[u] + a->peso < dist[a->destino])
                {
                    dist[a->destino] = dist[u] + a->peso;
                    prev[a->destino] = u;
                }
                a = a->next;
            }
        }
        if (dist[destino] == INF)
        {
            cout << "No hay ruta de " << origen << " a " << destino << endl;
            return;
        }
        cout << "Distancia minima de " << origen << " a " << destino << ": " << dist[destino] << endl;
        cout << "Ruta: ";
        int path[100], cnt = 0, curr = destino;
        while (curr != -1)
        {
            path[cnt++] = curr;
            curr = prev[curr];
        }
        for (int i = cnt - 1; i >= 0; --i)
        {
            cout << path[i];
            if (i > 0)
                cout << " -> ";
        }
        cout << endl;
    }
};