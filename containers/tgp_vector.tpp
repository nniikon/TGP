static const char kBadChangeCapacity[] = "tgp::vector bad change_capacity()";
static const char kBadPushBack[]       = "tgp::vector bad push_back()";
static const char kBadAt[]             = "tgp::vector index out of range at()";
static const char kBadPopBack[]        = "tgp::vector index out of range pop_back()";
static const char kBadCopyCtor[]       = "tgp::vector bad copy constructor";
static const char kBadConstructor[]    = "tgp::vector bad alloc in constructor";

template <typename T>
VectorProxy<T>::VectorProxy(Vector<T>& vec, size_t index)
    : vec_(vec),
      index_(index)
{}

template <typename T>
VectorProxy<T>& VectorProxy<T>::operator=(const T& value) {
    if (index_ < vec_.size()) {
        vec_.construct_at(index_, value);
    }
    else {
        throw MakeException<tgp::BadRange>("Index out of range");
    }
    return *this;
}

template <typename T> VectorProxy<T>::operator       T&()       { return *vec_.get_element(index_); }
template <typename T> VectorProxy<T>::operator const T&() const { return *vec_.get_element(index_); }

template <typename T>
Vector<T>::Vector()
    : byte_data_(nullptr),
      size_(0),
      capacity_(0)
{}

template <typename T>
Vector<T>::~Vector() {
    clear();
    operator delete(byte_data_);
}

template <typename T>
Vector<T>::Vector(const Vector& other)
    : byte_data_(nullptr),
      size_(0),
      capacity_(0) {
    reserve(other.size_);
    for (size_t i = 0; i < other.size_; i++) {
        push_back(other[i]);
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        Vector tmp(other);
        std::swap(byte_data_, tmp.byte_data_);
        std::swap(size_,      tmp.size_);
        std::swap(capacity_,  tmp.capacity_);
        // tmp being destroyed with our data =)
    }
    return *this;
}

template <typename T>
T& Vector<T>::at(size_t index) {
    if (index >= size_) {
        throw MakeException<tgp::BadRange>(kBadAt);
    }

    return *get_element(index);
}

template <typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= size_) {
        throw MakeException<tgp::BadRange>(kBadAt);
    }

    return *get_element(index);
}

template <typename T>
VectorProxy<T> Vector<T>::operator[](size_t index) {
    return VectorProxy<T>(*this, index);
}

template <typename T>
const T& Vector<T>::operator[](size_t index) const {
    return *get_element(index);
}

template <typename T>
void Vector<T>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        change_capacity(new_capacity);
    }
}

template <typename T>
void Vector<T>::shrink_to_fit() {
    if (capacity_ > size_) {
        change_capacity(size_);
    }
}

template <typename T>
void Vector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        size_t new_capacity = capacity_ == 0 ? 1 : static_cast<size_t>(capacity_ * kGrowFactor);
        try {
            Vector tmp;
            tmp.reserve(new_capacity);
            for (size_t i = 0; i < size_; i++) {
                // :cool: :cool:
                // no recursion because of reserve()
                tmp.push_back(*get_element(i));
            }
            std::swap(byte_data_, tmp.byte_data_);
            std::swap(size_,      tmp.size_);
            std::swap(capacity_,  tmp.capacity_);
        }
        catch (Exception& e) {
            throw MakeException<tgp::RuntimeError>(kBadPushBack, &e); 
        }
        catch (...) {
            throw;
        }
    }

    construct_at(size_, value);
    size_++;
}

template <typename T>
void Vector<T>::pop_back() noexcept {
    if (size_ < 0) {
        assert(0);
        return;
    }

    size_--;
    get_element(size_)->~T();
}

template <typename T>
const T& Vector<T>::back() const noexcept {
    return *get_element(size_ - 1);
}

template <typename T>
T& Vector<T>::back() noexcept {
    return *get_element(size_ - 1);
}

template <typename T>
const T& Vector<T>::front() const noexcept {
    return *get_element(0);
}

template <typename T>
T& Vector<T>::front() noexcept {
    return *get_element(0);
}

template <typename T>
const T* Vector<T>::data() const noexcept {
    return reinterpret_cast<const T*>(byte_data_);
}

template <typename T>
T* Vector<T>::data() noexcept {
    return reinterpret_cast<T*>(byte_data_);
}

template <typename T>
bool Vector<T>::empty() const noexcept {
    return (size_ == 0);
}

template <typename T>
size_t Vector<T>::size() const noexcept {
    return size_;
}

template <typename T>
size_t Vector<T>::capacity() const noexcept {
    return capacity_;
}

template <typename T>
void Vector<T>::clear() noexcept {
    destroy_range(0, size_);
    size_ = 0;
}

template <typename T>
void Vector<T>::change_capacity(size_t new_capacity) {
    // having fun with the new operator
    std::byte* new_byte_data = static_cast<std::byte*>(::operator new(new_capacity * sizeof(T)));
    size_t new_size = std::min(size_, new_capacity);

    try {
        for (size_t i = 0; i < new_size; i++) {
            new (new_byte_data + i * sizeof(T)) T(*get_element(i));
            get_element(i)->~T();
        }
    }
    catch (...) {
        destroy_range(0, new_size);
        ::operator delete(new_byte_data);
        throw;
    }

    destroy_range(0, size_);
    ::operator delete(byte_data_);

    byte_data_ = new_byte_data;
    size_      = new_size;
    capacity_  = new_capacity;
}

template <typename T>
T* Vector<T>::get_element(size_t index) const noexcept {
    assert(index < capacity_);
    return reinterpret_cast<T*>(byte_data_ + index * sizeof(T));
}

template <typename T>
void Vector<T>::construct_at(size_t index, const T& value) {
    assert(index < capacity_);
    new (get_element(index)) T(value);
}

template <typename T>
void Vector<T>::destroy_range(size_t start, size_t end) noexcept {
    for (size_t i = start; i < end; ++i) {
        get_element(i)->~T();
    }
}
