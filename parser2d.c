#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double dist(double x1, double y1, double x2, double y2)
{
    double distance;
    distance = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
    return distance;
}

double area(double x1, double y1, double x2, double y2, double x3, double y3)
{
    double a = dist(x1, y1, x2, y2);
    double b = dist(x2, y2, x3, y3);
    double c = dist(x3, y3, x1, y1);

    double s = (a + b + c) / 2;
    double area = sqrt(s * (s - a) * (s - b) * (s - c));
    return area;
}

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
    FILE *Input, *Output;
    Input = fopen("Mesh/square.msh", "r");

    int d, e, f, g, h, m, n;
    double a, b, c;
    char buffer[100];

    for (int i = 0; i < 5; i++)
    {
        fgets(buffer, 100, Input);
    }

    sscanf(buffer, "%d %d %d %d", &d, &e, &f, &g);

    for (int i = 0; i < d; i++)
    {
        fgets(buffer, 100, Input);
    }

    for (int i = 0; i < e; i++)
    {
        fgets(buffer, 100, Input);
    }

    for (int i = 0; i < f; i++)
    {
        fgets(buffer, 100, Input);
    }

    for (int i = 0; i < g; i++)
    {
        fgets(buffer, 100, Input);
    }

    for (int i = 0; i < 3; i++)
    {
        fgets(buffer, 100, Input);
    }

    sscanf(buffer, "%d %d %d %d", &n, &n, &n, &n);
    int k = n;
    double NodeCoordinate[n][2];

    f = 0;
    g = 0;

    while (f < n)
    {
        fgets(buffer, 100, Input);
        sscanf(buffer, "%d %d %d %d", &e, &e, &e, &e);

        for (int i = 0; i < e; i++)
        {
            fgets(buffer, 100, Input);
        }

        for (int i = 0; i < e; i++)
        {
            fgets(buffer, 100, Input);
            sscanf(buffer, "%lf %lf", &a, &b);
            NodeCoordinate[g][0] = a;
            NodeCoordinate[g][1] = b;
            g++;
        }

        f += e;
    }

    for (int i = 0; i < 3; i++)
    {
        fgets(buffer, 100, Input);
    }

    sscanf(buffer, "%d %d %d %d", &n, &n, &n, &n);
    int ElementNodes[n][3];
    int count = 0;
    d = 0;

    while (d < n)
    {
        fgets(buffer, 100, Input);
        sscanf(buffer, "%d %d %d %d", &f, &f, &e, &g);

        if (e == 15)
        {
            for (int i = 0; i < g; i++)
            {
                fgets(buffer, 100, Input);
            }
        }

        else if (e == 1)
        {
            for (int i = 0; i < g; i++)
            {
                fgets(buffer, 100, Input);
            }
        }

        else if (e == 2)
        {
            for (int i = 0; i < g; i++)
            {
                fgets(buffer, 100, Input);
                sscanf(buffer, "%lf %lf %lf %d", &a, &b, &c, &f);
                ElementNodes[count][0] = b;
                ElementNodes[count][1] = c;
                ElementNodes[count][2] = f;
                count++;
            }
        }
        d += g;
    }

    int ElementNodesDuplicate[count][3];

    for (int i = 0; i < count; i++)
    {
        ElementNodesDuplicate[i][0] = ElementNodes[i][0];
        ElementNodesDuplicate[i][1] = ElementNodes[i][1];
        ElementNodesDuplicate[i][2] = ElementNodes[i][2];
    }

    double Stiffness[k][k];
    double RHS[k];

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < k; j++)
        {
            Stiffness[i][j] = 0;
        }
    }

    for (int j = 0; j < k; j++)
    {
        RHS[j] = 0;
    }

    double y12, y23, y31, x21, x32, x13, A;

    for (int i = 0; i < count; i++)
    {
        A = area(NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][1] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][1] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][2] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][2] - 1][1]);

        y12 = ((NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][1] - 1][1]));
        y23 = ((NodeCoordinate[ElementNodesDuplicate[i][1] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][2] - 1][1]));
        y31 = ((NodeCoordinate[ElementNodesDuplicate[i][2] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1]));
        x21 = ((NodeCoordinate[ElementNodesDuplicate[i][1] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0]));
        x32 = ((NodeCoordinate[ElementNodesDuplicate[i][2] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][1] - 1][0]));
        x13 = ((NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][2] - 1][0]));

        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][0] - 1] += -((y23 * y23) + (x32 * x32)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][1] - 1] += -((y23 * y31) + (x32 * x13)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][2] - 1] += -((y23 * y12) + (x32 * x21)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][0] - 1] += -((y23 * y31) + (x32 * x13)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][1] - 1] += -((y31 * y31) + (x13 * x13)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][2] - 1] += -((y31 * y12) + (x13 * x21)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][0] - 1] += -((y23 * y12) + (x32 * x21)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][1] - 1] += -((y31 * y12) + (x13 * x21)) / (4 * A);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][2] - 1] += -((y12 * y12) + (x21 * x21)) / (4 * A);

        RHS[ElementNodesDuplicate[i][0] - 1] += ((4 * A) / 3);
        RHS[ElementNodesDuplicate[i][1] - 1] += ((4 * A) / 3);
        RHS[ElementNodesDuplicate[i][2] - 1] += ((4 * A) / 3);
    }

    double Vleft = 1, Vright = 1, Vdown = 1, Vup = 1;

    for (int i = 0; i < k; i++)
    {
        if (NodeCoordinate[i][0] == 0)
        {
            for (int j = 0; j < k; j++)
            {
                if (j == i)
                {
                    Stiffness[i][j] = 1;
                }
                else
                {
                    Stiffness[i][j] = 0;
                }
            }

            RHS[i] = Vleft;
        }

        else if (NodeCoordinate[i][1] == 0)
        {
            for (int j = 0; j < k; j++)
            {
                if (j == i)
                {
                    Stiffness[i][j] = 1;
                }
                else
                {
                    Stiffness[i][j] = 0;
                }
            }

            RHS[i] = Vdown;
        }

        else if (NodeCoordinate[i][0] == 4)
        {
            for (int j = 0; j < k; j++)
            {
                if (j == i)
                {
                    Stiffness[i][j] = 1;
                }
                else
                {
                    Stiffness[i][j] = 0;
                }
            }

            RHS[i] = Vright;
        }

        else if (NodeCoordinate[i][1] == 4)
        {
            for (int j = 0; j < k; j++)
            {
                if (j == i)
                {
                    Stiffness[i][j] = 1;
                }
                else
                {
                    Stiffness[i][j] = 0;
                }
            }

            RHS[i] = Vup;
        }
    }

    double transform[k][k];
    double product1[k][k];
    double product2[k];
    double z;

    for (int i = 0; i < k; i++)
    {

        if (Stiffness[i][i] == 0)
        {
            double r = 1;

            for (int j = 0; j < k; j++)
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

            for (int j = 1; j < k; j++)
            {
                if (fabs(Stiffness[j][i]) >= max)
                {
                    max = fabs(Stiffness[j][i]);
                    p = j;
                }
            }

            double l = 0, b = 0;

            for (int j = 0; j < k; j++)
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
            for (int p = 0; p < k; p++)
            {
                Stiffness[i][p] = Stiffness[i][p] / z;
            }

            RHS[i] = RHS[i] / z;
        }

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
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

        for (int j = 0; j < k; j++)
        {
            if (j != i)
            {
                transform[j][i] = -Stiffness[j][i];
            }
        }

        matrixmult(k, transform, Stiffness, product1);
        matrixmult1(k, transform, RHS, product2);

        for (int i = 0; i < k; i++)
        {
            for (int j = 0; j < k; j++)
            {
                Stiffness[i][j] = product1[i][j];
            }
        }

        for (int i = 0; i < k; i++)
        {
            RHS[i] = product2[i];
        }
    }

    Output = fopen("square.csv", "w");

    fprintf(Output,"x,y,voltage\n");

    for (int j = 0; j < k; j++)
    {
        fprintf(Output,"%lf,%lf,%lf\n", NodeCoordinate[j][0], NodeCoordinate[j][1], RHS[j]);
    }
}