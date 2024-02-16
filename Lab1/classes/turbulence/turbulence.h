/**
 * @file turbulence.h
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

#ifndef BGQ_OPENGL_CLASSES_TURBULENCE_H_
#define BGQ_OPENGL_CLASSES_TURBULENCE_H_

#include <vector>

namespace bgq_opengl {

    /**
    * @brief Implementation of the psuedorandom turbulence class.
    *
    *  Implementation of a class that contains all the methods to achieve psuedorandom turbulence.
    *
    * @author Borja García Quiroga <garcaqub@tcd.ie>
    */
    class Turbulence {

        public:
            
            /**
             * @brief Initializes the pseudorandom generators.
             *
             * Initializes the pseudorandom generators
             *
             * @param num_of_sins The number of sinusoids.
             * @param min_amplitude Minimum amplitude for each sinusoid.
             * @param max_amplitude Minimum amplitude for each sinusoid.
             * @param min_phi Minimum phase for each sinusoid.
             * @param max_phi Maximum phase for each sinusoid.
             * @param min_omega Minimum frequency for each sinusoid.
             * @param max_omega Maximum frequency for each sinusoid.
             */
            Turbulence(int num_of_sins, float min_amplitude, float max_amplitude, float min_phi, float max_phi, float min_omega, float max_omega);
        
            /**
             * @brief Solves all sinusoids.
             *
             * Solves all sinusoids and returns the cumulative result.
             *
             * @param x The x value.
             *
             * @returns The cumulative Y value.
             */
            float solveSinusoids(float x);

        private:
        
            /**
             * @brief A sinusoid funfction.
             *
             * A sinusoid function defined as y = amplitude * sin((x + phase) * frequency)
             */
            struct Sinusoid {

                float amplitude;
                float phase;
                float frequency;

            };
        
            /**
             * @brief Solve a sinusoid and return the result.
             *
             * Solve a sinusoid and return the result.
             *
             * @param sinusoid The sinusoid.
             * @param x The x value.
             *
             * @returns The Y value.
             */
            static float solveSinusoid(Sinusoid sinusoid, float x);
        
            std::vector<Sinusoid> partial_sinusoids;    // All the sinusoid funtions.

    };

}  // namespace bgq_opengl

#endif  //! BGQ_OPENGL_CLASSES_TURBULENCE_H_
