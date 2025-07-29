#include <limits>
#include <math.h>
#include <string>
#include <sstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <iostream>
#include <iomanip>


#pragma once

using namespace std;

 string Sort(queue<string>& otQueue,stack<string>& opStack);
 string Calculate(double& leftValue, string& op, double& rightValue);
 bool isCorrectInput(istringstream& iss);
