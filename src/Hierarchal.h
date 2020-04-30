#pragma once

#include <memory>
#include <vector>

template<typename TNode>
class Hierarchal
{
public:
    virtual std::shared_ptr<TNode> getParent() = 0;
    virtual std::vector<std::shared_ptr<TNode>> getChildren() = 0;
};