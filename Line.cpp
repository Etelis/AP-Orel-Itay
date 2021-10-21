/*
 * animaly_detection_util.cpp
 *
 * Author: Itay Etelis - 209041474.
 *         Orel Ben Shamay - 318869658.
 */

#include "Line.h"
Line::Line(): a(0), b(0){}
Line::Line(float a, float b): a(a), b(b) {}
float Line::f(float x) const {return a*x+b;}
