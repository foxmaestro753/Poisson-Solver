#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matrixmult(int n, double array1[][n], double array2[][n], double array3[][n])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array3[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                array3[i][j] += (array1[i][k] * array2[k][j]);
            }
        }
    }
}

void matrixmult1(int n, double array1[][n], double array2[], double array3[])
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            array3[i] = 0;
            for (int k = 0; k < n; k++)
            {
                array3[i] += (array1[i][k] * array2[k]);
            }
        }
    }
}

int main()
{

    int n = 100;
    double h = (200e-9 / (n - 1));
    double Stiffness[n][n];
    double RHS[n];

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            Stiffness[i][j] = 0;
        }
    }

    for (int j = 0; j < n; j++)
    {
        RHS[j] = 0;
    }

    for (int i = 1; i < n; i++)
    {
        Stiffness[i - 1][i - 1] += -1 / h;
        Stiffness[i - 1][i] += 1 / h;
        Stiffness[i][i - 1] += 1 / h;
        Stiffness[i][i] += -1 / h;

        RHS[i - 1] += ((2 * h) / 2);
        RHS[i] += ((2 * h) / 2);
    }

    double Vleft = 1, Vright = 2;

    for (int j = 1; j < n; j++)
    {
        Stiffness[0][j] = 0;
    }

    for (int j = 0; j < n - 1; j++)
    {
        Stiffness[n - 1][j] = 0;
    }

    Stiffness[0][0] = 1;
    Stiffness[n - 1][n - 1] = 1;
    RHS[0] = Vleft;
    RHS[n - 1] = Vright;

    double transform[n][n];
    double product1[n][n];
    double product2[n];
    double z;

    for (int i = 0; i < n; i++)
    {

        if (Stiffness[i][i] == 0)
        {
            double r = 1;

            for (int j = 0; j < n; j++)
            {
                if (Stiffness[j][i] != 0)
                {
                    r = 0;
                    break;
                }
            }

            if (r == 1)
            {
                continue;
            }

            double max = fabs(Stiffness[0][i]);
            int p = 0;

            for (int j = 1; j < n; j++)
            {
                if (fabs(Stiffness[j][i]) >= max)
                {
                    max = fabs(Stiffness[j][i]);
                    p = j;
                }
            }

            double l = 0, b = 0;

            for (int j = 0; j < n; j++)
            {
                l = Stiffness[p][j];
                Stiffness[p][j] = Stiffness[i][j];
                Stiffness[i][j] = l;
            }

            b = RHS[p];
            RHS[p] = RHS[i];
            RHS[i] = b;
        }

        if (Stiffness[i][i] != 1)
        {
            z = Stiffness[i][i];
            for (int p = 0; p < n; p++)
            {
                Stiffness[i][p] = Stiffness[i][p] / z;
            }

            RHS[i] = RHS[i] / z;
        }

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (i == j)
                {
                    transform[i][j] = 1;
                }
                else
                {
                    transform[i][j] = 0;
                }
            }
        }

        for (int j = 0; j < n; j++)
        {
            if (j != i)
            {
                transform[j][i] = -Stiffness[j][i];
            }
        }

        matrixmult(n, transform, Stiffness, product1);
        matrixmult1(n, transform, RHS, product2);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Stiffness[i][j] = product1[i][j];
            }
        }

        for (int i = 0; i < n; i++)
        {
            RHS[i] = product2[i];
        }
    }

    FILE *Output = fopen("line.csv", "w");

    fprintf(Output,"x,voltage\n");

    for (int j = 0; j < n; j++)
    {
        fprintf(Output,"%e,%e\n", h*j, RHS[j]);
    }
}