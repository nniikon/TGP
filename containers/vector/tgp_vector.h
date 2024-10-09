#ifndef CONTAINTERS_TGP_VECTOR_H_
#define CONTAINTERS_TGP_VECTOR_H_

#include "tgp_exceptions.h"

#include <cassert>
#include <cstddef>
#include <cstring>
#include <inttypes.h>

namespace tgp {

template <typename T, typename Strat, size_t N>
class VectorProxy;

template <typename T, typename Strat, size_t N>
class Vector;

#include "tgp_static_allocation.h"
#include "tgp_dynamic_allocation.h"

template <typename T, typename Strat, size_t N>
class VectorProxy {
public:
    VectorProxy(Vector<T, Strat, N>& vec, size_t index);
    VectorProxy& operator=(const T& value);
    operator       T&();
    operator const T&() const;

private:
    Vector<T, Strat, N>& vec_;
    size_t index_;
};

template <typename Strat, size_t N>
class VectorProxy<bool, Strat, N> {
public:
    VectorProxy(Vector<bool, Strat, N>& vec, size_t index);
    VectorProxy& operator=(bool value);
    operator bool();
    operator const bool() const;

private:
    Vector<bool, Strat, N>& vec_;
    size_t index_;
};

template <typename T, typename Strat, size_t N>
class Vector {
public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    T&       at(size_t index);
    const T& at(size_t index) const;
    VectorProxy<T, Strat, N> operator[](size_t index);
    const T&                 operator[](size_t index) const;

    void reserve(size_t capacity);
    void shrink_to_fit();

    void push_back(const T& value);
    void pop_back() noexcept;

    const T& back() const noexcept;
    T&       back()       noexcept;

    const T& front() const noexcept;
    T&       front()       noexcept;

    const T* data() const noexcept;
    T*       data()       noexcept;

    bool empty() const noexcept;

    size_t     size() const noexcept;
    size_t capacity() const noexcept;

    void clear() noexcept;

    friend class VectorProxy<T, Strat, N>;

private:
    static constexpr float kGrowFactor = 2.f;

    Strat strat_;
};

} // namespace tgp

#include "tgp_vector.tpp"

#endif  // CONTAINTERS_TGP_VECTOR_H_
