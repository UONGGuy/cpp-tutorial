# Object dependencies

Dependency occurs when an object invokes another object's functionality to accomplish a specific task.
It is a weaker relationship than association but any change to the object being depended on can break the functionality of the dependent caller.
Dependencies are always unidirectional relationships.
An example of a dependency is `std::ostream` where we can write classes that use it to output something to console but not otherwise.

## Differences with associations

Associations are a relationship between two classes at the class level meaning one class keeps a link (direct or indirect) to the associated class as a member.

On the other hand, dependencies are not represented at the class level, meaning the object being depended upon is not linked as a member.
Instead, it is usually instantiated as needed or passed to a function as a parameter.
