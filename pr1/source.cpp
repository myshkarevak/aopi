#include <iostream>
#include <math.h>
using namespace std;

float requestCoefficient(const char identifier)
{
    float value = 0;
    cout << "Please type coefficient " << identifier << endl
         << identifier << " = ";
    cin >> value; // program will fail if not float
    return value;
}

float calculateDiscriminant(const float coefficientA, const float coefficientB, const float coefficientC)
{
    return pow(coefficientB, 2) - 4 * coefficientA * coefficientC;
}

float calculateFirstRoot(const float discriminant, const float coefficientA, const float coefficientB)
{
    return ((-1) * coefficientB + sqrt(discriminant)) / (2 * coefficientA);
}

float calculateSecondRoot(const float discriminant, const float coefficientA, const float coefficientB)
{
    return ((-1) * coefficientB - sqrt(discriminant)) / (2 * coefficientA);
}

int main()
{
    system("cls");

    const float coefficientA = requestCoefficient('A');
    const float coefficientB = requestCoefficient('B');
    const float coefficientC = requestCoefficient('C');

    if (coefficientA != 0)
    {
        const float discriminant = calculateDiscriminant(coefficientA, coefficientB, coefficientC);
        cout << endl << "Discriminant = " << discriminant << "." << endl;

        if (discriminant < 0)
        {
            cout << "Discriminant < 0. No real roots." << endl;
        }
        else if (discriminant == 0)
        {
            cout << "Discriminant = 0. Equation root x = " 
                << calculateFirstRoot(discriminant, coefficientA, coefficientB)
                << "." << endl;
        }
        else
        {
            cout << "Equation roots are: x1 = "
                << calculateFirstRoot(discriminant, coefficientA, coefficientB)
                << ", x2 = " << calculateSecondRoot(discriminant, coefficientA, coefficientB)
                << "." << endl;
        }
    }
    else
    {
        if (coefficientB != 0)
        {
            cout << "Equation root x = " << (-1) * coefficientC / coefficientB << "." << endl;
        }
        else if (coefficientC != 0)
        {
            cout << "Equation has no solutions." << endl;
        }
        else
        {
            cout << "Any x counts as a solution." << endl;
        }
    }

    system("pause");
    return 0;
}
