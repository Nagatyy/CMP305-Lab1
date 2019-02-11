/*----
 NOTE: We used the mathematical defenition of a set in our class:
 Key features:
 - A set can only have unique values for elements
 - Addition and Subtraction of a set follow set convection (NOT as Arrays)
 - ie {1, 2, 3} + { 3, 4, 5} = {1, 2, 3, 4, 5}
 - ie {1, 2, 3} - { 1, 2, 3, 4} = {4}
 - A + B = B + A & A - B = B - A
-----*/
#ifndef Set_hpp
#define Set_hpp

#include <stdio.h>
#include <iostream>
using namespace std;



template <class T>
class  Set {
private:
    int eCount;    // current number of elements within the set.
    int max_size;
    int iter; // variable used in reset and getNextElement function for iteration.
    T  *arr; // an array to store the Set elements.

public:
//    constructors and destructor
    Set(int size = 5); //default constructor
    Set(const Set & s); // copy constructor
    ~Set(); //destructor
//    getters
    int GetSize() const;   // returns the max size of the Set
    int GetCount()  const;// returns the  current number  of  elements  within Set
//    additional
    bool InsertElement(T value); // insert value
    bool DeleteElement(T value); // delete value
    int GetNextElement(); //returns value at iter
    void Reset(); //sets iter to 0;
    bool ValueExists(T value);
    void clean(); // clean used in + operator, removes any duplicates
//    operators
    Set &operator=(const Set <T> &s);
    bool operator==(const Set<T> &s);
    bool operator!=(const Set<T> &s);
    Set operator+(const Set<T> &s);
    Set operator-(const Set<T> &s);
    Set &operator+=(const Set &s);
    Set &operator-=(const Set &s);
    Set &operator++();
    Set operator++(int x);
    Set &operator--();
    Set operator--(int x);
//    friends defined in class to run on Xcode
    friend ostream &operator<<(ostream &outs, const Set<T> &s) {
        cout << " = { ";
        for (int i = 0; i < s.eCount; i++)
            outs << s.arr[i] << " ";
        cout << "}" << endl;
        return outs;
    }
    friend istream &operator>>(istream &ins, Set <T> &s){
        cout << "Enter how many elements in the set: ";
        cin >> s.eCount;
        while (s.eCount < 0 ||s.eCount > s.max_size)
        {
            cout << "Too many elements!" << endl;
            cout << "Enter how many elements in the set: ";
            cin >> s.eCount;
        }
        cout << "Enter the elements of your set: ";
        for (int i = 0; i < s.eCount; i++)
        {
            cin >> s.arr[i];
        }
        return ins;
    }
};

template <typename T> Set<T>::Set(int size)
{
    max_size = size;
    arr = new T[max_size];
    iter = 0;
    eCount = 0;
}
template <typename T>Set<T>::Set(const Set<T> &s)
{
    max_size = s.max_size;
    eCount = s.eCount;
    arr = new T[max_size];
    for (int i = 0; i < eCount; i++)
    {
        arr[i] = s.arr[i];
    }
    iter = 0;
}
template <typename T>Set<T>::~Set<T>()
{
    delete[]arr;
}
template <typename T>int Set<T>::GetSize() const
{
    return max_size;
}
template <typename T>int Set<T>::GetCount() const
{
    return eCount;
    
}
template <typename T>bool Set<T>::InsertElement(T value) //Sets cannot have two elements of the same value!
{
    if (eCount < max_size)
    {
        if (ValueExists(value))
        {
            cout << "Value already exists in the array!" << endl;
            return false;
        }
        
        arr[eCount] = value;
        eCount++;
        cout << value << " was succesfully added to the set!" << endl;
        return true;
    }
    cout << "Set is full!" << endl;
    return false;
}
template <typename T>bool Set<T>::DeleteElement(T value)        //Only checks one time, as sets cannot have repeated elements!
{
    if (!ValueExists(value))
        return false;
    for (int i = 0; i < eCount; i++)
    {
        if (arr[i] == value)
        {
            for (int j = i; j < eCount - 1; j++)
            {
                arr[j] = arr[j + 1];
            }
            i--;
            eCount--;
        }
    }
    return true;
}

