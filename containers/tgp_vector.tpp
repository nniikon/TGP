#ifndef CONTAINTERS_TGP_VECTOR_TPP_
#define CONTAINTERS_TGP_VECTOR_TPP_

namespace tgp {

template <typename T, typename Strat, size_t N>
VectorProxy<T, Strat, N>::VectorProxy(Vector<T, Strat, N>& vec, size_t index)
    : vec_(vec), index_(index) {}

template <typename T, typename Strat, size_t N>
VectorProxy<T, Strat, N>& VectorProxy<T, Strat, N>::operator=(const T& value) {
    if (index_ < vec_.size()) {
        *vec_.strat_.get_element(index_) = value;
    }
    else {
        throw MakeException<tgp::BadRange>("Index out of range");
    }
    return *this;
}

template <typename T, typename Strat, size_t N>
VectorProxy<T, Strat, N>::operator T&() { return *vec_.strat_.get_element(index_); }

template <typename T, typename Strat, size_t N>
VectorProxy<T, Strat, N>::operator const T&() const { return *vec_.strat_.get_element(index_); }

template <typename Strat, size_t N>
VectorProxy<bool, Strat, N>::VectorProxy(Vector<bool, Strat, N>& vec, size_t index)
    : vec_(vec), index_(index) {}

template <typename Strat, size_t N>
VectorProxy<bool, Strat, N>& VectorProxy<bool, Strat, N>::operator=(bool value) {
    vec_.strat_.set_element(index_, value);
    return *this;
}

template <typename Strat, size_t N>
VectorProxy<bool, Strat, N>::operator bool() {
    return vec_.strat_.get_element(index_);
}

template <typename Strat, size_t N>
VectorProxy<bool, Strat, N>::operator const bool() const {
    return vec_.strat_.get_element(index_);
}

template <typename T, typename Strat, size_t N>
Vector<T, Strat, N>::Vector()
    : strat_() {}

template <typename T, typename Strat, size_t N>
Vector<T, Strat, N>::~Vector() {}

template <typename T, typename Strat, size_t N>
Vector<T, Strat, N>::Vector(const Vector& other)
    : strat_(other.strat_) {}

template <typename T, typename Strat, size_t N>
Vector<T, Strat, N>& Vector<T, Strat, N>::operator=(const Vector& other) {
    strat_.operator=(other.strat_);
    return *this;
}

template <typename T, typename Strat, size_t N>
T& Vector<T, Strat, N>::at(size_t index) {
    if (index >= strat_.size()) {
        throw MakeException<tgp::BadRange>("Index out of range");
    }
    return *strat_.get_element(index);
}

template <typename T, typename Strat, size_t N>
const T& Vector<T, Strat, N>::at(size_t index) const {
    if (index >= strat_.size()) {
        throw MakeException<tgp::BadRange>("Index out of range");
    }
    return *strat_.get_element(index);
}

template <typename T, typename Strat, size_t N>
VectorProxy<T, Strat, N> Vector<T, Strat, N>::operator[](size_t index) {
    return VectorProxy<T, Strat, N>(*this, index);
}

template <typename T, typename Strat, size_t N>
const T& Vector<T, Strat, N>::operator[](size_t index) const {
    return *strat_.get_element(index);
}

template <typename T, typename Strat, size_t N>
void Vector<T, Strat, N>::reserve(size_t new_capacity) {
    strat_.reserve(new_capacity);
}

template <typename T, typename Strat, size_t N>
void Vector<T, Strat, N>::shrink_to_fit() {
    strat_.shrink_to_fit();
}

template <typename T, typename Strat, size_t N>
void Vector<T, Strat, N>::push_back(const T& value) {
    strat_.push_back(value);
}

template <typename T, typename Strat, size_t N>
void Vector<T, Strat, N>::pop_back() noexcept {
    strat_.pop_back();
}

template <typename T, typename Strat, size_t N>
const T& Vector<T, Strat, N>::back() const noexcept {
    return *strat_.get_element(strat_.size_ - 1);
}

template <typename T, typename Strat, size_t N>
T& Vector<T, Strat, N>::back() noexcept {
    return *strat_.get_element(strat_.size_ - 1);
}

template <typename T, typename Strat, size_t N>
const T& Vector<T, Strat, N>::front() const noexcept {
    return *strat_.get_element(0);
}

template <typename T, typename Strat, size_t N>
T& Vector<T, Strat, N>::front() noexcept {
    return *strat_.get_element(0);
}

template <typename T, typename Strat, size_t N>
const T* Vector<T, Strat, N>::data() const noexcept {
    return strat_.data();
}

template <typename T, typename Strat, size_t N>
T* Vector<T, Strat, N>::data() noexcept {
    return strat_.data();
}

template <typename T, typename Strat, size_t N>
bool Vector<T, Strat, N>::empty() const noexcept {
    return (strat_.size() == 0);
}

template <typename T, typename Strat, size_t N>
size_t Vector<T, Strat, N>::size() const noexcept {
    return strat_.size();
}

template <typename T, typename Strat, size_t N>
size_t Vector<T, Strat, N>::capacity() const noexcept {
    return strat_.capacity();
}

template <typename T, typename Strat, size_t N>
void Vector<T, Strat, N>::clear() noexcept {
    strat_.clear();
}

} // namespace tgp

#endif  // CONTAINTERS_TGP_VECTOR_TPP_
