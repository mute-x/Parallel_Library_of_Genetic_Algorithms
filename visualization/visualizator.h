#ifndef PARALLEL_LIBRARY_OF_GENETIC_ALGORITHMS_VISUALIZATOR_H
#define PARALLEL_LIBRARY_OF_GENETIC_ALGORITHMS_VISUALIZATOR_H

#include <iostream>
#include <string>
#include <fstream>
#include <fmt/core.h>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>



double fitness_function(const double &x, const double & y);

class Visualizator{
    private:
        unsigned int height = 1000,
                width = 0,
                population_number = 0,
                number_iterations = 0,
                header_height = 200,
                item_radius = 10;
        double x1, x2, y1, y2, min_value, max_value;

        unsigned int get_pixel_value(const double &value);
        unsigned int get_pixel_x_coordinate(const double &x);
        unsigned int get_pixel_y_coordinate(const double &y);
        void find_min_and_max_values();
        cv::Mat create_background();
        void draw_item(cv::Mat &field, const int &x, const int &y);

    public:
        void set_height(unsigned int new_height);
        int visualize(const std::string &filename, const std::string &visualized_filename);

};

#endif //PARALLEL_LIBRARY_OF_GENETIC_ALGORITHMS_VISUALIZATOR_H
