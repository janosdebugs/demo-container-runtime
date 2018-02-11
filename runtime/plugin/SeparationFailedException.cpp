#include "SeparationFailedException.h"

#include <utility>

const char *SeparationFailedException::what() const _GLIBCXX_USE_NOEXCEPT {
    return reason.c_str();
}

SeparationFailedException::SeparationFailedException(std::string reason) {
    this->reason = std::move(reason);
}
