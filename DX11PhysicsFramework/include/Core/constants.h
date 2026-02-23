#pragma once
#include <cmath>
#include <corecrt_math_defines.h>

/* Drag Co-Efficient of Sphere in Earth Air */
constexpr float sphere_co_efficient = 0.47f;

/* Universal Gravitational Constant */
constexpr double k_G = 6.67E-11;

/* Number of bodies to be run in the simulation */
constexpr int k_Body_Count = 5;

/* Mass constants - scaled for OpenFrameworks */
constexpr double k_Mass_Scale = 1E-4;
constexpr double k_Solar_Mass = 1.99E12;
constexpr double k_Planet_Mass = 5.972E6;

const double k_Solar_Radius = pow(((3 * 40.0f)/(4 * M_PI)), 1.0f/3.0f);
const double k_Solar_Volume = 4.0f/3.0f * M_PI * pow(k_Solar_Radius, 3);
const double k_Solar_Density = k_Solar_Mass * k_Mass_Scale / k_Solar_Volume;

const double K_Planet_Radius =  pow(((3 * 19.0f)/(4 * M_PI)), 1.0f/3.0f);
const double k_Planet_Volume = 4.0f/3.0f * M_PI * pow(K_Planet_Radius, 3);
const double K_Planet_Density = k_Planet_Mass * k_Mass_Scale / k_Planet_Volume;

const double relative_Density = k_Solar_Density - K_Planet_Density;
