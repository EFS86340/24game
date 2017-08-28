//
// Created by wang on 8/11/17.
//

#ifndef INC_24GAME_GAME_H
#define INC_24GAME_GAME_H


template <typename Arg, typename Result>
struct unary_function {
    typedef Arg argument_type;
    typedef Result result_type;
};

template <typename Arg1, typename Arg2, typename Result>
struct binary_function {
    typedef Arg1 first_argument_type;
    typedef Arg2 second_argument_type;
    typedef Result result_type;
};

template <typename T>
struct Nor : public unary_function<T, T> {
    T operator()(const T& x) const {
        return ~x;  // TODO class T requires override ~ operator
    }
};

template <typename T>
struct Plus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x + y;
    }
};

template <typename T>
struct Minus : public binary_function<T, T, T> {
    T operator()(const T& x, const T& y) const {
        return x - y;
    }
};

//  test operators above

/*
 * Some operator-deduce of operator nor:
 * Does it work different from when it is placed among the expressions ?
 */

/*
 *  N stand for number between A and K
 *  O stand for oprations
 *  thus there are five formats: 1.NNNNOOO 2.NNONNOO 3.NNONONO 4.NNNOONO 5.NNNONOO   (postfix expression)
 *  we try each number, each opration and each format, quit a combination process when succeeded in one
 *  trial at once
 */

namespace Game {

    /*
     *  templates intends for single data type, int or float
     */

    /*
     *  As for more than 13 alternatives operators, can we make it typelist-like.
     *  and problem is operand maybe more than 1, even 3.
     *
     */
    
}



#endif //INC_24GAME_GAME_H