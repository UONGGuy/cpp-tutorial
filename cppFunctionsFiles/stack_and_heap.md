# The stack and the heap

The memory a program uses can be categorised into different segments:
- The code (text) segment. This is where the compiled program sits in the memory and is typically read-only.
- The bss (unninitialised data) segment. This is where zero-initialised global and static variables are stored.
- The (initialised) data segment. This is where global and static variables are stored.
- The heap. Memory that is allocated to dynamically allocated variables.
- The call stack. Where function parameters, local variables and other function-related information are stored.

## The heap segement

This is also known as the "free store" and keeps track of memory used for dynamic memory allocation.

When the `new` operator is used to allocate memory, the memory is allocated in the application's heap segment.
The address of this memory is passed back by operator `new` and can be stored in a pointer.

Note that sequential memory requests may not result in sequential memory addresses being allocated.

When a dynamically allocated variable is deleted, memory is "returned" to the heap, available for future reallocation.

Some features of the heap:
- Allocating memory on the heap is comparatively slow.
- Allocated memory stays allocated until specifically allocated (which can lead to memory leaks) or the application ends (where the OS *should* clean it up).
- Dynamically allocated memory must be accessed through a pointer and dereferencing pointers is slower than directly accessing variables.
- The size of the heap allows large arrays, structures or classes to be allocated there.

## The call stack

Usually referred to as the stack, it keeps track of all active functions that have been called but not yet terminated.
It handles the allocation of all function parameteres and local variables.

Some features of the call stack:
- Allocating memory on the stack is comparatively fast.
- Memory alllocated on the stack stays in scope as long as it is on the stack and is destroyed when popped off it.
- All memory allocated on the stack is known at compile time, meaning it can be accessed directly through a variable.
- The stack is relatively small so is not suitable for high-memory usage (e.g. passing by value, creating local variables of large arrays/memory-intensive structures).

### The stack data structure

A data structure is a programming mechanism for organising data for efficient usage.
Examples of such are arrays and structs.

A stack is a container data structure that holds multiple variables.
However, it is more limited than say an array which lets you access and modify elements in any order you wish (called random access).
Operations that can be performed on a stack correspond to:
1. Looking at the top item on the stack (usually done via a function called `top()` or `peek()`)
2. Take the top item off the stack (done via a function called `pop()`)
3. Put a new item on top of the stack (done via a function called `push()`)

It is a last-in, first-out (LIFO) structure: the last item pushed onto the stack will be the first item popped off.

The call stack is similar to the stack data structure.
An analogy would be having a column of mailboxes nailed on top of one another.
We mark the bottom-most empty mailbox with a post-it note and move it up one if an item is added (pushed onto the stack) and down one if an item is removed from the mailbox (popped from the stack.
Anything at or above the marker is not on the stack.

The call stack is a fixed-size chanck of memory addresses and the items pushed and popped off the stack are called stack frames.
Each stack frame acts as a "mailbox" and keeps track of all the data associated with one function call.
The "marker" is a register, a small piece of memory in the CPU known as the stack pointer keeping trackf where the top of the call stack currently is.
When an item is popped off the call stack, the stack pointer only has to move down.
We don't need to clean up the memory as it is no longer considered "on the stack" so won't be accessed.
If a new stack frame is pushed on later, it will overwrite the previous value.

When a C++ application starts, the main() function is pushed onto the call stack by the OS and the program begins executing.
When a function call is encountered, the function is pushed onto the call stack.
When the current function ends, the function is popped off the call stack (process is called "unwinding the stack").
By looking at functions currently on the call stack, we can see all the functions that were called to get to the current point of execution.

In more detail, when a function is called:

1. The program enters a function call.
2. A stack frame is constructed and pushed onto the stack. A stack frame consists of:
    - The address of the instruction beyond the function call (return address)
    - All function arguments
    - Memory for any local variables
    - Saved copies of any registers modified by the function that need restoring when the function returns.
3. The CPU jumps to the function's start point.
4. The function instructions are executed.

When a function terminates:

1. Registers are restored from the call stack.
2. The stack frame is popped off the stack.
3. The return value is handled.
4. The CPU resumes execution at the return address.

### Stack overflow

The stack has a limited size, restricting the amount of information it can hold.
If a program tries to put too much information on the stack, stack overflow occurs and memory allocations overflow into other sections of memory.

Stack overflow is generally the result of allocating too many variables onto the stack and/or making too many nested function calls.


