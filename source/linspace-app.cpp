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

  torch::Tensor int_result1, int_result2, float_result1, float_result2;

  /* Int data type */
  int start[] = {3, 2, -10, 25, -5, -10, 6, 52};
  int end[] = {10, 5, 10, 100, 10, 10, 78, 60};

  /* Float data type*/
  float f_start[] = {-2.5, 3.4, 23.3, 20.6, 11.1, -10.2};
  float f_end[] = {10.2, 10.5, 40.2, 30.2, 57.3, -5.2};

  int steps[] = {5, 4, 5, 6, 6, 5, 10, 0};

  int float_count = 0, int_count = 0, total_count;

  try
  {

    for (int i = 0; i < 6; i++)
    {

      float_count++;

      if (steps[i] == 0)
      {

        throw MyException();
      }

      float_result1 = torch::linspace(f_start[i], f_end[i], steps[i]);         //Built in linspace
      float_result2 = compute_linspace<float>(f_start[i], f_end[i], steps[i]); //Custom op for linspace

      /* Printing the values to check the output*/
      std::cout << "Float Linspace output" << std::endl;
      std::cout << float_result1 << std::endl;
      std::cout << "Float Custom ops output" << std::endl;
      std::cout << float_result2 << std::endl;

      assert(torch::equal(float_result1, float_result2));
    }

    for (int i = 0; i < 8; i++)
    {

      int_count++;

      if (steps[i] == 0)
      {

        throw MyException();
      }

      int_result1 = torch::linspace(start[i], end[i], steps[i]);       //Built in linspace
      int_result2 = compute_linspace<int>(start[i], end[i], steps[i]); //Custom op for linspace

      /* Printing the values to check the output*/

      std::cout << "Int Linspace output" << std::endl;
      std::cout << int_result1 << std::endl;
      std::cout << "Custom ops output" << std::endl;
      std::cout << int_result2 << std::endl;

      assert(torch::equal(int_result1, int_result2));
    }
  }

  catch (MyException &e)
  {
    std::cout << e.what_exception() << std::endl;
  }

  total_count = float_count + int_count;

  std::cout << "Total test cases passed:" << total_count << std::endl
            << std::endl;
}
