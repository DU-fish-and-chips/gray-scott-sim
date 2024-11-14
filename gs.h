//
// gs.h
//

#pragma once

#include "gtest/gtest.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
// 全局变量声明
extern const int width;
extern const int height;
extern double Du;
extern double Dv;
extern double F;
extern double k;
extern double threshold;
extern const double dt;
extern const int numIterations;
extern const int outputInterval;

extern std::vector<std::vector<double>> u;
extern std::vector<std::vector<double>> v;

// 函数声明
void init();
void writeVTKFile(int iteration);
void simulateStep();
double countElementsAboveThreshold(double threshold);
