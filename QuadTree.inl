#include "QuadTree.h"
#include <memory>
#include <iostream>
#include <vector>

namespace utec {
    namespace spatial {

        template<typename Node, typename Rectangle, typename Point>
        QuadTree<Node, Rectangle, Point>::QuadTree() {
            this->root=nullptr;
        }

        template<typename Node, typename Rectangle, typename Point>
        void QuadTree<Node, Rectangle, Point>::insert(Point new_point) {
            std::shared_ptr<Node>& target = search(new_point, this->root);
            if(target==nullptr){
                target=std::make_shared<Node>(new_point);
            }
        }

        template<typename Node, typename Rectangle, typename Point>
        std::shared_ptr<Node>& QuadTree<Node, Rectangle, Point>::search(Point target, std::shared_ptr<Node>& node) {
            if(node == nullptr){
                return node; //not found
            } else if(node->get_point() == target){
                return node;
            }
            
            auto cur_point = node->get_point();

            const int x=0, y=1;

            if(target.get(x) < cur_point.get(x)){
                if(target.get(y) > cur_point.get(y))
                    return search(target, node->NW());
                else
                    return search(target, node->SW());
            }else{
                if(target.get(y) > cur_point.get(y))
                    return search(target, node->NE());
                else
                    return search(target, node->SE());
            }
        }

        template<typename Node, typename Rectangle, typename Point>
        std::shared_ptr<Node> QuadTree<Node, Rectangle, Point>::search(Point target) {
            return search(target, this->root);
        }

        template<typename Node, typename Rectangle, typename Point>
        std::vector<Point> QuadTree<Node, Rectangle, Point>::range (Rectangle region, std::shared_ptr<Node>& node) {
            std::vector<Point> result;
            const int x=0, y=1;
            if (node == nullptr) {
                return result;
            }
            if (region.is_in(node->get_point())) {
                result.push_back(node->get_point());
            }
            if (region._max.get(x) >= node->get_point().get(x) && region._min.get(y) <= node->get_point().get(y)) {
                auto resp = range(region, node->SE());
                for (auto& j : resp)
                    result.push_back(j);
            }
            if (region._min.get(x) <= node->get_point().get(x) && region._max.get(y) >= node->get_point().get(y)) {
                auto resp = range(region, node->NW());
                for (auto& j : resp)
                    result.push_back(j);
            }
            if (region._max.get(x) >= node->get_point().get(x) && region._max.get(y) >= node->get_point().get(y)) {
                auto resp = range(region, node->NE());
                for (auto& j : resp)
                    result.push_back(j);
            }
            if (region._min.get(x) <= node->get_point().get(x) && region._min.get(y) <= node->get_point().get(y)) {
                auto resp = range(region, node->SW());
                for (auto& j : resp)
                    result.push_back(j);
            }   
            return result;
        }

        template<typename Node, typename Rectangle, typename Point>
        std::vector<Point> QuadTree<Node, Rectangle, Point>::range (Rectangle region) {
            return range(region, this->root);
        }

        template<typename Node, typename Rectangle, typename Point>
        Point QuadTree<Node, Rectangle, Point>::nearest_neighbor(Point reference) {
            // TODO
        }
    } //spatial
} //utec
