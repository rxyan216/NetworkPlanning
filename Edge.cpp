#include "Edge.hpp"

/**
 * Constructs an Edge from the given parameters.
 */
Edge::Edge( Vertex *from, Vertex *to,
            unsigned int cost,
            unsigned int length ) {
    this->from = from;
    this->to = to;
    this->cost = cost;
    this->length = length;
}

/**
 * Returns a pointer to the Vertex that
 * this Edge originates from.
 */
Vertex *Edge::getFrom() const {
    return from;
}

/**
 * Returns a pointer to the Vertex that
 * this Edge terminates at.
 */
Vertex *Edge::getTo() const {
    return to;
}

/**
 * Sets the cost of this Edge.
 */
void Edge::setCost( unsigned int cost ) {
    this->cost = cost;
}

/**
 * Returns the cost of this Edge.
 */
unsigned int Edge::getCost() const {
    return cost;
}

/**
 * Sets the length of this Edge.
 */
void Edge::setLength( unsigned int length ) {
    this->length = length;
}

/**
 * Returns the length of this Edge.
 */
unsigned int Edge::getLength() const {
    return length;
}

/**
 * Compares this Edge to another Edge.
 * Return true if this Edge's cost is
 * than right's cost.
 */
bool Edge::operator<( const Edge &right ) const {
    if ( this->cost > right.cost ) {
        return 1;
    }
    else {
        return 0;
    }
}
