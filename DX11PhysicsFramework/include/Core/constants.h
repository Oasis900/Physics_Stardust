#pragma once
#include <cmath>
#include <corecrt_math_defines.h>

/* Universal Gravitational Constant */
static constexpr double k_G = 6.67E-10;

/* Number of bodies to be run in the simulation */
static constexpr int k_Body_Count = 10;

/* Mass constants - scaled for OpenFrameworks */
static constexpr float k_Mass_Scale = 1E-4;
static constexpr double k_Solar_Mass = 1.99E10;
static constexpr double k_Solar_Volume = 1.41E8;
static constexpr double k_Solar_Density = k_Solar_Mass / k_Solar_Volume;
static constexpr double k_Planet_Mass = 5.972E4;
static constexpr double k_Planet_Volume = 1.083;
static constexpr double K_Planet_Density = k_Planet_Mass / k_Planet_Volume;
const double k_Solar_Radius = pow(((3 * k_Solar_Mass/k_Solar_Density)/(4 * M_PI)), 1.0f/3.0f);
const double K_Planet_Radius =  pow(((3 * k_Planet_Mass/K_Planet_Density)/(4 * M_PI)), 1.0f/3.0f);
