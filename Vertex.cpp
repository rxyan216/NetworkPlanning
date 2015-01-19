#include "Vertex.hpp"

/**
 * Initialize the Vertex with the given name.
 */
Vertex::Vertex( const std::string &name) {
    this->name = name;
}

/**
 * Add an edge to this Vertex.
 */
bool Vertex::addEdge( Vertex *to, unsigned int cost, unsigned int length ) {

    std::unordered_map<std::string, Edge>::const_iterator it = edges.find( to->name );

    /**
     * If this edge already exists, updates the cost of length of the edge.
     */
    if ( it != edges.end() ) {
        edges.at(to->name).setCost( cost );
        edges.at(to->name).setLength( length );
        return 0;
    }

    /**
     * Otherwise, creates a new edge.
     */
    else {
        edges.insert( make_pair( to->name, Edge( this, to, cost, length ) ) );
        return 1;
    }
}

/**
 * Returns the Vertex's name.
 */
const std::string &Vertex::getName() const {
    return name;
}

/**
 * Gets the Vertex's distance value.
 */
unsigned int Vertex::getDistance() const {
    return distance;
}

/**
 * Sets the Vertex's distance value.
 */
void Vertex::setDistance( unsigned int distance ) {
    this->distance = distance;
}

/**
 * Gets the Vertex's visited state.
 */
bool Vertex::wasVisited() const {
    return visited;
}

/**
 * Sets the Vertex's visited state.
 */
void Vertex::setVisited( bool visited ) {
    this->visited = visited;
}

/**
 * Clears all edges from this Vertex.
 */
void Vertex::clearEdges() {
    edges.clear();
}

/**
 * Gets total cost of all edges originating from this Vertex.
 */
unsigned int Vertex::totalEdgeCost() const {
    unsigned int temp = 0;
    std::unordered_map<std::string, Edge>::const_iterator it;
    for ( it = edges.begin(); it != edges.end(); ++it ) {
        temp = temp + it->second.getCost();
    }
    return temp;
}

/**
 * Returns a reference to the internal map of Edges.
 */
const std::unordered_map<std::string, Edge> &Vertex::getEdges() const {
    return edges;
}
