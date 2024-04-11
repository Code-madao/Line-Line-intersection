#pragma once

#include <iostream>
#include <glm/glm.hpp>

#define PI 3.141592653589
//TODO: maybe redesign commonPart's DS
template <typename Type = double>
struct GeoLine
{
    glm::vec<3, Type> loc; //location point, default para is 0
    glm::vec<3, Type> dir; //normalized direction
    Type tol; // tolerence

    Type t1, t2;//begin and end parameter t for line segment

    GeoLine() : loc(glm::vec<3, Type>(0)), dir(glm::vec<3, Type>(0)), t1(Type(0)), t2(Type(0)), tol(Type(0)) {}

    // template <typename T>
    // GeoLine(const GeoLine<T> &input) : loc(input.loc), dir(input.dir), t1(input.t1), t2(input.t2), tol(input.tol) {}

    // template <typename T>
    // GeoLine<T>& operator=(const GeoLine<T> &input)
    // {
    //     printf("this is =\n");
    //     loc = input.loc;
    //     dir = input.dir;
    //     tol = input.tol;
    //     t1 = input.t1;
    //     t2 = input.t2;
    // }

    template <typename T>
    GeoLine(glm::vec<3, T> loc, glm::vec<3, T> dir, Type t1, Type t2, T tol = 0.)
    {
        this->loc = loc;
        this->dir = glm::normalize(dir);
        this->t1 = t1;
        this->t2 = t2;
        this->tol = tol;
    }

    void setRange(Type tf, Type tl)
    {
        t1 = tf;
        t2 = tl;
    }

    glm::vec<3, Type> getPoint(Type t) const { return dir * t + loc; }

    glm::vec<3, Type> getLoc() const { return loc; }

    //return middle point of line segment
    glm::vec<3, Type> getMid() const { return dir * (t2 + t1) / 2. + loc; }

    //return begin point of line segment
    glm::vec<3, Type> getP1() const { return getPoint(t1); } 

    //return end point of line segment
    glm::vec<3, Type> getP2() const { return getPoint(t2); } 

    Type getPointPara(const glm::vec<3, Type>& p) const
    {
        return glm::dot(p - loc, dir);
        // Type dif = glm::length(tVec);

        // return (glm::dot(tVec, dir) > 0) ? t1 + dif : t1 - dif;
    }

    void printInfo() const 
    {
        printf("loc: %.2lf, %.2lf, %.2lf\n", loc.x, loc.y, loc.z);
        printf("dir: %.2lf, %.2lf, %.2lf\n", dir.x, dir.y, dir.z);
        printf("t1: %.2lf, t2: %.2lf\n", t1, t2);
    }
    
    ~GeoLine(){}
};

class IntLineLine
{
public:
    enum LineLineIntRes 
    {
        NOINT,
        VERTEX,
        COLINEAR
    };

    IntLineLine(){};

    IntLineLine(const GeoLine<double> &l1, const GeoLine<double> &l2, double ttol = 0., double tprecision = 1e-6)
    : line1(l1), line2(l2), tol(ttol), precision(tprecision), intStatus(LineLineIntRes::NOINT){}

    bool isLineLinecoplanar() const;
    void perform();

    LineLineIntRes resStatus() const{ return intStatus; }

    GeoLine<double> result() const { return commonPart; }

    ~IntLineLine(){}

private:
    GeoLine<double> line1, line2;
    double tol;
    double precision;
    GeoLine<double> commonPart;// it's a point when lines intersect, and a line segment when colinear
    LineLineIntRes intStatus;
};
