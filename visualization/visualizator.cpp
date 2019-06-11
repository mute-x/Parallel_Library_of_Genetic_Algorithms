#include "visualizator.h"


double fitness_function(const double &x, const double &y){
    return 1000 - (x * y);
}


unsigned int Visualizator::get_pixel_value(const double &value){
    double r = ((value - min_value) * 255 / (max_value - min_value));
    if ((r <= 0) || (r > 255)){
    }
    return (unsigned int) r;
}


unsigned int Visualizator::get_pixel_x_coordinate(const double &x){
    double r = ((x - x1) * width / (x2 - x1));
    if ((r < 0) || (r > width)){
    }
    return (unsigned int) r;
}


unsigned int Visualizator::get_pixel_y_coordinate(const double &y){
    double r = ((y - y1) * height / (y2 - y1));
    if ((r < 0) || (r > height)){
    }
    return (unsigned int) r;
}


void Visualizator::find_min_and_max_values(){
    max_value = fitness_function(x1, y1);
    min_value = max_value;
    double delta_x = (x2 - x1) / width;
    double delta_y = (y2 - y1) / height;
    double temp_x;
    double temp_y = y1;
    double cur_val;

    // Looking for whole_field max & min
    while(temp_y < y2){
        temp_x = x1;
        while(temp_x < x2){
            cur_val = fitness_function(temp_x, temp_y);
            if (cur_val > max_value){
                max_value = cur_val;
            } else if(cur_val < min_value){
                min_value = cur_val;
            }
            temp_x += delta_x;
        }
        temp_y += delta_y;
    }
}


cv::Mat Visualizator::create_background(){
    width = (unsigned int) ((x2 - x1) * height / (y2 - y1));

    cv::Mat background_field(height + header_height, width, CV_8UC3, cv::Scalar(255, 255, 255));
    unsigned int y_c;
    uchar r_g;
    double cur_val;

    double temp_x, temp_y;

    double delta_x = (x2 - x1) / width;
    double delta_y = (y2 - y1) / height;

    cv::Vec3b color;
    color[0] = 255;

    temp_y = y1;
    while(temp_y < y2){
        y_c = get_pixel_y_coordinate(temp_y) + header_height;
        temp_x = x1;
        while(temp_x < x2){
            cur_val = fitness_function(temp_x, temp_y);
            r_g = (uchar) (255 - get_pixel_value(cur_val));
            color[2] = r_g;
            color[1] = r_g;
            background_field.at<cv::Vec3b>(cv::Point(get_pixel_x_coordinate(temp_x), y_c)) = color;

            temp_x += delta_x;
        }
        temp_y += delta_y;
    }

    cv::putText(background_field,
                "Best current:",
                cv::Point(50, 80), // Coordinates
                cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                3.0, // Scale. 2.0 = 2x bigger
                cv::Scalar(0, 0, 0), // BGR Color
                5); // Line Thickness (Optional)

    cv::putText(background_field,
                "Best:",
                cv::Point(50, 150), // Coordinates
                cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                3.0, // Scale. 2.0 = 2x bigger
                cv::Scalar(0, 0, 0), // BGR Color
                5); // // Line Thickness (Optional)

    return background_field;
}

void Visualizator::draw_item(cv::Mat &field, const int &x, const int &y){
    unsigned int i_lower_bound, i_upper_bound, j_lower_bound, j_upper_bound;
    i_lower_bound = y - item_radius + 1 > header_height ? y - item_radius + 1 : header_height;
    i_upper_bound = y + item_radius < height + header_height ? y + item_radius : height + header_height;
    j_lower_bound = x - item_radius + 1 > 0 ? x - item_radius + 1 : 0;
    j_upper_bound = x + item_radius < width ? x + item_radius : width;

    cv::Vec3b color;
    color[0] = 0;
    color[1] = 0;
    color[2] = 255;

    for (unsigned int i = i_lower_bound; i < i_upper_bound; i++){
        for (unsigned int j = j_lower_bound; j < j_upper_bound; j++){
            if (abs((int)(y - i)) + abs((int)(x - j)) < item_radius){
                field.at<cv::Vec3b>(cv::Point(j, i)) = color;
            }
        }
    }
}


void Visualizator::set_height(unsigned int new_height){
    height = new_height;
    item_radius = (unsigned int) (0.01 * height);
}


int Visualizator::visualize(const std::string &filename, const std::string &visualized_filename){
    std::ifstream file(filename);
    try{
        if (file.is_open()){
            std::istream& cf = file;

            std::ios::fmtflags flags( cf.flags() ); // Save stream state
            cf.exceptions(std::ifstream::failbit); // Enable exception on fail

            std::string line;

            cf >> population_number;
            cf >> number_iterations;
            getline(cf, line);
            cf >> x1;
            cf >> x2;
            cf >> y1;
            cf >> y2;

            find_min_and_max_values();
            cv::Mat back = create_background();
            cv::Mat current_iteration;

            std::string item_coor;
            double x_item, y_item;
            int i, j;
            unsigned long coma_place;
            double best_current, best = min_value, current;

            unsigned long r = visualized_filename.find('.');
            if (r==visualized_filename.length()){
                std::cerr << "Visualized output should have exatension." << std::endl;
                return -3;
            }
            std::string vis_filename_begin = visualized_filename.substr(0, r);
            std::string vis_filename_end = visualized_filename.substr(r, visualized_filename.length() - r);

            std::string s;
            for (i = 0; i < number_iterations; i++){
                best_current = min_value;
                current_iteration = back.clone();
                getline(cf, line);
                for (j = 0; j < population_number; j++){
                    cf >> item_coor;
                    coma_place = item_coor.find(',');
                    x_item = std::stod(item_coor.substr(1, coma_place - 1));
                    y_item = std::stod(item_coor.substr(coma_place + 1, item_coor.length() - 2));
                    current = fitness_function(x_item, y_item);
                    if (current > best_current){
                        best_current = current;
                        if (current > best){
                            best = current;
                        }
                    }
                    draw_item(current_iteration, get_pixel_x_coordinate(x_item), get_pixel_y_coordinate(y_item) + header_height);
                }
                s = fmt::format("{:.2f}", best_current);
                cv::putText(current_iteration,
                            s,
                            cv::Point(600, 80), // Coordinates
                            cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                            3.0, // Scale. 2.0 = 2x bigger
                            cv::Scalar(0, 0, 0), // BGR Color
                            5); // Line Thickness (Optional)

                s = fmt::format("{:.2f}", best);
                cv::putText(current_iteration,
                            s,
                            cv::Point(600, 150), // Coordinates
                            cv::FONT_HERSHEY_COMPLEX_SMALL, // Font
                            3.0, // Scale. 2.0 = 2x bigger
                            cv::Scalar(0, 0, 0), // BGR Color
                            5); // // Line Thickness (Optional)
                cv::imwrite(vis_filename_begin + std::to_string(i) + vis_filename_end, current_iteration);
            }


        } else{
            std::cerr << "File " << filename << " couldn't be opened." << std::endl;
            return -1;
        }
    } catch(std::string &err){
        std::cerr << err << std::endl;
        return -2;
    }
    return 0;
}