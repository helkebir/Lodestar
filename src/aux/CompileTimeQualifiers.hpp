//
// Created by Hamza El-Kebir on 5/17/21.
//

#ifndef LODESTAR_COMPILETIMEQUALIFIERS_HPP
#define LODESTAR_COMPILETIMEQUALIFIERS_HPP

#define LS_IS_DYNAMIC_DEFAULT(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0))>::type* = nullptr

#define LS_ENABLE_IF_DYNAMIC_DEFAULT(TSTATE, TINPUT, TOUTPUT) template <typename std::enable_if<((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0)), int>::type = 0>

#define LS_ENABLE_IF_DYNAMIC(TSTATE, TINPUT, TOUTPUT) template <typename std::enable_if<((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0)), int>::type>

#define IF_DYNAMIC_RETURN(TSTATE, TINPUT, TOUTPUT, RETTYPE) template <int T_##TSTATE = TSTATE, int T_##TINPUT = TINPUT, int T_##TOUTPUT = TOUTPUT> typename std::enable_if<((T_##TSTATE < 0) || (T_##TINPUT < 0) || (T_##TOUTPUT < 0)), RETTYPE>::type

#define IF_STATIC_RETURN(TSTATE, TINPUT, TOUTPUT, RETTYPE) template <int T_##TSTATE = TSTATE, int T_##TINPUT = TINPUT, int T_##TOUTPUT = TOUTPUT> typename std::enable_if<!((T_##TSTATE < 0) || (T_##TINPUT < 0) || (T_##TOUTPUT < 0)), RETTYPE>::type

#define LS_IS_DYNAMIC(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0))>::type*

#define LS_IS_STATIC_DEFAULT(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<!((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0))>::type* = nullptr

#define LS_IS_STATIC(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<!((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0))>::type*

#define LS_ENABLE_IF_STATIC_DEFAULT(TSTATE, TINPUT, TOUTPUT) template <typename std::enable_if<!((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0)), int>::type = 0>

#define LS_ENABLE_IF_STATIC(TSTATE, TINPUT, TOUTPUT) template <typename std::enable_if<!((TSTATE < 0) || (TINPUT < 0) || (TOUTPUT < 0)), int>::type>

//#define LS_IS_STATIC_DEFAULT(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<((TSTATE >= 0) && (TINPUT >= 0) && (TOUTPUT >= 0))>::type* = nullptr
//
//#define LS_IS_STATIC(TSTATE, TINPUT, TOUTPUT) typename std::enable_if<((TSTATE >= 0) && (TINPUT >= 0) && (TOUTPUT >= 0))>::type*

template<class T>
constexpr T &Kmin(T a, T b)
{
    return (a > b ? b : a);
}

template<class T>
constexpr T &Kmax(const T &a, const T &b)
{
    return (int &) (a >= b ? a : b);
}

template<class T>
constexpr T Kmax2(const T a, const T b, const T c)
{
    return (a >= b ? a : c);
}

#define LS_STATIC_UNLESS_DYNAMIC(DIM) Kmax(-1, DIM)

#define LS_STATIC_UNLESS_DYNAMIC_VAL(DIM, VAL) Kmax2(-1, DIM, VAL)

#endif //LODESTAR_COMPILETIMEQUALIFIERS_HPP
