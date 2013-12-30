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

#include <iostream>

#include <boost/graph/astar_search.hpp>
#include <boost/graph/filtered_graph.hpp>
#include <boost/graph/grid_graph.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/unordered_map.hpp>
#include <boost/unordered_set.hpp>
#include <ctime>
#include <iostream>

using namespace std;

// typedef Boost types for this particular problem
typedef boost::grid_graph<2> grid;
typedef boost::graph_traits<grid>::vertex_descriptor vertex_descriptor;
typedef boost::graph_traits<grid>::vertices_size_type vertices_size_type;

// Hashing of vertices
struct vertex_hash:unary_function<vertex_descriptor, size_t> {
    size_t operator()(vertex_descriptor const& u) const {
        size_t seed = 0;
        boost::hash_combine(seed, u[0]);
        boost::hash_combine(seed, u[1]);
        return seed;
    }
};

// Abstracted representation of a graph to search and methods to do it using A*
// For example, dungeons construct an instance of this for pathfinding
class AStarSearcher
{
public:
    // Make from world or object
    // TODO
    AStarSearcher();
    ~AStarSearcher();
    
private:
};

#endif /* defined(__forogue__AStarSearcher__) */
