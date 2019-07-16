#pragma once

#include <ose/typedef.h>

namespace ose::memory {

    // struct NodeTraits
    // {
    //     using Node
    //     using NodePtr
    //     using ConstNodePtr

    //     static NodePtr  getNext(ConstNodePtr n) { return n->next; }
    //     static void     setNext(NodePtr n, NodePtr next) { n->next = next; }
    // };

    template<class NodeTraits>
    struct SListAlgorithms
    {
        using Node = typename NodeTraits::Node;
        using NodePtr = typename NodeTraits::NodePtr;
        using ConstNodePtr = typename NodeTraits::ConstNodePtr;

        inline static void init(NodePtr node)
        {
            NodeTraits::setNext(node, NodePtr{});
        }

        inline static void linkAfter(NodePtr prevNode, NodePtr thisNode)
        {
            NodeTraits::setNext(thisNode, NodeTraits::getNext(prevNode));
            NodeTraits::setNext(prevNode, thisNode);
        }

        inline static void unlinkAfter(NodePtr prevNode)
        {
            ConstNodePtr thisNode = NodeTraits::getNext(prevNode);
            NodeTraits::setNext(prevNode, NodeTraits::getNext(thisNode));
        }

        inline static std::size_t count(ConstNodePtr node)
        {
            std::size_t count{ 0u };
            while(node)
            {
                ++count;
                node = NodeTraits::getNext(node);
            }

            return count;
        }
    };

}