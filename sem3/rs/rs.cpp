#include "gfprime.h"
#include "matrix.h"

int main()
{

    std::cout << "Solving AX = B (double):\n";

    Matrix<double> A(2, 2);
    A[0, 0] = 1; A[0, 1] = 3;
    A[1, 0] = 2; A[1, 1] = 4;

    Matrix<double> B(2, 3);
    B[0, 0] = 5; B[0, 1] = 7; B[0, 2] = 9;
    B[1, 0] = 7; B[1, 1] = 10; B[1, 2] = 13;

    auto X = A.solve(B);

    std::cout << "A =\n" << A;
    std::cout << "B =\n" << B;
    std::cout << "X =\n" << X;

    std::cout << "Solving AX = B (GF(11)):\n";

    Matrix<GFprime<11>> AA(2, 2);
    AA[0, 0] = 1; AA[0, 1] = 3;
    AA[1, 0] = 2; AA[1, 1] = 4;

    Matrix<GFprime<11>> BB(2, 3);
    BB[0, 0] = 5; BB[0, 1] = 7; BB[0, 2] = 9;
    BB[1, 0] = 7; BB[1, 1] = 10; BB[1, 2] = 13;

    auto XX = AA.solve(BB);

    std::cout << "A =\n" << AA;
    std::cout << "B =\n" << BB;
    std::cout << "X =\n" << XX;

    return 0;

}
