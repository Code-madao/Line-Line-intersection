#include <iostream>
#include "intLineLine.h"

/*MARK: already tested: coincide/colinear/common-intersecting/parallel/
                  extreme close/
*/
void test01()
{
    using vec3 = glm::dvec3;

    vec3 temp1(2, 2, 2);
    GeoLine<double> l1(vec3(0), temp1, 0, 4);
    vec3 temp2(-2, 2.00, 2.0);
    GeoLine<double> l2(vec3(2.00, 0, 0), temp2, 0, 3);

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
