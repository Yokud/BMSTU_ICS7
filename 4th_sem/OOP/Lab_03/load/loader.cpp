#include "loader.h"


    std::shared_ptr<Object> FileLoader::load(std::shared_ptr<BaseBuilder> builder)
    {
        builder->buildPtr();

        size_t points_count;
        this->file >> points_count;

        for (size_t i = 0; i < points_count; i++)
        {
            double x, y, z;
            this->file >> x >> y >> z;
            builder->buildPoint(x, y, z);
        }

        size_t links_count;
        this->file >> links_count;

        for (size_t i = 0; i < links_count; i++)
        {
            size_t pt1, pt2;
            this->file >> pt1 >> pt2;
            builder->buildEdge(pt1, pt2);
        }

        return builder->get();
    }

    void FileLoader::open(std::string &fname)
    {
        try
        {
            this->file.open(fname);
        } catch (std::ifstream::failure &error)
        {
            error.what();
        }
    }

    void FileLoader::close()
    {
        try
        {
            this->file.close();
        } catch (std::ifstream::failure &error)
        {
            error.what();
        }
    }

