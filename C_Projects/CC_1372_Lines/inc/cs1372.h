// Various subroutines, templates and macros needed for CS1372
// George F. Riley, Georgia Tech, Summer 2008

#include <iostream>

// Templated PrintLn (print line) functions
template <typename T1>
void PrintLn(T1 t1)
{
  std::cout << t1 << std::endl;
}

template <typename T1, typename T2>
void PrintLn(T1 t1, T2 t2)
{
  std::cout << t1 <<  t2 << std::endl;
}

template <typename T1, typename T2, typename T3>
  void PrintLn(T1 t1, T2 t2, T3 t3)
{
  std::cout << t1 << t2 << t3 << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4>
  void PrintLn(T1 t1, T2 t2, T3 t3, T4 t4)
{
  std::cout << t1 << t2 << t3 <<  t4 << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void PrintLn(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6>
  void PrintLn(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6 << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7>
  void PrintLn(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6 << t7 << std::endl;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8>
  void PrintLn(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6 << t7 << t8 << std::endl;
}

// Templated Print (print) functions
// Same as PrintLn, but no end of line at the end
template <typename T1>
void Print(T1 t1)
{
  std::cout << t1;
}

template <typename T1, typename T2>
void Print(T1 t1, T2 t2)
{
  std::cout << t1 <<  t2;
}

template <typename T1, typename T2, typename T3>
  void Print(T1 t1, T2 t2, T3 t3)
{
  std::cout << t1 << t2 << t3;
}

template <typename T1, typename T2, typename T3, typename T4>
  void Print(T1 t1, T2 t2, T3 t3, T4 t4)
{
  std::cout << t1 << t2 << t3 <<  t4;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5>
  void Print(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6>
  void Print(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7>
  void Print(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6 << t7;
}

template <typename T1, typename T2, typename T3, typename T4, typename T5,
          typename T6, typename T7, typename T8>
  void Print(T1 t1, T2 t2, T3 t3, T4 t4, T5 t5, T6 t6, T7 t7, T8 t8)
{
  std::cout << t1 << t2 << t3 <<  t4 << t5 << t6 << t7 << t8;
}



