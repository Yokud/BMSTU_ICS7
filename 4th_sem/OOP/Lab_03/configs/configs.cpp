#include "configs.h"


    void GraphLibConfig::readConfig()
    {
        try {
            std::ifstream fin(source);
            std::string graph_lib, load_source;
            fin >> graph_lib;
            fin >> load_source;

            this->frame = graph_lib;
            this->load_source = load_source;
        }  catch (std::ifstream::failure e) {
            std::string s = e.what();
            throw FileError(s);
        }

    }

    std::string GraphLibConfig::getFrame()
    {
        return frame;
    }

    std::string GraphLibConfig::getLoadSource()
    {
        return load_source;
    }

