#include "node.h"

#include <iostream>

Node::Node(Eigen::Vector3d y, uint32_t id, uint32_t depth)
    : id(id), depth(depth)
{
    target.init(y);
}

Node::Node(Node node, Eigen::Vector3d y, uint32_t id, uint32_t depth)
    : id(id), depth(depth)
{
    target = node.get_target();

    target.correct(y, target);
}

Node::~Node()
{

}

Target_Hypothesis Node::get_target(void)
{
    return target;
}


uint32_t Node::get_id(void)
{
    return id;
}

void Node::add_prev(uint32_t id)
{
    prev = id;
}

void Node::add_next(uint32_t id)
{
    next.push_back(id);
}

uint32_t & Node::get_prev(void)
{
    return prev;
}

std::vector<uint32_t> & Node::get_next(void)
{
    return next;
}


