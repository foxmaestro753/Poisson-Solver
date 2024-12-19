lc = 0.5; // Size of meshing near the points
a = 4; // Size of Square

// Points in Square

Point(1) = {a, a, 0, lc};
Point(2) = {a, 0, 0, lc};
Point(3) = {0, a, 0, lc};
Point(4) = {0, 0, 0, lc};

// Edges in Square

Line(1) = {4, 2};
Line(2) = {2, 1};
Line(3) = {1, 3};
Line(4) = {3, 4};

// Surfaces in Square

Curve Loop(1) = {1, 2, 3, 4};

Plane Surface(1) = {1};