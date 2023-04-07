# Object composition

Object composition refers to the process of building up more complex objects from simpler ones.
This allows us to create complex classes by combining simpler, more easily manageable parts.
By reducing complexity, code can be written faster and with fewer errors.

The relationship between object composition models can be described as A "has-a" B.
The complex overall object is called the whole or parent.
A simpler object making up the parent is often called the part, child or component.

One example is structs and classes which can hold data members of various other types.
In essence, we are constructing a more complex object from simpler parts.

There are two basic subtypes to object composition: composition and aggregation.

## Composition

If a parent object and child object have the following relationships, they are classified as a composition:
- The child is part of the parent.
- The child can only belong to one parent at a time.
- The child has its existence managed by the parent.
- The child does not know about the existence of the parent.

Composition refers to part-whole relationships where the part must constitute part of the whole object.
In composition relationships, the object is responsible for the existence of its parts meaning parts are created when the object is created and destroyed when the object is destroyed.
The relationship is also unidirectional in that the part does not know about the existence of the whole.

Composition has nothing to say about the transferability of parts as parts can still be in composition relationships even when they are transferred to different objects.

Physical relationships where one object is physically contained within another are often modelled by compositions.

As a general rule, the parts that make up the whole should be self-contained, reusable and focus on performing one task well.
This makes such objects easier to write and understand.

### Implementing compositions

Typically created as structs or classes, compositions are straightforward to implement in C++.
Compositions requiring dynamic allocation or deallocation may be reimplemented using pointer data members (the composition class should be responsible for all necessary memory management).

In general, if you can design a class using composition, you should as they will be straightforward, flexible, and robust.

### Variants on compositions

Not all compositions adhere to the rules outlined above.
For example,
- A composition may defer creation of some parts until needed.
- A composition may opt to use a part given as an input rather than create it itself.
- A composition may delegate destruction of its parts to another object.

## Aggregation

If a parent and its children are an aggregation, they must follow the following relationships:
- The child is part of the parent.
- The child can (if desired) belong to more than one parent at a time.
- The child does *not* have its existence managed by the parent.
- The child does not know about the existence of the parent.

Aggregation is still a unidirectional, part-whole relationship.
However, its parts can belong to more than one object at a time and the whole object is not responsible for the existence and lifespan of the parts.
When an aggregation is destroyed, it is also not responsible for destroying the parts.

### Implementing aggregations

Aggregations are implemented almost identically to compositions, with differences between them being mostly semantic.
In a composition, parts are typically added using normal member variables.
In an aggregation, parts are also added as member variables, but these are usually references or pointers that point at objects created outside the scope of the class.
As such, aggregations usually take objects they will point to as constructor parameters or begin empty, with sub-objects added later via access functions or operators.

### std::reference\_wrapper

If we want to store multiple parts, from references, we may need to use `std::reference_wrapper` as we cannot store references to parts in fixed arrays or standard library lists.

`std::reference_wrapper` is a class that acts like a reference but allows assignment and copying, making it compatible with lists like `std::vector`.

The main things to know are:
- `std::reference_wrapper` lives in the `<functional>` header
- When creating a `std::reference_wrapper` wrapped object, the object cannot be an anonymous object (else it would leave a dangling reference)
- To get an object back from `std::reference_wrapper`, use the `get()` member function

## Summary

The best practice is to implement the simplest relationship type meeting the needs of your program, not what seems right in real life.

In summary, compositions
- Typically use normal member variables
- Can use pointer members if the class handles object allocation/deallocation by itself
- Are responsible for the creation/destruction of parts

whereas aggregations
- Typically use pointer or reference members that point to or reference objects that live outside the scope of the aggregate class
- Are not responsible for creating/destroying parts

Both concepts can be mixed freely within the same class, but it is always important to ensure deallocation is handled properly.
For this reason, compositions are usually favoured over aggregations which are potentially more dangerous.
