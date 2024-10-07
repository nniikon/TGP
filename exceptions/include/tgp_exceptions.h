#ifndef CONTAINTERS_TGP_EXCEPTIONS_H_
#define CONTAINTERS_TGP_EXCEPTIONS_H_

#include <exception>
#include <memory>
#include <string>

namespace tgp {

class Exception : public std::exception {
public:
    explicit Exception(const char* message, const std::exception* nested = nullptr) noexcept;

    virtual const char* what() const noexcept override;

    void unroll() const noexcept;

private:
    std::string message_;
    std::unique_ptr<std::exception_ptr> nested_;
};

template <typename T>
T MakeException(const char* message, const std::exception* nested = nullptr) {
    return T(message, nested);
}

class BadAlloc : public Exception {
public:
    explicit BadAlloc(const char* message, const std::exception* nested = nullptr);
};

class BadRange : public Exception {
public:
    explicit BadRange(const char* message, const std::exception* nested = nullptr);
};

class RuntimeError : public Exception {
public:
    explicit RuntimeError(const char* message, const std::exception* nested = nullptr);
};

} // namespace tgp

#endif  // CONTAINTERS_TGP_EXCEPTIONS_H_
