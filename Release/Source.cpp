#include <Python.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Windows.h>
#include <cmath>
#include <string>

using namespace std;

int userInput;
string str;
string fileLine;


void CallProcedure(string pName)
{
    char* procname = new char[pName.length() + 1];
    std::strcpy(procname, pName.c_str());

    Py_Initialize();
    PyObject* my_module = PyImport_ImportModule("PythonCode");
    PyErr_Print();
    PyObject* my_function = PyObject_GetAttrString(my_module, procname);
    PyObject* my_result = PyObject_CallObject(my_function, NULL);
    Py_Finalize();

    delete[] procname;
}


int callIntFunc(string proc, string param)
{
    char* procname = new char[proc.length() + 1];
    std::strcpy(procname, proc.c_str());

    char* paramval = new char[param.length() + 1];
    std::strcpy(paramval, param.c_str());


    PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
    // Initialize the Python Interpreter
    Py_Initialize();
    // Build the name object
    pName = PyUnicode_FromString((char*)"PythonCode");
    // Load the module object
    pModule = PyImport_Import(pName);
    // pDict is a borrowed reference 
    pDict = PyModule_GetDict(pModule);
    // pFunc is also a borrowed reference 
    pFunc = PyDict_GetItemString(pDict, procname);
    if (PyCallable_Check(pFunc))
    {
        pValue = Py_BuildValue("(z)", paramval);
        PyErr_Print();
        presult = PyObject_CallObject(pFunc, pValue);
        PyErr_Print();
    }
    else
    {
        PyErr_Print();
    }
    //printf("Result is %d\n", _PyLong_AsInt(presult));
    Py_DECREF(pValue);
    // Clean up
    Py_DECREF(pModule);
    Py_DECREF(pName);
    // Finish the Python Interpreter
    Py_Finalize();

    // clean 
    delete[] procname;
    delete[] paramval;

    return _PyLong_AsInt(presult);
}


void UserMenu()
{
    // Displays menu to the user
    cout << "1: List of items purchased and how many \n";
    cout << "2: How many times a certain item was purchased \n";
    cout << "3: Sales data histogram \n";
    cout << "4: Exit \n\n";
    
    // Uses user input as option
    cin >> userInput;

    if (userInput == 1)
    {
        // Uses function that displays items purchased and quantity
        cout << "\n\nDisplaying items purchased and quantity: \n\n";
        CallProcedure("AddingItems");
        cout << "\n\n";
        return;
    }
    else if (userInput == 2)
    {
        // User inputs a specific item to store
        cout << "\n\nEnter item name: \n\n";
        cin >> str;
        cout << "\n\n";
        cout << "Displaying purchase amount of " << str << ":\n\n";
        // Calls the functions depending on the item selected
        cout << str << ": " << callIntFunc("ItemCounter", str) << "\n\n";
        return;
    }
    else if (userInput == 3)
    {
        // Getting amount from input to output file
        cout << "\n\nStoring items purchased/quantity to file: \n\n";
        CallProcedure("ItemStore");
        cout << "\n\n";
        // Read data from output
        ifstream frequencyFile("frequency.dat");
        string item;
        int count;
        // Print histogram from data
        while (getline(frequencyFile, fileLine))
        {
            istringstream iss(fileLine);
            if (!(iss >> item >> count)) { break; } // error
            // Print the item name and "count" number of asterisks
            cout << item << " " << string(count, '*') << endl;
        }
        cout << "\n\n";
        return;
    }
    else if (userInput == 4)
    {
        //When user input is 4 exit
        cout << "\n\nExiting\n\n";
        exit(EXIT_SUCCESS);
    }
    else
    {
        // Sends user back to beginning if they dont choose valid option
        cout << "\n\nEnter valid input \n\n";
        return;
    }
}


int main()
{
    // Looping back to menu unless user chooses to exit
    while (1)
    {
        UserMenu();
    }

    return 0;
}