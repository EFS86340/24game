//
// Created by wang on 8/18/17.
//

/*
 * 2.1  compile-time assertions
 *
 */

/*!
 *  it is illegal when an array gets its length as zero.
 */
#define STATIC_CHECK(expr) {    char unamed[(expr) ? 1 : 0];    }

template <class To, class From>
To safe_reinterpret_cast(From  from) {
    STATIC_CHECK(sizeof(To) < sizeof(from));
    return reinterpret_cast<To>(from);
};

// better version
template <bool> struct CompileTimeError;

template<> struct CompileTimeError<true> { };

#define STATIC_CHECKv2(expr) \
    (CompileTimeError<(expr) != 0>())

/*
 * version support error msg
 */
template <bool>
struct CompileTimeChecker {
    CompileTimeChecker(...);
};

template <> struct CompileTimeChecker<false> { };

#define STATIC_CHECKERv3(expr, msg) \
    { \
        class ERROR_##msg {}; \
        (void)sizeof(CompileTimeChecker<(expr)>(ERROR_##msg())); \
    }

template <class To, class From>
To safe_reinterpret_castv3(From from) {
    STATIC_CHECKERv3(sizeof(From) < sizeof(To),
        Destination_Type_Too_Narrow);
    return reinterpret_cast<To>(from);
};

/*
 * 2.2 Partial Template Specialization
 *
 */

template <class Window,class Controller>
class Widget{

};

//   