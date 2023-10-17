#include "node.h"

Node::Node(Eigen::Vector3d y_, uint32_t target_id_, uint32_t measurement_id_, Node * prev_)
    : target_id(target_id), measurement_id(measurement_id), target(y_), prev(prev)
{
    next.push_back(nullptr);

}

Node::~Node()
{
}
