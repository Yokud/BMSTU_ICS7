#ifndef ABSCONFIG_H
#define ABSCONFIG_H

#include <iostream>
#include <memory>
#include <string>
#include <fstream>

#include "errors/errors.h"


    class AbsConfig
    {
    public:
        AbsConfig(std::string source = nullptr) : source(std::move(source)) {};

        virtual void readConfig() = 0;
        virtual std::string getFrame() = 0;
        virtual std::string getLoadSource() = 0;

    protected:
        std::string source;
    };

    class GraphLibConfig : public AbsConfig
    {
    public:
        GraphLibConfig(std::string source = nullptr): AbsConfig(source) {};

        virtual void readConfig() override;
        virtual std::string getFrame() override;
        virtual std::string getLoadSource() override;

    private:
        std::string frame;
        std::string load_source;
    };



#endif // ABSCONFIG_H
