#include "tgp_exceptions.h"

#include <iostream>

using namespace tgp;

Exception::Exception(const char* message, const std::exception* nested) noexcept 
    : message_(message) {

    if (nested == nullptr) {
        nested_ = nullptr;
        return;
    }

    try {
        std::exception_ptr nested_ptr = std::make_exception_ptr(*nested);
        nested_ = std::make_unique<std::exception_ptr>(nested_ptr);
    }
    catch (...) {
        std::cerr << "TGP Exception: Failed to copy nested exception" << std::endl;
        nested_ = nullptr;
    }
}

const char* Exception::what() const noexcept {
    return message_.c_str();
}

void Exception::unroll() const noexcept {
    try {
        std::cerr << what();
        const Exception* current = this;

        while (current->nested_) {
            try {
                std::rethrow_exception(*(current->nested_));
            }
            catch (const tgp::Exception& e) {
                std::cerr << " -> " << e.what();
                current = &e;
            }
            catch (const std::exception& e) {
                std::cerr << " -> " << e.what();
                return;
            }
        }
    }
    catch (...) {
        std::cerr << "TGP Exception: Exception during exception handling." << std::endl; 
    }
}

BadAlloc::BadAlloc        (const char* message, const std::exception* nested) : Exception(message, nested) {}
BadRange::BadRange        (const char* message, const std::exception* nested) : Exception(message, nested) {}
RuntimeError::RuntimeError(const char* message, const std::exception* nested) : Exception(message, nested) {}
