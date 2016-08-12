/**************
Author: Mark Singleton
Date: 11/11/2015
Class: COP 2224C Professor Reed
***************/

#ifndef GRAPH_H
#define GRAPH_H
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <string>

class Graph
{
public:
    Graph(std::string name);
    virtual ~Graph();
    void frame ();
    void plot(int x, int y, char c);
    void splot(int, int, std::string);
    std::map<std::pair<int, int>, char> coordinatesXY;
    void draw();
    void ticks();
    void data();
    void labelBottom();
    int xscale(int x);
    int yscale(int y);

private:
    struct Axes
    {
        int minX;
        int minY;
        int maxX;
        int maxY;
    };

    std::ifstream inFS;
    std::string fileName;
    std::string fileLines;

    std::vector<int> dataPointX;
    std::vector<int> dataPointY;
    std::vector<std::pair<int, int> > graphPlacesXY;

    void Parse(std::string name);
    std::string label;
    struct Axes range;
    int ht;
    int wid;
    int ox;
    int oy;
};

#endif // GRAPH_H
