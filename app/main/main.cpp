#include "../class/grafo.cpp"

int main()
{
    Grafo g;
    // Crear vértices
    for (int i = 0; i < 5; ++i)
        g.agregarVertice(i);

    // Agregar aristas (grafo dirigido y ponderado)
    g.agregarArista(0, 1, 10);
    g.agregarArista(0, 2, 3);
    g.agregarArista(1, 2, 1);
    g.agregarArista(2, 1, 4);
    g.agregarArista(2, 3, 8);
    g.agregarArista(2, 4, 2);
    g.agregarArista(3, 4, 7);
    g.agregarArista(4, 3, 9);

    cout << "Grafo (lista de adyacencia):\n";
    g.imprimir();

    cout << "\nRuta mas corta de 0 a 3:\n";
    g.dijkstra(0, 3);

    return 0;
}
