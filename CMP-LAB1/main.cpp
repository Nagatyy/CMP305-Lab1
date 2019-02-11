#include <iostream>
#include "Set.hpp"


int main()
{
    cout << "Constructing and cin-ing set A" << endl;
    Set<int> a; //works
    cin >> a;
    cout << "cout-ing " << endl;
    cout << "A " << a << endl;
    
    
    cout << "Testing copy constructor for b(a);" << endl;
    Set<int> b(a); //works
    cout << "B " << b << endl;
    
    
    cout << "Testing assignment operator for c = b" << endl;
    Set<int> c;
    c = b; //works
    cout << "C " << c << endl;
    
    
    Set <int> d;
    cout << "Setting d = {4, 5, 6}, then d += a" << endl;
    d.InsertElement(4);
    d.InsertElement(5);
    d.InsertElement(6);
    d += a;
    cout << "D " << d << endl;
    
    
    cout << "Testing boolean == and !=" << endl;
    if (a == b) //works
        cout << "Set a & b are the same!" << endl;
    else cout << "Set a & b are different!" << endl;
    if (c != d) //works
        cout << "Set c & d are different!" << endl;
    else cout << "Set c & d are the same!" << endl << endl;
    
    
    cout << endl << "Declaring set E as A + C (changed to {2, 3, 800}) " << endl;
    c.DeleteElement(1);
    c.InsertElement(800);
    
    Set<int> e = a + c;
    cout << "E " << e << endl;
    
    
    cout << "Declaring set f as D - A " << endl;
    Set <int> f = d - a;
    cout << "F " << f << endl;
    
    
    cout << "Testing insertion" << endl;
    Set <int>g;
    for (int i = 0; i < g.GetSize() + 1; i++) //getcount+1 to show what happens when set is full!
        g.InsertElement(123167);
    cout << "G " << g << endl;
    
    
    cout << "Testing ++A" << endl;
    cout << "A " << ++a;
    cout << "Testing B++" << endl;
    cout << "B " << b++;
    cout << "For clarification, B " << b << endl;
    
    cout << "Testing --A" << endl;
    cout << "A " << --a;
    cout << "Testing B--" << endl;
    cout << "B " << b--;
    cout << "For clarification, B " << b << endl;
    
    int del;
    cout << "Testing delete function" << endl;
    cout << "Enter element to delete from set A (hint: try 2): ";
    cin >> del;
    a.DeleteElement(del);
    cout << "A " << a << endl;
}


