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

#include "Location.h"

using namespace std;

// The domain of the distance function is _integers_, that is the number of steps we need to walk to get somewhere.
// This is different from using Euclidean distance (direct line)
// This shouldn't really make much difference
typedef unsigned int dist;

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

// Specific data types we use
typedef boost::unordered_set<vertex_descriptor, vertex_hash> vertex_set;
typedef boost::vertex_subset_complement_filter<grid, vertex_set>::type
filtered_grid;
typedef boost::unordered_map<vertex_descriptor,vertex_descriptor,vertex_hash> pred_map;
typedef boost::unordered_map<vertex_descriptor,dist,vertex_hash> dist_map;


// Abstracted representation of a graph to search and methods to do it using A*
// For example, dungeons construct an instance of this for pathfinding
class AStarSearcher
{
public:
    // Make from world or object
    // TODO
    AStarSearcher(Location *_loc);
    ~AStarSearcher();
    
    // TODO
    vertex_descriptor source() const { return vertex(0, m_grid);}
    vertex_descriptor goal() const { return vertex(num_vertices(m_grid)-1, m_grid);}
    
private:
    // Create the underlying rank-2 grid with the specified dimensions.
    grid create_grid(size_t x, size_t y);

    // Filter the barrier vertices out of the underlying grid.
    filtered_grid create_barrier_grid(Location *loc);
    
    bool solve();
    bool solved();  // solution found?
    
    // Is vertex part of shortest path?
    bool solution_contains(vertex_descriptor u) const
    {
        return m_solution.find(u) != m_solution.end();
    }
    
    // The grid underlying the maze
    grid m_grid;
    // The underlying maze grid with barrier vertices filtered out
    filtered_grid m_barrier_grid;
    // The barriers in the maze
    vertex_set m_barriers;
    // The vertices on a solution path through the maze
    vertex_set m_solution;
    // The length of the solution path
    dist m_solution_length;
    
    // Tile-containing object we are building search graph for
    Location *location;
};

// Heuristic for the distance function
// This calculates the Manhattan distance (taxicab metric) between a vertex and a goal
// vertex.
class heuristic:
public boost::astar_heuristic<filtered_grid, dist>
{
public:
    heuristic(vertex_descriptor goal):m_goal(goal) {};
    
    dist operator()(vertex_descriptor v)
    {
        return abs((int)(m_goal[0] - v[0])) + abs((int)(m_goal[1] - v[1]));
    }
    
private:
    vertex_descriptor m_goal;
};

// Something for Boost to throw when a solution is found
// It doesn't need any structure
struct found_goal {};

// Visitor class for travering nodes
// Throw found_goal to signal goal found for termination
struct astar_goal_visitor : public boost::default_astar_visitor
{
    astar_goal_visitor(vertex_descriptor goal) : m_goal(goal) {};
    
    void examine_vertex(vertex_descriptor u, const filtered_grid&)
    {
        if (u == m_goal)
            throw found_goal();
    }
    
private:
    vertex_descriptor m_goal;
};

#endif /* defined(__forogue__AStarSearcher__) */
