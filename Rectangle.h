#pragma once

namespace utec {
    
    namespace spatial {

        template<typename Point>
        struct Rectangle{
            Rectangle(Point min, Point max):_min(min),_max(max){}
            Point _min;
            Point _max;
            bool is_in(Point p) {
                const int x=0, y=1;
                if (p.get(x) <= _max.get(x) && p.get(x) >= _min.get(x) && p.get(y) <= _max.get(y) && p.get(y) >= _min.get(y)) {
                    return true;
                }
                return false;
            }
        };

    } //spatial

} //utec