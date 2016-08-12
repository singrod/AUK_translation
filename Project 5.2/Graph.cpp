/**************
Author: Mark Singleton
Date: 11/11/2015
Class: COP 2224C Professor Reed
***************/

#include "Graph.h"
#include <iostream>
#include <map>
#include <sstream>
#include <stdlib.h>
#include <string>

using namespace std;

Graph::Graph(string fileName)
{
    Parse(fileName);
    ht = 24;
    wid = 80;
    ox = 10;
    oy = 2;
    frame();
    ticks();
    data();
    labelBottom();
    draw();
}

Graph::~Graph()
{

}

void Graph::Parse(string fileName)
{

    inFS.open(fileName.c_str());
    if(!inFS.is_open())
    {
        cout << "Could not open file!" << endl;
    }

    while(!inFS.eof())
    {
// gets each line of file
        getline(inFS, fileLines);

        string tmps;
        istringstream is (fileLines);

// Parsing lines

        while (is.good ())
        {
            is >> tmps;
            if(tmps == "label")
            {
                label = "";
                while (is.good ())
                {
                    is >> tmps;
                    label = label + tmps + " ";
                }

            }
            else if(tmps == "range")
            {
                while (is.good ())
                {
                    is >> range.minX;
                    is >> range.minY;
                    is >> range.maxX;
                    is >> range.maxY;
                }

            }
            else if(tmps == "left")
            {
                int left = 0;
                is >> tmps;
                while (is.good ())
                {

                    is >> left;
                    dataPointY.push_back(left);

                }

            }
            else if(tmps == "bottom")
            {
                int bottom = 0;
                is >> tmps;
                while (is.good ())
                {

                    is >> bottom;
                    dataPointX.push_back(bottom);

                }

            }
            else if(atoi(tmps.data()) != 0)
            {
                int number;
                is >> number;
                pair<int, int> pairTemp(atoi(tmps.data()), number);
                graphPlacesXY.push_back(pairTemp);

            }

        }

    }

    inFS.close();

}
void Graph::frame ()
{
    for (int i = ox; i < wid; i++)  // bottom
    {
        plot(i, oy, '-');
    }
    for (int i = ox; i < wid; i++)  // top
    {
        plot(i, ht-1, '-');
    }

    for (int i = oy; i < ht; i++)  // left
    {
        plot(ox, i, '|');
    }
    for (int i = oy; i < ht; i++)  // right
    {
        plot(wid-1, i, '|');
    }

}

void Graph::ticks()  // create tick marks for both axes
{

    char a [20];

    for(unsigned int i = 0; i < dataPointX.size(); i++)
    {
        plot(xscale(dataPointX[i]), oy, '|');
        splot(xscale(dataPointX[i]) - 1, 1, string(itoa(dataPointX[i], a, 10)));
    }
    for(unsigned int i = 0; i < dataPointY.size(); i++)
    {
        plot(ox, yscale(dataPointY[i]), '-');
        splot(0, yscale(dataPointY[i]), string(itoa(dataPointY[i], a, 10)));
    }

}

void Graph::data()  // create data points
{
    for(unsigned int i = 0; i <graphPlacesXY.size(); i++)
    {
        int x =xscale(graphPlacesXY[i].first);
        int y = yscale(graphPlacesXY[i].second);
        plot(x, y,  '.' );
    }
}
void Graph::labelBottom()  // center label under x-axis
{
    splot(int((wid + ox - label.size()) / 2.0), 0, label);
}

int Graph::xscale(int x)  // scale x-value
{
    return (int)((x - (double)range.minX) / (range.maxX - range.minX) * (wid-1-ox) + ox + 0.5);
}
int Graph::yscale(int y)  // scale y-value
{
    return  (int)((y - (double)range.minY) / (range.maxY - range.minY) * (ht-1-oy) + oy + 0.5);
}

void Graph::plot(int x, int y, char c)  // put character c in array
{
    pair<int, int>  pointsXY(y, x);
    coordinatesXY[pointsXY]= c ;
}

void Graph::splot(int x, int y, string label)  // put string s in array
{
    for(unsigned int i = 0; i < label.size(); i++)
    {
        pair<int, int>  pointsXY(y, x+i);
        coordinatesXY[pointsXY] = label.at(i);
    }
}
void Graph::draw()  // print graph from array
{
    for(int i = ht - 1; i >= 0; i--)
    {
        for(int j = 0; j < wid; j++)
        {
            pair<int, int> pointsXY(i, j);
            char c = coordinatesXY[pointsXY];
            if(c == 0)
            {
                cout << " ";

            }
            else
            {
                cout << c ;
            }

        }
        cout << endl;
    }
}
