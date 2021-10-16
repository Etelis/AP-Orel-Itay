//
// Created by itay on 16/10/2021.
//

#include "Line.h"
Line::Line(): a(0), b(0){}
Line::Line(float a, float b): a(a), b(b) {}
float Line::f(float x) const {return a*x+b;}
