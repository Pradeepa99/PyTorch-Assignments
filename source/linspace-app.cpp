#include <torch/torch.h>
#include <iostream>

/*
Creates a one-dimensional tensor of size steps whose values are 
evenly spaced from start to end,inclusive. 

linspace_value = (end-start) / (step-1) for the given range
*/

/* To raise an exception that occurs*/
struct MyException
{
  const char *what_exception() const throw()
  {
    return "Exception occured : Step value is zero";
  }
};

/* Custom ops to compute the linspace function*/

template <typename T>
torch::Tensor compute_linspace(T start, T end, T steps)
{
  try
  {

    torch::Tensor a = torch::sub(torch::tensor(end), torch::tensor(start));
    torch::Tensor b = torch::sub(torch::tensor(steps), torch::tensor(1));
    torch::Tensor c = torch::div(a, b);

    /*If steps is 1 print only the start element*/
    if (steps == 1)
    {
      torch::Tensor x = torch::tensor(start);
      return x;
    }

    if (steps != 0)
    {
      torch::Tensor x = torch::range(start, end, c.item());
      return x;
    }

    /*If steps is 0 throw an exception message*/
    if (steps == 0)
    {
      throw MyException();
    }
  }

  catch (MyException &e)
  {

    std::cout << e.what_exception() << std::endl;
  }
}

int main()
{

  torch::Tensor float_result1, float_result2, float_result3, float_result4, float_result5, float_result6;
  torch::Tensor int_result1, int_result2, int_result3, int_result4, int_result5, int_result6, int_result7, int_result8;
  torch::Tensor float_compute_result1, float_compute_result2, float_compute_result3, float_compute_result4, float_compute_result5, float_compute_result6;
  torch::Tensor int_compute_result1, int_compute_result2, int_compute_result3, int_compute_result4, int_compute_result5, int_compute_result6, int_compute_result7, int_compute_result8;

  try
  {

    /* Built in linspace - Float data type */

    float_result1 = torch::linspace(-2.5, 10.2, 5);  //start is negative
    /* Both start and end is positive */
    float_result2 = torch::linspace(3.4, 10.5, 4);  
    float_result3 = torch::linspace(23.3, 40.2, 5);
    float_result4 = torch::linspace(20.6, 30.2, 6);
    float_result5 = torch::linspace(11.1, 57.3, 6); 
    float_result6 = torch::linspace(-10.2, -5.2, 5); //Both start and end is negative

    /* Custom op for linspace - Float data type */

    float_compute_result1 = compute_linspace<float>(-2.5, 10.2, 5);
    float_compute_result2 = compute_linspace<float>(3.4, 10.5, 4);
    float_compute_result3 = compute_linspace<float>(23.3, 40.2, 5);
    float_compute_result4 = compute_linspace<float>(20.6, 30.2, 6);
    float_compute_result5 = compute_linspace<float>(11.1, 57.3, 6);
    float_compute_result6 = compute_linspace<float>(-10.2, -5.2, 5);

    /* Built in linspace - Int data type */

    int_result1 = torch::linspace(3, 10, 5); //Both start and end is positive
    int_result2 = torch::linspace(2, 5, 4);
    int_result3 = torch::linspace(-100, 10, 5); //start is negative
    int_result4 = torch::linspace(25, 100, 6);
    int_result5 = torch::linspace(-5, 10, 6);
    int_result6 = torch::linspace(-10, 10, 5);
    int_result7 = torch::linspace(6, 78, 10);
    int_result8 = torch::linspace(52, 60, 0); //step is zero

    /* Custom op for linspace - Int data type */

    int_compute_result1 = compute_linspace<int>(3, 10, 5);
    int_compute_result2 = compute_linspace<int>(2, 5, 4);
    int_compute_result3 = compute_linspace<int>(-100, 10, 5);  
    int_compute_result4 = compute_linspace<int>(25, 100, 6);
    int_compute_result5 = compute_linspace<int>(-5, 10, 6);
    int_compute_result6 = compute_linspace<int>(-10, 10, 5);
    int_compute_result7 = compute_linspace<int>(6, 78, 10);
    int_compute_result8 = compute_linspace<int>(52, 60, 0);  

    /* Printing the values to check the Builtin output for Float Test cases */

    std::cout << "Float Linspace output" << std::endl;
    std::cout << float_result1 << std::endl;
    std::cout << float_result2 << std::endl;
    std::cout << float_result3 << std::endl;
    std::cout << float_result4 << std::endl;
    std::cout << float_result5 << std::endl;
    std::cout << float_result6 << std::endl;

    /* Printing the values to check the Custom ops output for Float Test cases */

    std::cout << "Float Custom ops output" << std::endl;
    std::cout << float_compute_result1 << std::endl;
    std::cout << float_compute_result2 << std::endl;
    std::cout << float_compute_result3 << std::endl;
    std::cout << float_compute_result4 << std::endl;
    std::cout << float_compute_result5 << std::endl;
    std::cout << float_compute_result6 << std::endl;

    /* Assert to check the results for Float Test cases */

    assert(torch::equal(float_result1, float_compute_result1));
    assert(torch::equal(float_result2, float_compute_result2));
    assert(torch::equal(float_result3, float_compute_result3));
    assert(torch::equal(float_result4, float_compute_result4));
    assert(torch::equal(float_result5, float_compute_result5));
    assert(torch::equal(float_result6, float_compute_result6));

    /* Printing the values to check the Built in output for Int Test cases*/

    std::cout << "Int Linspace output" << std::endl;
    std::cout << int_result1 << std::endl;
    std::cout << int_result2 << std::endl;
    std::cout << int_result3 << std::endl;
    std::cout << int_result4 << std::endl;
    std::cout << int_result5 << std::endl;
    std::cout << int_result6 << std::endl;
    std::cout << int_result7 << std::endl;
    std::cout << int_result8 << std::endl;

    /* Printing the values to check the Custom ops output for Int Test cases*/

    std::cout << "Int Custom ops output" << std::endl;
    std::cout << int_compute_result1 << std::endl;
    std::cout << int_compute_result2 << std::endl;
    std::cout << int_compute_result3 << std::endl;
    std::cout << int_compute_result4 << std::endl;
    std::cout << int_compute_result5 << std::endl;
    std::cout << int_compute_result6 << std::endl;
    std::cout << int_compute_result7 << std::endl;
    std::cout << int_compute_result8 << std::endl;

    /* Assert to check the results for Int Test cases */

    assert(torch::equal(int_result1, int_compute_result1));
    assert(torch::equal(int_result2, int_compute_result2));
    assert(torch::equal(int_result3, int_compute_result3));
    assert(torch::equal(int_result4, int_compute_result4));
    assert(torch::equal(int_result5, int_compute_result5));
    assert(torch::equal(int_result6, int_compute_result6));
    assert(torch::equal(int_result7, int_compute_result7));
    assert(torch::equal(int_result8, int_compute_result8));
  }

  catch (MyException &e)
  {
    std::cout << e.what_exception() << std::endl;
  }

 
}
