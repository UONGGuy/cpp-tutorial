# Command line arguments

These allow greater functionality to our programs by letting the user input parameters and options to change how the program will behave.

Command line arguments are optional string arguments passed by the OS to the program when launched.
Similar to function parameters, these can be used as inputs or ignored and give users a way to provide a progam with inputs.

## Passing command line arguments

To pass command line arguments to an executable, list them after the executable name:
```cpp
./WordCount Myfile.txt Myfile2.txt
```

## Using command line arguments

To access command line arguments from our C++ program, we use a different form of `main()`.
This form takes two arguments: argc and argv:
```cpp
int main(int argc, char* argv[])
// or sometimes written
// int main(int argx, char** argv)
```

argc is an integer parameter which represents the number of arguments passed to the program (you can remember this as argc = "argument count").
It will always be at least 1 as the first argument is the name of the program itself and increases by one per command line argument provided.

argv is where the argument values are stored (think argv = "argument vector/values").
It is an array of C-style strings with length argc.

An example program that prints the value of all command line parameters is:
```cpp
#include <iostream>

int main(int argc, char* argv[])
{
    std::cout << "There are " << argc << " arguments:\n";

    for (int count{ 0 }; count < argc; ++count)
    {
        std::cout << count << ' ' << argv[count] << '\n';
    }

    return 0;
}
```

## Dealing with numeric arguments

Command line arguments are always passed as strings.
To use a command line argument as a number, it needs to be converted from a string to a number.
This requires the use of `std::stringstream` from the `<sstream>` header.
```cpp
#include <iostream>
#include <sstream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc <= 1)
    {
        // argv[0] can be an empty string for some OSs
        // conditionalise response based off argv[0] empty or not
        if (argv[0])
            std::cout << "Usage: " << argv[0] << "<number>" << '\n';
        else
            std::cout << "Usage: <program name> <number>" << '\n';
        return 1;
    }

    // set up stringstream variable initialised with argv[1]
    std::stringstream convert{ argv[1] };
    
    int myint{};
    if (!(convert >> myint)) // do conversion
        myint = 0; // set myint to default value if conversion fails

    std::cout << "Got integer: " << myint << '\n';
    
    return 0;
}
```

`std::stringstream` is similar to std::cin in that it uses `operator >>` to extract an integer variable.

## OS command line parsing

The OS parses command line arguments first.
Strings passed in double quotes are ususally considered part of the same string.
Literal double quote symbols can be indicated by backslashing them on most OSs.

