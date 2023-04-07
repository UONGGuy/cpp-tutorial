# Object association

Association is a type of relationship weaker than object composition between two otherwise unrelated objects.
Unlike object composition relationships, there is no implied whole-part relationship in association.

## Association

Two objects qualify as an association if they share the following relationship:
- The associated object is otherwise unrelated to the other object.
- The associated object can belong to more than one object at a time.
- The associated object does *not* have its existence managed by the other object.
- The associated object may or may not know about the existence of the other object.

In association, the associated object is otherwise unrelated to the object.
The relationship in an association can be unidirectional or bidirectional (both objects are aware of each other).
However, bidirectional associations are usually avoided if unidirectional ones are sufficient as they add complexity and potential for errors.
Association models have a "uses-a" type of relationship ("A uses a B").

### Implementing associations

Associations are broader than compositions and aggregations so can be implemented in many different ways.
Most often, associations are implemented using pointers where the object points at the associated object.

```cpp
#include <functional>
#include <string>
#include <vector>

class Patient;

class Doctor
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<const Patient>> m_patient{};

public:
    Doctor(const std::string& name)
        : m_name{ name }
    {}

    void addPatient(Patient& patient);
    const std::string& getName() const { return m_name; }
};

class Patient
{
private:
    std::string m_name{};
    std::vector<std::reference_wrapper<const Doctor>> m_doctor{};
    // Make addDoctor private to prevent public use
    // Should use Doctor::addPatient() instead
    void addDoctor(const Doctor& doctor)
    {
        m_doctor.push_back(doctor);
    }

public:
    Patient(const std::string& name) : m_name{ name }
    {}

    const std::string& getName() const { return m_name; }
    friend void Doctor::addPatient(Patient& patient);
};

void Doctor::addPatient(Patient& patient)
{
    // Doctor adds patient
    m_patient.push_back(patient);
    // Patient also adds doctor
    patient.addDoctor(*this);
}

int main()
{
    Patient dave{ "Dave" };
    Doctor james{ "James" };

    james.addPatient(dave);
    // james.m_patient[0] = dave
    // dave.m_doctor[0] = james

    return 0;
}
```
### Reflexive association

Reflexive association refers to objects having relationships with other objects of the same type.
For example:

```cpp
#include <string>
class Course
{
private:
    std::string m_name;
    const Course* m_prerequisite;

public:
    Course(const std::string& name const Course* prerequisite=nullptr)
        : m_name{ name }, m_prerequisite{ prerequisite }
    {}
};
```

This can lead to a chain of associations.

### Indirect associations

In associations, any kind of data that allows two objects to be linked together is sufficient - i.e. you do not have to only use either pointers or references to link objects.

```cpp
#include <iosream>
#include <string>

class Car
{
private:
    std::string m_name;
    int m_id;

public:
    Car(const std::string& name, int id) 
        : m_name{ name }, m_id{ id }
    {}

    const std::string& getName() const { return m_name; }
    int getId() const { return m_id; }
};

class CarLot // essentially a static array of Cars + lookup fn
// No need to allocate an object of type CarLot to use as is static
{
private:
    static Car s_carLot[4]; 

public:
    CarLot() = delete; // prevent creation of CarLot

    static Car* getCar(int id)
    {
        for (int count{ 0 }; count < 4; ++count)
        {
            if (s_carLot[count].getId() == id )
            {
                return &(s_carLot[count]);
            }
        }
        return nullptr;
    }
};

Car CarLot::s_carLot[4]{ 
    { "Prius", 4 },
    { "Corolla", 17 },
    { "Accord", 84 },
    { "Matrix", 62 }
};

class Driver
{
private:
    std::string m_name;
    int m_carId; // asssociated with Car by ID rather than pointer

public:
    Driver(const std::string& name, int carId)
        : m_name{ name }, m_carId{ carId }
    {}

    const std::string& getName() const { return m_name; }
    int getCarId() const { return m_carId; }
};

int main()
{
    Drive d{ "Franz", 17 };

    Car* car{ CarLot::getCar(d.getCarId()) };

    if (car)
        std::cout << d.getName() << " is driving a " << car->getName() << '\n';
    else
        std::cout << d.getName() << " couldn't find his car\n";

    return 0;
}
```

In this example, the car ID is used to link the Driver to the Car instead of a pointer.
Although a pointer is much faster, using a unique ID allows things not currently in memory to be referenced and can save lots of memory.


