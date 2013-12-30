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
                int index = y*sy+sx;
                
                // get vertex descriptor
                vertex_descriptor u = vertex(index,m_grid);
                
                // Add to barrier vertex set
                m_barriers.insert(u);
            }
        }
    }

    return boost::make_vertex_subset_complement_filter(m_grid, m_barriers);
}