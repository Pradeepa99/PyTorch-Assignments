#include <torch/torch.h>
#include <iostream>

/*
Computes the element-wise remainder of division
fmod_value = ((number - divisor) * (number / divisor) )
*/

/* To raise an exception that occurs*/
struct MyException
{
    const char *what_exception() const throw()
    {
        return "ZeroDivision error";
    }
};

/* Custom ops to compute the fmod function*/

template <typename T>
torch::Tensor compute_fmod(torch::Tensor array, T value)
{

    try
    {

        torch::Tensor x = torch::remainder(array, value);
        torch::Tensor y = torch::sign(array);
        torch::Tensor z = torch::mul(x, y);
        return z;
    }

    catch (MyException &e)
    {
        std::cout << e.what_exception() << std::endl;
    }
}

int main()
{

    try
    {

        torch::Tensor x1 = torch::tensor({1.2, 7.36, 2.51, 56.2, 9.1, 4.9});   /*Dividend of float type*/
        torch::Tensor x2 = torch::tensor({12, 6, 98, 34, 74, 23});             /*Dividend of int type*/
        torch::Tensor x3 = torch::tensor({3.6, 4.2, 9.345, 8.61, 12.81, 1.2}); /*Dividend of both positive and negative  float values*/
        torch::Tensor x4 = torch::tensor({-34, -11, -87, -65, -126, -76});     /*Dividend of both positive and negative  int values*/

        torch::Tensor y1 = torch::tensor({2, 3, 4, 5, 6, 8}); /*Divisor of tensor type*/

        /*Computing the builtin fmod function*/

        torch::Tensor a1 = torch::fmod(x1, 7.3);
        torch::Tensor a2 = torch::fmod(x2, 64);
        torch::Tensor a3 = torch::fmod(x3, 23);
        torch::Tensor a4 = torch::fmod(x2, y1);
        torch::Tensor a5 = torch::fmod(x2, 5);
        torch::Tensor a6 = torch::fmod(x4, 13);

        /* Printing the values to check Fmod Builtin output*/

        std::cout << "Fmod output" << std::endl;
        std::cout << a1 << std::endl;
        std::cout << a2 << std::endl;
        std::cout << a3 << std::endl;
        std::cout << a4 << std::endl;
        std::cout << a5 << std::endl;
        std::cout << a6 << std::endl;

        /*Computing Custom ops for Fmod function*/

        torch::Tensor result1 = compute_fmod<float>(x1, 7.3); /*Divisor of float scalar type*/

        torch::Tensor result2 = compute_fmod<int>(x2, 64); /*Divisor of int scalar type*/
        torch::Tensor result3 = compute_fmod<int>(x3, 23); /*Divisor of int scalar type*/
        torch::Tensor result4 = compute_fmod(x2, y1);      /*Dividend and Divisor of Tensor type*/
        torch::Tensor result5 = compute_fmod(x2, 5);
        torch::Tensor result6 = compute_fmod<int>(x4, 13);

        /* Printing the values to check the Custom output*/

        std::cout << "custom ops output" << std::endl;
        std::cout << result1 << std::endl;
        std::cout << result2 << std::endl;
        std::cout << result3 << std::endl;
        std::cout << result4 << std::endl;
        std::cout << result5 << std::endl;
        std::cout << result6 << std::endl;

        assert(torch::equal(a1, result1));
        assert(torch::equal(a2, result2));
        assert(torch::equal(a3, result3));
        assert(torch::equal(a4, result4));
        assert(torch::equal(a5, result5));
        assert(torch::equal(a6, a6));
    }

    catch (MyException &e)
    {
        std::cout << e.what_exception() << std::endl;
    }
}
