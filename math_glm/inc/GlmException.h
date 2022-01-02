//
// Created by volodya on 29.08.2021.
//

#ifndef PROJECT_GLMEXCEPTION_H
#define PROJECT_GLMEXCEPTION_H

#include <exception>
#include <string>
#include <utility>

class GlmException: public std::exception {
private:
    std::string _desc;
public:
    explicit GlmException(std::string desc) : _desc(std::move(desc)) {}

    [[nodiscard]] const char *what() const noexcept override {
        return _desc.c_str();
    }
};


#endif //PROJECT_GLMEXCEPTION_H
