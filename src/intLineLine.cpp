#include "intLineLine.h"
#include <iostream>

//TODO: Tol control
//MARK: check diff between this and OCC

//return a 0-PI angle
double lineLineAngle(const glm::dvec3&  a, const glm::dvec3& b)
{
    using vec3 = glm::dvec3;

    vec3 x = glm::normalize(a);
    vec3 y = glm::normalize(b);
    double cos = glm::dot(x, y);

    if (cos > -0.7 && cos < 0.7)
        return acos(cos);
    else 
    {
        double sin = glm::length(glm::cross(x, y));

        return cos > 0 ? asin(sin) : PI - asin(sin);
    }
}

double pointLineDistance(const glm::dvec3&  a, const GeoLine<>& line)
{
    using namespace glm;
    const dvec3 pOnLine = line.getP1();
    dvec3 tempVec = a - pOnLine;
    dvec3 resVec = cross(tempVec, dvec3(normalize(line.dir)));
    return length(resVec);
}

bool IntLineLine::isLineLinecoplanar() const
{
    auto p1 = line1.getP1();
    double x1 = p1.x;
    double y1 = p1.y;
    double z1 = p1.z;

    auto p2 = line2.getP1();
    double x2 = p2.x;
    double y2 = p2.y;
    double z2 = p2.z;
    glm::mat<3, 3, double> coplanarMat(x2 - x1,     y2 - y1,     z2 - z1,
                                       line1.dir.x, line1.dir.y, line1.dir.z,
                                       line2.dir.x, line2.dir.y, line2.dir.z);

    double coplanarFlag = glm::determinant(coplanarMat);//solve determinant of a 3 order matrix

    return (fabs(coplanarFlag) > precision) ? false : true;
}

void IntLineLine::perform()
{
    //non-coplanar
    if (!isLineLinecoplanar())
    {
        intStatus = LineLineIntRes::NOINT;
        return;
    }

    //coplanar
    double angle = lineLineAngle(line1.dir, line2.dir);
    if ( angle < precision || fabs(PI - angle) < precision)
    {
        // if (pointLineDistance(line1.getP1(), line2) > precision) // parallel
        if (pointLineDistance(line1.getP1(), line2) > line1.tol + line2.tol) // parallel
        {
            intStatus = LineLineIntRes::NOINT;
            return;
        }
        else //colinear
        {
            double t21 = line2.getPointPara(line1.getP1());
            double t22 = line2.getPointPara(line1.getP2());

            if (t21 > t22)
                std::swap (t21, t22);
            
            double line2t1 = line2.t1;
            double line2t2 = line2.t2;
            if (line2t1>line2t2)
                std::swap(line2t1, line2t2);
            
            if ((t21 < line2t1 && t22 < line2t1) || (t21 > line2t2 && t22 > line2t2))
            {
                //projection is out of range
                intStatus = LineLineIntRes::NOINT;
                return;
            }

            commonPart = line2;

            commonPart.setRange((t21 < line2t1) ? line2t1 : t21, (t22 < line2t2) ? t22 : line2t2);

            intStatus = (fabs(commonPart.t1 - commonPart.t2) < precision) ? LineLineIntRes::VERTEX : LineLineIntRes::COLINEAR;

            return;
        }
    }
    else //intersect
    {
        //MARK: there's a diff with OCC's, need check (OCC IntTools_EdgeEdge line:925)
        glm::dvec3 tempVec = line2.getP1() - line1.getP1();
        double sineOfAngle = glm::length(glm::cross(glm::normalize(line1.dir), glm::normalize(line2.dir)));
        //MARK: should be same as: double sineOfAngle = sin(angle); 

        double temp = glm::dot(line1.dir*(glm::dot(tempVec, line1.dir))-tempVec, line2.dir);
        double aT2 = temp / pow(sineOfAngle, 2);
        double aT1 = line1.getPointPara(line2.getPoint(aT2));

        if (aT2 < line2.t1 || aT2 > line2.t2 || aT1 < line1.t1 || aT1 > line1.t2)
        {
            //out of range
            intStatus = LineLineIntRes::NOINT;
            return;
        }
        //MARK: there's a diff with OCC's, need check (OCC IntTools_EdgeEdge line:961)
        commonPart = line1;
        commonPart.setRange(aT1, aT1);

        intStatus = LineLineIntRes::VERTEX;
        return;
    }
    printf("line line intersection finish.\n");
}