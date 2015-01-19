#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

/**
 * Constructs an empty UndirectedGraph with no vertices and no edges.
 */
UndirectedGraph::UndirectedGraph() {}

/**
 * Destructs an UndirectedGraph.
 */
UndirectedGraph::~UndirectedGraph() {
    std::unordered_map<std::string, Vertex*>::const_iterator it;
    for ( it = vertices.begin(); it != vertices.end(); ++it ) {
        delete it->second;
    }
}

/**
 * Insert an edge into the graph.
 */
void UndirectedGraph::addEdge( const std::string &from, const std::string &to,
                               unsigned int cost, unsigned int length ) {
    std::unordered_map<std::string, Vertex*>::const_iterator it;

    /**
     * If the vertex this edge originates from does not exist, creates it.
     */
    it = vertices.find( from );
    if ( it == vertices.end() ) {
        vertices.insert( make_pair( from, new Vertex( from ) ) );
    }

    /**
     * If the vertex this edge terminates to does not exist, creates it.
     */
    it = vertices.find( to );
    if ( it == vertices.end() ) {
        vertices.insert( make_pair( to, new Vertex( to ) ) );
    }

    /**
     * Add the edge.
     */
    vertices.at( from )->addEdge( vertices.at( to ), cost, length );
    vertices.at( to )->addEdge( vertices.at( from ), cost, length );
}

/**
 * Returns the total cost of all edges in the graph.
 */
unsigned int UndirectedGraph::totalEdgeCost() const {
    unsigned int temp = 0;
    std::unordered_map<std::string, Vertex*>::const_iterator it;
    for ( it = vertices.begin(); it != vertices.end(); ++it ) {
        temp = temp + it->second->totalEdgeCost();
    }
    return temp / 2;
}

/**
 * Removes all edges from the graph except those necessary to form
 * a minimum cost spanning tree of all vertices using Prim's algorithm.
 */
void UndirectedGraph::minSpanningTree() {
    std::vector<Edge> mstEdge;
    std::priority_queue< Edge, std::vector<Edge> > pq;
    std::unordered_map<std::string, Vertex*>::const_iterator it_1;
    std::unordered_map<std::string, Edge>::const_iterator it_2;
    std::vector<Edge>::const_iterator it_3;
    int trueNum = 0;
    int vNum = 0;

    /**
     * If the graph is empty, nothing need to do.
     */
    if ( vertices.begin() == vertices.end() ) ;

    else {
        /**
         * Sets all vertices' visited state false.
         */
        for ( it_1 = vertices.begin(); it_1 != vertices.end(); ++it_1 ) {
            it_1->second->setVisited( 0 );
            vNum += 1;
        }

        /**
         * Sets an arbitrary start vertex's visited state true.
         */
        vertices.begin()->second->setVisited( 1 );
        trueNum += 1;

        /**
         * Iterates through the adjacency list of the start vertex
         * and puts those edges in the priority queue.
         */
        for ( it_2 = vertices.begin()->second->getEdges().begin();
               it_2 != vertices.begin()->second->getEdges().end();
                                                         ++it_2 ) {
            pq.push( it_2->second );
        }

        /**
         * While the priority queue is not empty or
         * until the visited state of all vertices are true.
         */
        while ( pq.size() != 0 || trueNum != vNum ) {
            Edge popEdge( pq.top().getFrom(), pq.top().getTo(),
                          pq.top().getCost(), pq.top().getLength() );
            pq.pop();
            if ( popEdge.getTo()->wasVisited() == 1 ) {
                continue;
            }
            else {
                popEdge.getTo()->setVisited( 1 );
                trueNum += 1;
                mstEdge.push_back( popEdge );
                for( it_2 = popEdge.getTo()->getEdges().begin();
                      it_2 != popEdge.getTo()->getEdges().end();
                                                       ++it_2 ) {
                    if ( it_2->second.getTo()->wasVisited() == 0 ) {
                        pq.push( it_2->second );
                    }
                }
            }
        }

        /**
         * Removes all edges from the graph.
         */
        for ( it_1 = vertices.begin(); it_1 != vertices.end(); ++it_1 ) {
            it_1->second->clearEdges();
        }

        /**
         * Add the neccessary edges which form
         * the minimum cost spanning tree.
         */
        for ( it_3 = mstEdge.begin(); it_3 != mstEdge.end(); ++it_3 ) {
            this->addEdge( it_3->getFrom()->getName(),
                           it_3->getTo()->getName(),
                           it_3->getCost(), it_3->getLength() );
        }
    }
}

