#ifndef CONTAINTERS_TGP_VECTOR_H_
#define CONTAINTERS_TGP_VECTOR_H_

#include "tgp_exceptions.h"

#include <cassert>
#include <cstddef>
#include <cstring>

namespace tgp {

template <typename T>
class VectorProxy;

template <typename T>
class Vector;

template <typename T>
class VectorProxy {
public:
    VectorProxy(Vector<T>& vec, size_t index);

    VectorProxy& operator=(const T& value);

    operator       T&();
    operator const T&() const;

private:
    Vector<T>& vec_;
    size_t index_;
};

template <typename T>
class Vector {
public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    T&       at(size_t index);
    const T& at(size_t index) const;
    VectorProxy<T> operator[](size_t index);
    const T&       operator[](size_t index) const;

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

    friend class VectorProxy<T>;

private:
    static constexpr float kGrowFactor = 2.f;

    void change_capacity(size_t new_capacity);
    T* get_element(size_t index) const noexcept;
    void construct_at(size_t index, const T& value);
    void destroy_range(size_t start, size_t end) noexcept;

    std::byte* byte_data_;
    size_t size_;
    size_t capacity_;
};

#include "tgp_vector.tpp"
#include "tgp_vector_bool.h"

} // namespace tgp

#endif  // CONTAINTERS_TGP_VECTOR_H_
