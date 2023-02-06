# Void pointers

Also known as generic pointers, these are special types of pointers that can be pointed at objects of any data point.

They are declared as follows:

```cpp
void* ptr; // ptr is a void pointer
```

However, since the void pointers does not know what type of object it is pointing to, dereferencing it is illegal.
It must be cast to another pointer type before dereferencing can be performed.
This can be done using `static_cast`.

It is down to the programmer to keep track of the type of object that the void pointer points to.

Void pointers can also be set to a null value (`nullptr`).

Some compilers allow deleting void pointers pointing to dynamically allocated memory but doing so should be avoided as it can result in undefined behaviour.

Because it lacks a type, pointer arithmetic cannt be performed on a void pointer.
This is because the pointer needs to know what size object it points to to increment/decrement appropriately.

There is no such thing as a void reference as it would be of type `void&` and would not know what type of value it referenced.

In general, it is best to avoid using void pointers unless necessary.


