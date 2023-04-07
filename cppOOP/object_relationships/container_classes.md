# Container classes

These are classes designed to hold and organise multiple instances of another type.
There are many different kinds of container classes which come with their own pros and cons.
The most common container is the array but array container classes such `std::array` and `std::vector` are more commonly used due to their additional benefits.

Container classes usually have a fairly standard minimal set of functionalities including:
- Empty container creation
- Object insertion
- Object removal
- Current object count
- Empty container of all objects
- Provide access to stored objects
- Sort elements

## Types of containers

Container classes usually come in two varieties.
Value containers are compositions storing copies of the objects they hold.
Reference containers are aggregations storing pointers or references to other objects.

Unlike real life, containers in C++ generally only hold one type of data and do not allow arbitrary mixing of types.
To hold multiple types, you may require advanced C++ features like templates.
Generally, you will need to use multiple containers which, although is seemingly restrictive, makes programming easier, safer and faster.

### Writing container classes

When writing container classes, it may be desirable to allow for an initialiser list to be used.
This can be done by using `std::initializer_list`, which lives in the `<initializer_list>` header, in the constructor argument.

To use `std::initializer_list`, you need to bear in mind that
- You have to specify the type of data the list will hold
- The `size()` function returns the number of elements in the list (useful to determine list length passed)
- `std::initializer_list` is often passed by value as it is a view (c.f. `std::string_view`)
- `std::initializer_list` does not provide access to the list elements using the subscripting operator `[]` (meaning you may need to use a for-each loop to assign values)
- List initialisation prefers list constructors over non-list constructors

`std::initializer_list` can be used to assign new values to a class by overloading the assignment operator `=`= to take a `std::initializer_list` parameter.
If you implement a constructor taking a `std::initializer_list`, you should ensure you do at least one of the following:
- Provide an overloaded list assignment operator
- Provide a proper deep-copying copy assignment operator
- Delete the copy assignment operator

When initialising a container with a list constructor, you should use brace initialising when intending to call the list constructor as your initialisers are element values.
Use direct initialisation when you intend to call a non-list constructor.

Note that adding a list constructor to an existing class that cause existing programs to silently change behaviour and break existing programs.

If you provide list construction, it is a good idea to provide list assignment as well.

Writing container classes can be quite complex but once written and working, they can be used and reused with minimal effort.
You should use a container class in the standard library if it meets your needs instead of writing your own, but it's good to be aware of how to create your own if you ever need to do so.
