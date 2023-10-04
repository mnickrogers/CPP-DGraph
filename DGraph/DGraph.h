//
//  DGraph.h
//  DGraph
//
//  Created by Nicholas Rogers on 7/13/16.
//  Copyright © 2016 Nicholas Rogers. All rights reserved.
//

#ifndef DGraph_h
#define DGraph_h

#include <cstdlib>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#include <algorithm>

template <class T>
class DGraph
{
public:
    
    typedef std::string EdgeType;
    
    DGraph()
    {
        vertices = std::unordered_set<T>();
        edges = std::unordered_map<EdgeType, std::unordered_map<T, std::unordered_set<T>>>();
    }
    
    void addVertex(T target) const
    {
        vertices.insert(target);
    }
    
    void addEdge(T target1, T target2, EdgeType edgeName, bool isBidirectional = false)
    {
        if (vertices.find(target1) == vertices.end())
            vertices.insert(target1);
        if (vertices.find(target2) == vertices.end())
            vertices.insert(target2);
        
        edges[edgeName][target1].insert(target2);
        if (isBidirectional)
            edges[edgeName][target2].insert(target1);
    }
    
    const std::unordered_set<T> connectedNodes(T target, EdgeType edgeName = EdgeType())
    {
        std::unordered_set<T> neighbors;
        
        if (edgeName.empty())
        {
            for (auto edg: edges)
                neighbors.insert(edg.second[target].begin(), edg.second[target].end());
        }
        else
        {
            neighbors = edges[edgeName][target];
        }
        
        return neighbors;
    }
    
    /// Get a valid path from a source edge to another edge. This does not guarantee the shortest path.
    const std::vector<T> path(T start, T end, EdgeType edgeName = EdgeType())
    {
        std::queue<T> q;
        std::unordered_map<T, bool> visited;
        std::unordered_map<T, T> parents;
        std::vector<T> path;
        
        q.push(start);
        
        while (!q.empty())
        {
            T front = q.front();
            q.pop();
            
            if (front == end)
                break;
            
            if (edgeName.empty())
            {
                for (auto edg: edges)
                {
                    if (edg.second.find(front) != edg.second.end())
                    {
                        for (auto vertex: edg.second[front])
                        {
                            if (!visited[vertex])
                            {
                                visited[vertex] = true;
                                q.push(vertex);
                                parents[vertex] = front;
                            }
                        }
                    }
                }
            }
            else
            {
                for (auto vertex: edges[edgeName][front])
                {
                    if (visited[vertex] == false)
                    {
                        visited[vertex] = true;
                        q.push(vertex);
                        parents[vertex] = front;
                    }
                }
            }
        }
        
        int count(0);
        T parent = end;
        while (parent != start && count < parents.size())
        {
            if (parent != end)
                path.push_back(parent);
            
            parent = parents[parent];
            count++;
        }
        
        // There is no path.
        if (count > parents.size())
            return std::vector<T>();
        
        path.push_back(start);
        path.insert(path.begin(), end);
        
        std::reverse(path.begin(), path.end());
        
        return path;
    }
    
private:
    
    std::unordered_set<T>                                                       vertices;
    std::unordered_map<EdgeType, std::unordered_map<T, std::unordered_set<T>>>  edges;
    
};

#endif /* DGraph_h */
