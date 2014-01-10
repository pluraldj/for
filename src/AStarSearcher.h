//
//  AStarSearcher.h
//  forogue
//
//  Created by Lasse Carstensen on 30/12/13.
//  Copyright (c) 2013 Lasse Carstensen. All rights reserved.
//
// This file is part of FOR.
//
// FOR is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// FOR is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with FOR (see file LICENSE).  If not, see <http://www.gnu.org/licenses/>.

// Generic A* search for path finding
// Based on http://www.boost.org/doc/libs/1_46_1/libs/graph/example/astar_maze.cpp

#ifndef __forogue__AStarSearcher__
#define __forogue__AStarSearcher__

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED
#endif

#include <iostream>

#include <ctime>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

#include "Location.h"

using namespace std;

// Floating point infinity, used for unreachable nodes
#define MAX_COST numeric_limits<double>::max()

// What set a node belongs to
#define OPEN 1
#define CLOSED 2
#define CAME_FROM 3

struct GridGraphVertex
{
public:
    GridGraphVertex()
    {
        coord = veci(0,0);
        
        outNeighbors = new vector<GridGraphVertex*>;
        
        f_score = 0.0;
        g_score = 0.0;
        state = OPEN;
        
        cameFrom = NULL;
    }
    
    ~GridGraphVertex()
    {
        if ( outNeighbors )
            delete outNeighbors;
    }
    
    veci coord; // coordinates in grid
    
    int state;      // open,closed,came_from
    
    double f_score, g_score;    // real and heuristic score for node in path
    
    // The node we came from last, for rebuilding the optimal path after search
    GridGraphVertex *cameFrom;
    
    vector<GridGraphVertex *> *outNeighbors;
};

struct GridGraph
{
public:
    GridGraph(int _sizex, int _sizey)
    {
        sizex = _sizex;
        sizey = _sizey;
        
        vertices = new vector< vector<GridGraphVertex*>* >(_sizex);
        for ( auto it1=vertices->begin(); it1 != vertices->end(); ++it1 )
        {
            (*it1) = new vector<GridGraphVertex*>(_sizey);
            for ( auto it2=(*it1)->begin(); it2!=(*it1)->end(); it2++ )
                *it2 = new GridGraphVertex();
        }
    }
    
    ~GridGraph()
    {
        if ( vertices )
        {
            for ( auto it1=vertices->begin(); it1 != vertices->end(); ++it1 )
            {
                for ( auto it2=(*it1)->begin(); it2!=(*it1)->end(); it2++ )
                    delete (*it2);
                
                delete (*it1);
            }
            
            delete vertices;
        }
    }

    int sizex, sizey;
    
    vector<vector<GridGraphVertex*>*> *vertices;
};

class AStarSearcher
{
public:
    AStarSearcher(Location *_loc);
    ~AStarSearcher();
    
    bool Solve();   // Returns success/failure
    
    // Construct path (vector of nodes) if solution found
    void ReconstructPath(GridGraphVertex *node);
    
    void DumpSolution(string path);
    
    Location *loc;
    veci start, goal;
    
    GridGraph *graph;
    vector<GridGraphVertex*> *solution;
    
private:
    void CreateGraph();
    
    // Compute heuristic function based on relative vector, distance based
    double Heuristic(GridGraphVertex *a, GridGraphVertex *b);
};



#endif /* defined(__forogue__AStarSearcher__) */
