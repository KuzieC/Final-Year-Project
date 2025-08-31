/**
 * @file map.h
 * @brief Map loading and management class
 * 
 * Provides functionality to read map configuration files
 * and create Map structures for the CBS algorithm.
 */

#pragma once
#include "util.h"

/**
 * @class map
 * @brief Map file reader and processor
 * 
 * This class handles loading map configurations from files,
 * including grid dimensions, obstacles, and agent configurations.
 */
class map{
    private:   
       
    public:
        Map m;      ///< The loaded map structure
        map();      ///< Default constructor
        ~map();     ///< Destructor
        
        /// Reads map configuration from specified file
        void readMap(std::string filename);
};