//
// Created by mbero on 18/07/2025.
//

#ifndef BRACKETING_HPP
#define BRACKETING_HPP
#include "base_elements.hpp"

namespace Optim::bracketing {
    struct IntervalType {
        double minimum;
        double maximum;
    };

    inline auto bracketing_minimum(const base::UnaryFuncType& func, double x, double s, double k = 2.0) -> IntervalType {
        auto a = x ; double y_a = func(x);
        auto b = a + s ; double y_b = func(a + s);

        if (y_b > y_a) {
            a = b ; b = a;
            y_a = y_b ; y_b = y_a;
            s = -s;
        }
        while (true) {
            auto c = b + s ; double y_c = func(b + s);
            if (y_c > y_b) {
                return  a > c ? IntervalType{.maximum = a, .minimum = c} : IntervalType{.minimum = c, .maximum = a} ;
            }
            a = b;
            y_a = y_b ;
            b = c;
            y_b = y_c ;
        }

    }
}
#endif //BRACKETING_HPP
