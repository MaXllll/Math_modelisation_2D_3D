//
//  Point.cpp
//  TP1
//
//  Created by Maxime Lahaye on 04/11/14.
//  Copyright (c) 2014 Maxime Lahaye. All rights reserved.
//
#include "Point.h"

Point::Point()
{
    this->x_ = 0.0f;
    this->y_ = 0.0f;
}

Point::Point(float x, float y, float z)
{
    this->x_ = x;
    this->y_ = y;
	this->z_ = z;
}

Point::Point(const Point &p)
{
    this->x_ = p.x_;
    this->y_ = p.y_;
	this->z_ = p.z_;
}


std::ostream& operator<<(std::ostream& out, const Point &p)
{
    out<<"("<<p.x_<<","<<p.y_ <<","<<p.z_<<")";
    return out;
}

Point::~Point(void)
{
    
}