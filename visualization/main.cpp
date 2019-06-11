#include "visualizator.h"


int main(int argc, char* argv[]){
    std::string in_filename, out_filename;
    if (argc > 2){
        in_filename = argv[1];
        out_filename = argv[2];
    } else{
        std::cerr << "Too few arguments. Should be: <in-filename> <out_filename>." << std::endl;
        return -1;
    }

    Visualizator v;
    v.visualize(in_filename, out_filename);
    return 0;
}