template <typename T>int Set<T>::GetNextElement()
{
    if (iter < eCount)
    {
        iter++;
        return arr[iter - 1];
    }
    else
    {
        iter = 0;
        return arr[eCount - 1];
    }
}
template <typename T>void Set<T>::Reset()
{
    iter = 0;
    
}
template <typename T>Set<T> &Set<T>::operator=(const Set<T> &s)
{
    if (this == &s) //checking for self assignment
        return *this;
    
    if (max_size != s.max_size)
    {
        delete[]arr;
        max_size = s.max_size;
        arr = new int[max_size];
    }
    eCount = s.eCount;
    iter = 0;
    
    for (int i = 0; i < eCount; i++)
    {
        arr[i] = s.arr[i];
    }
    return *this;
}
template <typename T>bool Set<T>::operator==(const Set<T> &s) //will get back to u
{
    if (max_size != s.max_size && eCount != s.eCount)
        return false;
    
    for (int i = 0; i < eCount; i++)
    {
        if (arr[i] != s.arr[i])
        {
            return false;
        }
    }
    return true;
}
template <typename T>bool Set<T>::operator!=(const Set<T> &s)
{
    return !(*this == s);
}
template <typename T>Set<T> Set<T>::operator+(const Set<T> &s) //Addition adds all elements into a new set with no repeated elements!
{
    int m;
    m = max_size + s.max_size;
    
    Set<int> temp(m);
    
    for (int i = 0; i < eCount; i++)
    {
        temp.arr[i] = arr[i];
    }
    temp.eCount = eCount;
    
    for (int i = eCount, j = 0; j<s.eCount; j++)
    {
        if (!temp.ValueExists(s.arr[j])) {
            temp.arr[i] = s.arr[j];
            temp.eCount++;
            i++;
        }
    }
    return temp;
}
template <typename T>Set<T> Set<T>::operator-(const Set<T> &s) //Subtraction adds all unique elements into a new set!
{
    int m;
    m = max_size + s.max_size;
    
    
    Set<int> temp(m);
    temp.eCount = eCount + s.eCount;
    
    for (int i = 0; i < eCount; i++)
        temp.arr[i] = arr[i];
    
    for (int i = eCount, j=0; i < temp.eCount;j++, i++)
        temp.arr[i] = s.arr[j];
    temp.clean();
    return temp;
    
}

template <typename T>Set<T> &Set<T>::operator+=(const Set<T> &s)
{
    *this = *this + s;
    
    return *this;
}

template <typename T>Set<T> &Set<T>::operator-=(const Set<T> &s)
{
    *this = *this - s;
    return *this;
}
template <typename T>Set<T> &Set<T>::operator++()
{
    for (int i = 0; i < eCount; i++)
        arr[i]++;
    return *this;
}
template <typename T>Set<T> Set<T>::operator++(int x)
{
    Set temp = *this;
    for (int i = 0; i < eCount; i++)
        arr[i]++;
    return temp;
}
template <typename T>Set<T> &Set<T>::operator--()
{
    for (int i = 0; i < eCount; i++)
        arr[i]--;
    return *this;
}
template <typename T>Set<T> Set<T>::operator--(int x)
{
    Set temp = *this;
    for (int i = 0; i < eCount; i++)
        arr[i]--;
    return temp;
}
template <typename T>bool Set<T>::ValueExists(T value)
{
    for (int i = 0; i < eCount; i++)
        if (value == arr[i])
            return true;
    return false;
}
template <typename T>void Set<T>::clean()
{
    int c = 0;
    for (int i = 0; i < eCount; i++) {
        for (int j = i + 1; j < eCount; j++) {
            if (arr[i] == arr[j]) {
                DeleteElement(arr[i]);
                i--;
                c++;
            }
        }
    }
}


#endif /* Set_hpp */
