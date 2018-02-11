#ifndef DEMO_CONTAINER_RUNTIME_SEPARATIONFAILEDEXCEPTION_H
#define DEMO_CONTAINER_RUNTIME_SEPARATIONFAILEDEXCEPTION_H

#include <exception>
#include <string>

class SeparationFailedException: public std::exception {
private:
    std::string reason;
public:
    explicit SeparationFailedException(std::string reason);
    const char *what() const _GLIBCXX_USE_NOEXCEPT; // NOLINT
};


#endif //DEMO_CONTAINER_RUNTIME_SEPARATIONFAILEDEXCEPTION_H
