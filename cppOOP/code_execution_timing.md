# Code execution timing

One way to evaluate the performance of code is to time how long it takes to run.
This can be done using the `chrono` library and more elegantly implemented using classes.

```cpp
#include <chrono> // for std::chrono functions

class Timer
{
private: 
    // type aliases for ease of access
    using Clock = std::chrono::steady_clock;
    using Second = std::chrono::duration<double, std::ratio<1>>;

    std::chrono::time_point<Clock> m_beg{ Clock::now() };

public:
    void reset()
    {
        m_beg = Clock::now()
    }

    double elapsed() const
    {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    }
};
```

To use this, instantiate a Timer object at the beginning of the main function (or from where timing is to start) then call the `elapsed()` member function to the point where you want to stop timing.

## Factors that can affect timing

Although straightforward, it is important to be aware of many factors that can influence the timing results of a program.

First is whether you are using a release build target or a debug build target.
Debug build targets typically turn optimisation off which can impact the results significantly.

Second is what else your system may be doing in the background.
If it is doing any CPU or memory intensive tasks (e.g. gaming) or hard drive intensive tasks (e.g. file search, antivirus scan), then your timed results will be slower.

Third is to be aware of factors such as randomisation (which can be controlled by using a fixed seed) and time for user inputs (try to avoid timing through these or at least account for them).

Finally is to remember the reslts are only valid for the architecture of the machine you are working on - results may vary depending on systems used.

It is best to do a few runs to ensure consistency of results and have an idea of the average time taken.
This ensures that outliers due to unexpected or temporary events such as CPU spikes do not affect your data.
