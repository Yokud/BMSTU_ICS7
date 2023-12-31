#ifndef ERROR_H
#define ERROR_H

#include <exception>
#include <string>


    class Error : public std::exception
    {
    public:
        Error() = default;
        Error(std::string &message): error_info(message) {};

        const char *what() const noexcept override
        {
            return "Something wrong...";
        }

        const std::string &getInfo() const noexcept
        {
            return error_info;
        }

    protected:
        std::string error_info;
    };

    class CameraError : public Error
    {
    public:
        CameraError() = default;
        CameraError(std::string &message): Error(message) {};

        const char *what() const noexcept override
        {
            return "Camera doesn't set.";
        }
    };

    class FileError: public Error
    {
    public:
        FileError() = default;
        FileError(std::string &message): Error(message) {};

        const char *what() const noexcept override
        {
            return "File corrupt or does not exist.";
        }
    };

    class ModelError : public Error
    {
    public:
        ModelError() = default;
        ModelError(std::string &message): Error(message) {};

        const char *what() const noexcept override
        {
            return "Error while building model.";
        }
    };

    class IdError : public Error
    {
    public:
        IdError() = default;
        IdError(std::string &message): Error(message) {};

        const char *what() const noexcept override
        {
            return "Error while finding id.";
        }
    };


#endif // ERROR_H