/**
 * Determines the combined distance from the given Vertex to all
 * other Vertices in the graph using Dijkstra's algorithm.
 */
unsigned int UndirectedGraph::totalDistance( const std::string &from ) {
    std::priority_queue< std::pair<Vertex*, unsigned int>,
            std::vector< std::pair<Vertex*, unsigned int> >,
                                 DijkstraVertexComparator > pq;
    std::unordered_map<std::string, Vertex*>::const_iterator it_1;
    std::unordered_map<std::string, Edge>::const_iterator it_2;
    std::pair<Vertex*, unsigned int> popPair;
    int trueNum = 0;
    int vNum = 0;
    unsigned int temp = 0;

    /**
     * Sets all vertices' distance infinity and visited state false.
     */
    for ( it_1 = vertices.begin(); it_1 != vertices.end(); ++it_1 ) {
        it_1->second->setDistance( UINT_MAX );
        it_1->second->setVisited( 0 );
        vNum += 1;
    }

    /**
     * Sets the start vertex's distance 0 and enqueue this vertex.
     */
    vertices.at( from )->setDistance( 0 );
    pq.push( std::make_pair( vertices.at( from ),
             vertices.at( from )->getDistance() ) );

    /**
     * While the priority queue is not empty or
     * until the visited state of all vertices are true.
     */
    while ( pq.size() != 0 || trueNum != vNum ) {
        popPair = pq.top();
        pq.pop();
        if ( popPair.first->wasVisited() == 1 ) {
            continue;
        }
        else {
            popPair.first->setVisited( 1 );
            trueNum += 1;
            for ( it_2 = popPair.first->getEdges().begin();
                   it_2 != popPair.first->getEdges().end();
                                                  ++it_2 ) {
                if ( vertices.at( it_2->first )->wasVisited() == 0 ) {
                    if ( popPair.second + it_2->second.getLength() <
                         vertices.at( it_2->first )->getDistance() ) {

                        vertices.at( it_2->first )->setDistance
                          ( popPair.second + it_2->second.getLength() );
                     }
                     pq.push( std::make_pair( vertices.at( it_2->first ),
                       vertices.at( it_2->first )->getDistance() ) );
                }
            }
        }
    }

    /**
     * Sums the distance from the given Vertex to all
     * other Vertices in the graph.
     */
    for ( it_1 = vertices.begin(); it_1 != vertices.end(); ++it_1 ) {
        temp = temp + it_1->second->getDistance();
    }
    return temp;
}

/**
 * Determines the combined distance from all Vertices to all other
 * Vertices in the graph.
 */
unsigned int UndirectedGraph::totalDistance() {
    unsigned int temp = 0;
    std::unordered_map<std::string, Vertex*>::const_iterator it;
    for ( it = vertices.begin(); it != vertices.end(); ++it ) {
        temp = temp + totalDistance( it->first );
    }
    return temp;
}

/**
 * Comparison function for use with Dijkstra's algorithm.
 * Returns true if left's weight when it was inserted into the queue is
 * higher than right's weight when it was inserted into the queue.
 */
bool UndirectedGraph::DijkstraVertexComparator::operator()
         ( const std::pair<Vertex*, unsigned int> &left,
           const std::pair<Vertex*, unsigned int> &right ) {
    if ( left.second > right.second ) {
        return 1;
    }
    else {
        return 0;
    }
}
