#pragma once

/* Universal Gravitational Constant */
static constexpr double k_G = 6.67E-10;

/* Number of bodies to be run in the simulation */
static constexpr int k_Body_Count = 500;

/* Mass constants - scaled for OpenFrameworks */
static constexpr double k_Mass_Scale = 1E-6;
static constexpr double k_Solar_Mass = 1.989E10;
static constexpr double k_Solar_Mass_Scaled = k_Mass_Scale * k_Solar_Mass;

/* Time constants - scaled due to mass scaling */
static constexpr double k_Time_Scale = 1E-10;
static constexpr double k_Seconds_In_Year = 3.154E7;

/* Random velocity range for bodies */
static constexpr int k_Meters_In_Kilometers = 100;
static constexpr double K_Min_Velocity = -0.5 * k_Meters_In_Kilometers;
static constexpr double k_Max_Velocity = 0.5 * k_Meters_In_Kilometers;

/* Random mass range for bodies */
static constexpr double k_Min_Mass = 0.025 * k_Solar_Mass_Scaled;
static constexpr double k_Max_Mass = 10 * k_Solar_Mass_Scaled;

/* Random radius range for bodies */
static constexpr double k_Min_Radius = 5;
static constexpr double k_Max_Radius = 25;