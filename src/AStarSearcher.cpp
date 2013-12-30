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

AStarSearcher::AStarSearcher(Location *_loc) : m_grid(create_grid(_loc->size.x,_loc->size.y)), m_barrier_grid(create_barrier_grid(_loc))
{
    location = _loc;
}

AStarSearcher::~AStarSearcher()
{
}

// Initialise grid structure based on dimensions of tilemap
grid AStarSearcher::create_grid(size_t x, size_t y)
{
    boost::array<size_t, 2> lengths = { {x, y} };
    return grid(lengths);
}

filtered_grid AStarSearcher::create_barrier_grid(Location *loc)
{
    // Iterate over all tiles, add inaccessible to barrier vertex set
    int sx = loc->size.x;
    int sy = loc->size.y;
    for ( int x=0; x<sx; ++x)
    {
        for ( int y=0; y<sy; ++y )
        {
            Tile *tile = loc->GetTile(x,y);
            
            if ( tile ->clipMask == false )
            {
                // Convert to vertex index
                int index = y*sy+x;
                
                // get vertex descriptor
                vertex_descriptor u = vertex(index,m_grid);
                
                // Add to barrier vertex set
                m_barriers.insert(u);
            }
        }
    }

    return boost::make_vertex_subset_complement_filter(m_grid, m_barriers);
}

bool AStarSearcher::solve(veci start, veci goal)
{
    // Ineligible start/goal? No path can exist then
    if ( location->GetTile(start.x,start.y)->clipMask == false ||
         location->GetTile(goal.x,goal.y)->clipMask == false )
        return false;
    
    // Convert start/goal coords to vertex descriptors
    int s_index = start.y*location->size.y + start.x;
    int g_index = goal.y*location->size.y + goal.x;
    
    vertex_descriptor s = vertex(s_index, m_grid);
    vertex_descriptor g = vertex(g_index, m_grid);
    
    // Clear old solution
    m_solution.clear();
    m_solution_length = 0;
    
    // Uniform weight map, all edges have weight 1
    boost::static_property_map<dist> weight(1);
    
    // Predecessors of nodes
    pred_map predecessor;
    boost::associative_property_map<pred_map> pred_pmap(predecessor);
    
    // Distances for nodes based on the heuristic
    dist_map distance;
    boost::associative_property_map<dist_map> dist_pmap(distance);
    
    // Instances of heuristic and visitor
    manhattan_heuristic heuristic(g);
    astar_goal_visitor visitor(g);
    
    // Attempt search, catch struct to check if found
    try {
        astar_search(m_barrier_grid, s, heuristic,
                     boost::weight_map(weight).
                     predecessor_map(pred_pmap).
                     distance_map(dist_pmap).
                     visitor(visitor) );
    } catch(found_goal fg) {
        // Walk backwards from the goal through the predecessor chain adding
        // vertices to the solution path.
        for (vertex_descriptor u = g; u != s; u = predecessor[u])
            m_solution.insert(u);
        m_solution.insert(s);
        m_solution_length = distance[g];
        return true;
    }
    
    // Nope, didn't work.
    return false;
}

bool AStarSearcher::solved()
{
    // Any vertices in solution set?
    return !m_solution.empty();
}

void AStarSearcher::DumpSolution(string path)
{
    ofstream outfile;
    outfile.open(path.c_str());
    
    for ( int y=0; y<location->size.y; y++ )
    {
        for ( int x=0; x<location->size.x; x++ )
        {
            // Passable?
            bool mask = location->GetTile(x,y)->clipMask;
            
            vertex_descriptor v = vertex(y*location->size.y+x, m_grid);
            
            // Part of path?
            if ( solution_contains(v) )
            {
                outfile << "o";
            }
            else if ( mask )
                outfile << ".";
            else
                outfile << "x";
        }
        
        outfile << "\n";
    }
    
    outfile.close();
}







