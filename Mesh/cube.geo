lc = 0.8; // Size of meshing near the points
a = 4; // Size of cube

// Points in cube

Point(1) = {0, 0, 0, lc};
Point(2) = {a, 0, 0, lc};
Point(3) = {0, a, 0, lc};
Point(4) = {0, 0, a, lc};
Point(5) = {a, a, 0, lc};
Point(6) = {0, a, a, lc};
Point(7) = {a, 0, a, lc};
Point(8) = {a, a, a, lc};

// Edges in cube

Line(1) = {1, 2};
Line(2) = {1, 3};
Line(3) = {1, 4};
Line(4) = {4, 7};
Line(5) = {7, 2};
Line(6) = {2, 5};
Line(7) = {5, 3};
Line(8) = {3, 6};
Line(9) = {6, 4};
Line(10) = {6, 8};
Line(11) = {8, 5};
Line(12) = {8, 7};

// Surfaces in cube

Curve Loop(1) = {3, 4, 5, -1};
Curve Loop(2) = {12, -4, -9, 10};
Curve Loop(3) = {5, 6, -11, 12};
Curve Loop(4) = {-3, 2, 8, 9};
Curve Loop(5) = {-1, 2, -7, -6};
Curve Loop(6) = {7, 8, 10, 11};

Plane Surface(1) = {1};
Plane Surface(2) = {2};
Plane Surface(3) = {3};
Plane Surface(4) = {4};
Plane Surface(5) = {5};
Plane Surface(6) = {6};

// Volume enclosed by cube

Surface Loop(1) = {1, 2, 3, 4, 5, 6};

Volume(1) = {1};