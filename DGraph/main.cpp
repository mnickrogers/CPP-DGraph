//
//  main.cpp
//  DGraph
//
//  Created by Nicholas Rogers on 7/13/16.
//  Copyright © 2016 Nicholas Rogers. All rights reserved.
//

#include <iostream>
#include "DGraph.h"

int main(int argc, const char * argv[])
{
    DGraph<std::string> graph;
    
    graph.addEdge("Nick", "Steve", "friends");
    graph.addEdge("Steve", "James", "friends");
    graph.addEdge("James", "Aldo", "friends");
    
    auto result = graph.path("Nick", "Aldo");
    
    for (auto e: result)
        std::cout << e << std::endl;
    
    return 0;
}
