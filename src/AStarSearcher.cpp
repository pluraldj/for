//
//  AStarSearcher.cpp
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

#include "AStarSearcher.h"

#include <signal.h>

AStarSearcher::AStarSearcher(Location *_loc)
{
    loc = _loc;
    
    graph = new GridGraph(loc->size.x, loc->size.y);
    solution = new vector<GridGraphVertex*>;
    
    start = goal = veci(0,0);
    
    CreateGraph();
}

AStarSearcher::~AStarSearcher()
{
    if ( graph )
        delete graph;
    
    if ( solution )
        delete solution;
}


void AStarSearcher::CreateGraph()
{
    for ( int iy = 0; iy < graph->sizey; ++iy )
    {
        for ( int ix = 0; ix < graph->sizex; ++ix )
        {
            // Tentative new node
            GridGraphVertex *newnode = graph->vertices->at(ix)->at(iy);
            newnode->coord = veci(ix,iy);
            
            // Tile corresponding to node
            Tile *tile = loc->GetTile(ix, iy);
            
            // Is it passable? (clipmask true)
            if ( !tile->clipMask )
            {
                // Guess we ain't got to do no thing
                continue;
            }
            
            // Add neighbors
            for ( int dx=-1; dx<=1; dx++ )
            {
                for ( int dy=-1; dy<=1; dy++ )
                {
                    // Exclude ourself
                    if ( dx == 0 && dy == 0 )
                        continue;
                    
                    // Exclude diagonals
                    if ( abs(dx) == 1 && abs(dy) == 1 )
                        continue;
                    
                    int newx = ix+dx;
                    int newy = iy+dy;
                    
                    // Out of bounds?
                    if ( newx < 0 || newy < 0 || newx >= graph->sizex || newy >= graph->sizey )
                        continue;
                    
                    GridGraphVertex *neighborVertex = graph->vertices->at(newx)->at(newy);
                    
                    Tile *neighborTile = loc->GetTile(newx, newy);
                    
                    // Only link if we can get there from here
                    if ( neighborTile->clipMask == true )
                    {
                        // Remember to _not_ link both ways
                        // The other link will be made when we reach that node
                        newnode->outNeighbors->push_back(neighborVertex);
                        //neighborVertex->outNeighbors->push_back(newnode);
                    }
                }
            }
        }
    }
}

bool AStarSearcher::Solve()
{
    // Clear old stored solution, if any
    solution->clear();
    
    // Same tile? no path to find, just stay put
    if ( start == goal)
        return true;    // True return value distinguishes this from a failed search (no path)
    
    Tile *start_tile = loc->GetTile(start.x, start.y);
    Tile *goal_tile = loc->GetTile(goal.x, goal.y);
    
    // Is a solution even possible? Both start, end tiles must be passable
    if ( start_tile->clipMask == false || goal_tile->clipMask == false )
        return false;
    
    // Start and goal nodes
    GridGraphVertex *startNode = graph->vertices->at(start.x)->at(start.y);
    GridGraphVertex *goalNode = graph->vertices->at(goal.x)->at(goal.y);
    
    // The list of open nodes on the frontier
    vector<GridGraphVertex*> openSet;
    openSet.push_back(startNode);
    
    // Mark all as open and init scores to inf, also erase came from map
    for ( auto it1=graph->vertices->begin(); it1!=graph->vertices->end(); it1++ )
    {
        for ( auto it2=(*it1)->begin(); it2!=(*it1)->end(); it2++ )
        {
            (*it2)->state = OPEN;
            
            (*it2)->f_score = MAX_COST;
            (*it2)->g_score = MAX_COST;
            
            (*it2)->cameFrom = NULL;
        }
    }
    
    // Initil cost along best path
    startNode->g_score = 0.0;
    
    // Initial heuristic guess for best path
    startNode->f_score = startNode->g_score + Heuristic(startNode, goalNode);
    
    while ( openSet.size() != 0 )
    {
        // Determine which node has lowest f_score
        GridGraphVertex *current = openSet[0]; // initial guess
        for ( auto it=openSet.begin(); it!=openSet.end(); it++ )
        {
            if ( (*it)->f_score < current->f_score )
                current = (*it);
        }
        
        // Reached goal?
        if ( current->coord == goal )
        {
            ReconstructPath(current);
            return true;
        }
        
        // remove current from open and close it
        auto currIt = std::find(openSet.begin(), openSet.end(), current);
        openSet.erase(currIt);
        current->state = CLOSED;
        
        // Iterate over successors
        for ( auto succIt=current->outNeighbors->begin(); succIt!=current->outNeighbors->end(); succIt++ )
        {
            GridGraphVertex *neighbor = (*succIt);
            
            // Already closed? don't search again
            // Our cost function is monotonic
            if ( neighbor->state == CLOSED )
                continue;
            
            // Tentative score to assign to neighbor
            double g_score_tentative = current->g_score + Heuristic(current, neighbor);

            // Search again if not open or seems to be optimal by the heuristic
            if ( neighbor->state != OPEN || g_score_tentative < neighbor->g_score )
            {
                neighbor->cameFrom = current;
                neighbor->g_score = g_score_tentative;
                neighbor->f_score = neighbor->g_score + Heuristic(neighbor, goalNode);
                
                // Mark as open if not already marked
                // And add to open set
                neighbor->state = OPEN;
                openSet.push_back(neighbor);
            }
        }
    }
    
    // If we ever get here the open set is empty, and we're out of luck.
    // No path exists
    return false;
}


double AStarSearcher::Heuristic(GridGraphVertex *a, GridGraphVertex *b)
{
    // Coords in grid
    veci ca = a->coord;
    veci cb = b->coord;
    
    // Euclidean distance, Manhattan is also admissible but produces "unnatural" move pattern
    return (ca-cb).length();
}

void AStarSearcher::ReconstructPath(GridGraphVertex *node)
{
    // Found start?
    bool foundStart = false;
    
    GridGraphVertex *curr = node;
    while (!foundStart)
    {
        solution->push_back(curr);
        
        // Found start?
        if ( curr->coord == start )
            return;
    
        // Else get next
        curr = curr->cameFrom;
    }
}

void AStarSearcher::DumpSolution(string path)
{
    ofstream outfile;
    outfile.open(path.c_str());
    
    for ( int i=0; i<graph->sizey; i++ )
    {
        for ( int j=0; j<graph->sizex; j++ )
        {
            // Should use iterators but whatthefuckever
            GridGraphVertex *node = graph->vertices->at(j)->at(i);
            
            // Part of solution? (or part of the problem?)
            if ( std::find(solution->begin(), solution->end(), node) != solution->end() )
                outfile << "x";
            else if ( node->outNeighbors->size() == 0 )
                outfile << " ";
            else
                outfile << numberToString(node->outNeighbors->size());
        }
        outfile << "\n";
    }
    
    outfile.close();
}


