#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double tetrahedronVolume(double x1, double y1, double z1, double x2, double y2, double z2, double x3, double y3, double z3, double x4, double y4, double z4)
{

    double a1 = (x2 - x1), b1 = (y2 - y1), c1 = (z2 - z1);
    double a2 = (x3 - x1), b2 = (y3 - y1), c2 = (z3 - z1);
    double a3 = (x4 - x1), b3 = (y4 - y1), c3 = (z4 - z1);

    double determinant = (a1 * ((b2 * c3) - (b3 * c2))) - (b1 * ((a2 * c3) - (a3 * c2))) + (c1 * ((a2 * b3) - (a3 * b2)));

    double volume = fabs(determinant) / 6.0;
    return volume;
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
    Input = fopen("Mesh/cube.msh", "r");

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
    double NodeCoordinate[n][3];
    int k = n;

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
            sscanf(buffer, "%lf %lf %lf", &a, &b, &c);
            NodeCoordinate[g][0] = a;
            NodeCoordinate[g][1] = b;
            NodeCoordinate[g][2] = c;
            g++;
        }

        f += e;
    }

    for (int i = 0; i < 3; i++)
    {
        fgets(buffer, 100, Input);
    }

    sscanf(buffer, "%d %d %d %d", &n, &n, &n, &n);
    int ElementNodes[n][4];

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
            }
        }

        else if (e == 4)
        {
            for (int i = 0; i < g; i++)
            {
                fgets(buffer, 100, Input);
                sscanf(buffer, "%lf %lf %lf %d %d", &a, &b, &c, &f, &h);
                ElementNodes[count][0] = b;
                ElementNodes[count][1] = c;
                ElementNodes[count][2] = f;
                ElementNodes[count][3] = h;
                count++;
            }
        }
        d += g;
    }

    int ElementNodesDuplicate[count][4];

    for (int i = 0; i < count; i++)
    {
        ElementNodesDuplicate[i][0] = ElementNodes[i][0];
        ElementNodesDuplicate[i][1] = ElementNodes[i][1];
        ElementNodesDuplicate[i][2] = ElementNodes[i][2];
        ElementNodesDuplicate[i][3] = ElementNodes[i][3];
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

    double y21, y31, y41, x21, x31, x41, z21, z31, z41, V;
    double M11, M12, M13, M21, M22, M23, M31, M32, M33;
    double phi1x, phi1y, phi1z, phi2x, phi2y, phi2z, phi3x, phi3y, phi3z, phi4x, phi4y, phi4z;

    for (int i = 0; i < count; i++)
    {
        V = tetrahedronVolume(NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][0] - 1][2], NodeCoordinate[ElementNodesDuplicate[i][1] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][1] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][1] - 1][2], NodeCoordinate[ElementNodesDuplicate[i][2] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][2] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][2] - 1][2], NodeCoordinate[ElementNodesDuplicate[i][3] - 1][0], NodeCoordinate[ElementNodesDuplicate[i][3] - 1][1], NodeCoordinate[ElementNodesDuplicate[i][3] - 1][2]);

        x21 = ((NodeCoordinate[ElementNodesDuplicate[i][1] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0]));
        x31 = ((NodeCoordinate[ElementNodesDuplicate[i][2] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0]));
        x41 = ((NodeCoordinate[ElementNodesDuplicate[i][3] - 1][0]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][0]));
        y21 = ((NodeCoordinate[ElementNodesDuplicate[i][1] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1]));
        y31 = ((NodeCoordinate[ElementNodesDuplicate[i][2] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1]));
        y41 = ((NodeCoordinate[ElementNodesDuplicate[i][3] - 1][1]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][1]));
        z21 = ((NodeCoordinate[ElementNodesDuplicate[i][1] - 1][2]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][2]));
        z31 = ((NodeCoordinate[ElementNodesDuplicate[i][2] - 1][2]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][2]));
        z41 = ((NodeCoordinate[ElementNodesDuplicate[i][3] - 1][2]) - (NodeCoordinate[ElementNodesDuplicate[i][0] - 1][2]));

        M11 = ((y31 * z41) - (z31 * y41));
        M12 = ((z21 * y41) - (y21 * z41));
        M13 = ((y21 * z31) - (z21 * y31));
        M21 = ((z31 * x41) - (x31 * z41));
        M22 = ((x21 * z41) - (z21 * x41));
        M23 = ((z21 * x31) - (x21 * z31));
        M31 = ((x31 * y41) - (y31 * x41));
        M32 = ((y21 * x41) - (x21 * y41));
        M33 = ((x21 * y31) - (y21 * x31));

        phi1x = (M11 + M12 + M13) * (-1);
        phi1y = (M21 + M22 + M23) * (-1);
        phi1z = (M31 + M32 + M33) * (-1);
        phi2x = M11;
        phi2y = M21;
        phi2z = M31;
        phi3x = M12;
        phi3y = M22;
        phi3z = M32;
        phi4x = M13;
        phi4y = M23;
        phi4z = M33;

        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][0] - 1] += -((phi1x * phi1x) + (phi1y * phi1y) + (phi1z * phi1z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][1] - 1] += -((phi1x * phi2x) + (phi1y * phi2y) + (phi1z * phi2z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][2] - 1] += -((phi1x * phi3x) + (phi1y * phi3y) + (phi1z * phi3z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][0] - 1][ElementNodesDuplicate[i][3] - 1] += -((phi1x * phi4x) + (phi1y * phi4y) + (phi1z * phi4z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][0] - 1] += -((phi2x * phi1x) + (phi2y * phi1y) + (phi2z * phi1z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][1] - 1] += -((phi2x * phi2x) + (phi2y * phi2y) + (phi2z * phi2z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][2] - 1] += -((phi2x * phi3x) + (phi2y * phi3y) + (phi2z * phi3z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][1] - 1][ElementNodesDuplicate[i][3] - 1] += -((phi2x * phi4x) + (phi2y * phi4y) + (phi2z * phi4z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][0] - 1] += -((phi3x * phi1x) + (phi3y * phi1y) + (phi3z * phi1z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][1] - 1] += -((phi3x * phi2x) + (phi3y * phi2y) + (phi3z * phi2z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][2] - 1] += -((phi3x * phi3x) + (phi3y * phi3y) + (phi3z * phi3z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][2] - 1][ElementNodesDuplicate[i][3] - 1] += -((phi3x * phi4x) + (phi3y * phi4y) + (phi3z * phi4z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][3] - 1][ElementNodesDuplicate[i][0] - 1] += -((phi4x * phi1x) + (phi4y * phi1y) + (phi4z * phi1z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][3] - 1][ElementNodesDuplicate[i][1] - 1] += -((phi4x * phi2x) + (phi4y * phi2y) + (phi4z * phi2z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][3] - 1][ElementNodesDuplicate[i][2] - 1] += -((phi4x * phi3x) + (phi4y * phi3y) + (phi4z * phi3z)) / (36 * V);
        Stiffness[ElementNodesDuplicate[i][3] - 1][ElementNodesDuplicate[i][3] - 1] += -((phi4x * phi4x) + (phi4y * phi4y) + (phi4z * phi4z)) / (36 * V);

        RHS[ElementNodesDuplicate[i][0] - 1] += ((4 * V) / 4);
        RHS[ElementNodesDuplicate[i][1] - 1] += ((4 * V) / 4);
        RHS[ElementNodesDuplicate[i][2] - 1] += ((4 * V) / 4);
        RHS[ElementNodesDuplicate[i][3] - 1] += ((4 * V) / 4);
    }

    double Surface1 = 1, Surface2 = 1, Surface3 = 1, Surface4 = 1, Surface5 = 1, Surface6 = 1;

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

            RHS[i] = Surface1;
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

            RHS[i] = Surface2;
        }

        else if (NodeCoordinate[i][2] == 0)
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

            RHS[i] = Surface3;
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

            RHS[i] = Surface4;
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

            RHS[i] = Surface5;
        }

        else if (NodeCoordinate[i][2] == 4)
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

            RHS[i] = Surface6;
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

    Output = fopen("cube.csv", "w");

    fprintf(Output, "x,y,z,voltage\n");

    for (int j = 0; j < k; j++)
    {
        fprintf(Output, "%lf,%lf,%lf,%lf\n", NodeCoordinate[j][0], NodeCoordinate[j][1], NodeCoordinate[j][2], RHS[j]);
    }
}