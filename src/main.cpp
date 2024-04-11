#include <iostream>
#include "intLineLine.h"

/*already tested: coincide/colinear/common-intersecting/parallel/
                  extreme close/
*/
void test01()
{
    using vec3 = glm::dvec3;

    vec3 temp1(2, 2, 0);
    GeoLine<double> l1(vec3(0), temp1, 0, 4);
    vec3 temp2(2, 2.00, 0);
    GeoLine<double> l2(vec3(0.00, 0, 0), temp2, 3.9999999, 5);

    // l1.printInfo();
    // l2.printInfo();

    IntLineLine lineLineInt(l1, l2);
    lineLineInt.perform();

    switch (lineLineInt.resStatus())
    {
    case IntLineLine::LineLineIntRes::NOINT:
        printf("no intersection.\n");
        break;

    case IntLineLine::LineLineIntRes::VERTEX:
        printf("intersect at a point.\n");
        lineLineInt.result().printInfo();
        // vec3 res = lineLineInt.result().getP1();
        // printf("intersect at a point: %.2lf, %.2lf, %.2lf\n", res.x, res.y, res.z);
        break;

    case IntLineLine::LineLineIntRes::COLINEAR:
        printf("colinear.\n");
        lineLineInt.result().printInfo();
        break;

    default:
        break;
    }
}

int main(int argc, char const *argv[])
{
    test01();

    return 0;
}
