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
#include <zconf.h>

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

class ModalDialog {};
class MyController {};

template <>
class Widget<ModalDialog, MyController> {

};

/*
 * 2.3  Local Classes
 *
 */

void Fun() {
    class Local {

    };
}

/*
 *  cannot define static member within a local class, nor visit a non-static local var.
 *  but local class can be used within template functions.
 */

class Interface {
public:
    virtual void Fun() = 0;

};

template <class T, class P>
Interface* MakeAdapter(const T& obj, const P& arg) {
    class Local : public Interface {
        Local(const T& obj, const P& arg)
                : obj_(obj), arg_(arg) { }
        virtual void Fun() {
            obj_.Call(arg_);
        }

    private:
        T obj_;
        P arg_;
    };
    return new Local(obj, arg);
};

/*
 * 2.4  Mapping Integral Constants to Types
 *
 */
template <int v>
struct Int2Type {
    enum {  value = v   };
};

// init version
template <typename T, bool isPolymorphic>
class NiftyContainer {

    void DoSomething() {
        // ...
        if(isPolymorphic) {
            // ...
        }
        else {
            // ...
        }
    }
};  // compiler will work with every branch of if-else or switch sentences

//better
template <typename T, bool isPolymorphic>
class NiftyContainerv2 {
private:
    void DoSomething(T* pObj, Int2Type<true>) {

    }

    void DoSomething(T* pObj, Int2Type<false>) {

    }

public:
    void DoSometing(T* pObj) {
        DoSomething(pObj, Int2Type<isPolymorphic>());
    }
};
// however, compiler won't work with a template function which is never used.

// compile-time dispatch

/*
 * 2.5  Type-to-Type Mapping
 *
 */

// usually there does not exists specialization for template function.
template <class T, class U>
T* Create(const U& arg) {
    return new T(arg);
};

// Illegal code
template <class U>
Widget* Create<Widget, U>(const U& arg) {
    //return new Widget(arg, -1);
};

// correct code using override but costs extra spense
template <class T, class U>
T* Create(const U& arg, T) {
    return new T(arg);
};

template <class U>
Widget* Create(const U& arg, Widget) {
    //return new Widget(arg, -1);
}

// using Type2Type
template <typename T>
struct Type2Type {
    typedef T OriginalType;
};

template <class T, class U>
T* Create(const T& arg, Type2Type<T>) {
    return new T(arg);
};

template <class U>
Widget* Create(const U& arg, Type2Type<Widget>) {
    //return new Widget(arg, -1);
}

class String {
    explicit String(char* p) : _p(p) {   };
    explicit String(char str) : _p(&str) {  };
private:
    char* _p;
};

//use Create()
String* pStr = Create("Hello", Type2Type<String>());
// Clion warning: class Type2Type<String> is not compatible with class String TODO

/*
 * 2.6  Type Selection
 *
 */

/*
 *  for polymorphic type, store its pointer, and for non-poly, store entity more efficiently.
 */

// traits class template
template <typename T, bool isPolymorphic>
struct NiftyContainerValueTraits {
    typedef T* ValueType;
};

template <typename T>
struct NiftyContainerValueTraits<T, false> {
    typedef T ValueType;
};

template <typename T, bool isPolymorphic>
class NiftyContainerv3 {
    typedef NiftyContainerValueTraits<T, isPolymorphic> Traits;
    typedef typename Traits::ValueType ValueType;
};


/*
 * 2.7  Compile-time Convertibility and Inheritance
 *
 */

// discover inheritance relativity










/*
 * 2.10 Type Traits
 *
 */

class NullType;     // a placeholder type

// whether T is a pointer or not
template <typename T>
class TypeTraits {
private:
    template <class U> struct PointerTraits {
        enum {  result = false  };
        typedef NullType PointeeType;
    };

    template <class U> struct PointerTraits<U*> {
        enum {  result = true   };
        typedef U PointeeType;
    };


    template <class U> struct PToMTraits {
        enum {  result = false  };
    };

    template <class U, class V> struct PToMTraits<U V::*> { // TODO grammar puzzle
        enum {  result = true   };
    };
public:
    enum {  isPointer = PointerTraits<T>::result    };
    enum {  isMemberPointer = PToMTraits<T>::result };
    typedef PointerTraits<T>::PointeeType PointeeType;
};


























