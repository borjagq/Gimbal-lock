/**
 * @file turbulence.cpp
 * @brief Class that implemenets the methods to get pseudorandom turbulence.
 * @version 1.0.0 (2023-02-08)
 * @date 2023-02-08
 * @author Borja García Quiroga <garcaqub@tcd.ie>
 *
 *
 * Copyright (c) Borja García Quiroga, All Rights Reserved.
 *
 * The information and material provided below was developed as partial
 * requirements for the MSc in Computer Science at Trinity College Dublin,
 * Ireland.
 */

#include "turbulence.h"

#include <random>
#include <vector>
#include <cmath>

namespace bgq_opengl {

    Turbulence::Turbulence(int num_of_sins, float min_amplitude, float max_amplitude, float min_phi, float max_phi, float min_omega, float max_omega) {
        
        // Build the generators generator.
        std::default_random_engine generator;
        std::uniform_real_distribution<float> amplitude_dist(min_amplitude, max_amplitude);
        std::uniform_real_distribution<float> phi_dist(min_phi, max_phi);
        std::uniform_real_distribution<float> omega_dist(min_omega, max_omega);

        for (int i = 0; i < num_of_sins; ++i) {
            
            // Create the new sinusoid from the generators.
            Sinusoid new_sin{};
            new_sin.amplitude = amplitude_dist(generator);
            new_sin.phase = phi_dist(generator);
            new_sin.frequency = omega_dist(generator);
            
            this->partial_sinusoids.push_back(new_sin);

        }
        
    }

    float Turbulence::solveSinusoids(float x) {
        
        float y = 0;
        
        for (int i = 0; i < this->partial_sinusoids.size(); i++)
            y += solveSinusoid(this->partial_sinusoids[i], x);
        
        return y;
        
    }

    float Turbulence::solveSinusoid(Sinusoid sinusoid, float x) {

        return sinusoid.amplitude * sin((x + sinusoid.phase) * sinusoid.frequency);

    }

}  // namespace bgq_opengl
