#include <iostream>
#include <fstream>
#include <vector>

class Vertex
{
  public:
    int index;
    bool colour;
    std::vector<int> edges;
    Vertex() : index(0), colour(false) {}
};

class Graph
{
  public:
    Vertex *list;
    int size;

    Graph() : list(nullptr), size(0) {}
    Graph(int size)
    {
        list = new Vertex[size];
        this->size = size;
    }

    Vertex &operator[](const int &key)
    {
        return list[key];
    }

    void readGraph()
    {
        int amount;
        std::cin >> amount;
        list = new Vertex[amount];
        this->size = amount;
        int a, b;
        while (std::cin >> a && std::cin >> b)
        {
            list[a].edges.push_back(b);
            list[b].edges.push_back(a);
        }
    }

    void displayGraph()
    {
        for (int i = 0; i < size; ++i)
        {
            std::cout << "Wierzcholek: " << i << ", sasiedzi: ";
            for (auto it = list[i].edges.cbegin(); it != list[i].edges.end(); ++it)
            {
                std::cout << *it << ", ";
            }
            std::cout << std::endl;
        }
    }

    void backToStock()
    {
        for (int i = 0; i < size; ++i)
        {
            list[i].colour = false;
        }
    }
    bool checkConnectivity(int vertex) //sprawdza spojnosc
    {
        list[vertex].colour = true;
        for (auto it = list[vertex].edges.begin(); it != list[vertex].edges.end(); ++it)
        {
            if (list[*it].colour == false)
                checkConnectivity(*it);
        }
        if (checkAllColoured() == true)
            return true;
        else
            return false;
    }

    bool checkAllColoured()
    {
        for (int i = 0; i < size; ++i)
        {
            if (list[i].colour == false)
                return false;
        }
        return true;
    }

    bool checkAllColoured(int first, int second) //nie bierze pod uwage wierzcholkow first i second
    {
        for (int i = 0; i < size; ++i)
        {
            if (i == first || i == second)
                continue;
            if (list[i].colour == false)
                return false;
        }
        return true;
    }

    bool chechBridge(int vertex, int first, int second)
    {
        if (vertex == first || vertex == second)
            throw std::invalid_argument("Error!");
        list[vertex].colour = true;
        for (auto it = list[vertex].edges.begin(); it != list[vertex].edges.end(); ++it)
        {
            if (*it == first || *it == second)
                continue;
            if (list[*it].colour == false)
                chechBridge(*it, first, second);
        }
        if (checkAllColoured(first, second) == true)
            return false;
        else
            return true;
    }
};

int main(int argc, char *argv[])
{
    Graph myGraph;
    myGraph.readGraph();
    //myGraph.displayGraph();
    if (myGraph.checkConnectivity(0) == false)
    {
        std::cout << "Graf niespojny!\n";
        return 0;
    }
    myGraph.backToStock();
    try
    {
        for (int vertex = 0; vertex < myGraph.size; ++vertex)
        {

            for (auto it = myGraph[vertex].edges.begin(); it != myGraph[vertex].edges.end(); ++it)
            {
                if (*it < vertex)
                    continue;
                if (vertex != 0 && *it != 0) //trzy możliwosci poniewaz dwa wierzcholki moga byc mostem
                {
                    if (myGraph.chechBridge(0, vertex, *it))
                        std::cout << vertex << " " << *it << std::endl;
                }
                else if (vertex != 1 && *it != 1)
                {
                    if (myGraph.chechBridge(1, vertex, *it))
                        std::cout << vertex << " " << *it << std::endl;
                }
                else if (vertex != 2 && *it != 2) //jezeli 1 0 jest mostem
                {
                    if (myGraph.chechBridge(2, vertex, *it))
                        std::cout << vertex << " " << *it << std::endl;
                }
                myGraph.backToStock();
            }
        }
    }
    catch (const std::invalid_argument &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
