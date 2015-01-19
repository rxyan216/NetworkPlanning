#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "UndirectedGraph.hpp"

/**
 * Entry point into the netplan program.
 *
 * -Reads a file from the filesystem according to the specification for
 *  PA3, creating an UndirectedGraph.
 * -Finds the total cost & ping time of the graph as presented in the input
 *  file.
 * -Determines the minimum cost graph from the original graph.
 * -Finds the total cost & ping time of the minimum cost graph.
 * -Finds the change of cost & ping time from the original graph to the
 *  minimum cost graph.
 * -Prints the results to stdout.
 *
 * Usage:
 *   ./netplan infile
 *
 */
int main(int argc, char **argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " infile" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream in(argv[1]);
    if (!in) {
        std::cerr << "Unable to open file for reading." << std::endl;
        return EXIT_FAILURE;
    }

    UndirectedGraph g;
    UndirectedGraph mst;
    std::string s1, s2;
    unsigned int cost, length;
    unsigned int result_1, result_2, result_3, result_4, result_5, result_6;

    /**
     * Reads the file and constructs the grapsh.
     */
    while ( in.good() ) {
        in>>s1>>s2>>cost>>length;
        if ( !in.good() ) break;
        g.addEdge( s1, s2, cost, length );
    }

    /**
     * Closes the ifstream.
     */
    in.close();

    /**
     * Calculates the results.
     */
    result_1 = g.totalEdgeCost();
    result_4 = g.totalDistance();

    g.minSpanningTree();
    result_2 = g.totalEdgeCost();
    result_5 = g.totalDistance();

    result_3 = result_1 - result_2;
    result_6 = result_5 - result_4;

    /**
     * Outputs the results.
     */
    std::cout<<result_1<<std::endl;
    std::cout<<result_2<<std::endl;
    std::cout<<result_3<<std::endl;
    std::cout<<result_4<<std::endl;
    std::cout<<result_5<<std::endl;
    std::cout<<result_6<<std::endl;

    return EXIT_SUCCESS;
}
