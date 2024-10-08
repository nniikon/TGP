inline VectorProxy<bool>::VectorProxy(Vector<bool>& vec, size_t index)
    : vec_(vec),
      index_(index)
{}

inline VectorProxy<bool>& VectorProxy<bool>::operator=(bool value) {
    vec_.set_bit(index_, value);
    return *this;
}

inline VectorProxy<bool>::operator bool() const {
    return vec_.get_bit(index_);
}

inline Vector<bool>::Vector()
    : data_(nullptr),
      size_(0), 
      capacity_(0)
{}

inline Vector<bool>::~Vector() {
    delete[] data_;
}

inline Vector<bool>::Vector(const Vector& other)
    : data_(nullptr),
      size_(0),
      capacity_(0) {

    reserve(other.capacity_);
    size_ = other.size_;
    std::memcpy(data_, other.data_, (size_ + kBitsPerByte - 1) / kBitsPerByte);
}

inline Vector<bool>& Vector<bool>::operator=(const Vector& other) {
    if (this != &other) {
        Vector tmp(other);
        std::swap(data_, tmp.data_);
        std::swap(size_, tmp.size_);
        std::swap(capacity_, tmp.capacity_);
    }
    return *this;
}

inline bool Vector<bool>::at(size_t index) const {
    if (index >= size_) {
        throw MakeException<tgp::BadRange>(kBadAt);
    }
    return get_bit(index);
}

inline VectorProxy<bool> Vector<bool>::operator[](size_t index) {
    return VectorProxy<bool>(*this, index);
}

inline bool Vector<bool>::operator[](size_t index) const {
    return get_bit(index);
}

inline void Vector<bool>::reserve(size_t new_capacity) {
    if (new_capacity > capacity_) {
        change_capacity(new_capacity);
    }
}

inline void Vector<bool>::shrink_to_fit() {
    if (capacity_ > size_) {
        change_capacity(size_);
    }
}

inline void Vector<bool>::push_back(bool value) {
    if (size_ == capacity_) {
        size_t new_capacity = capacity_ == 0 ? 1 : static_cast<size_t>(capacity_ * kGrowFactor);
        change_capacity(new_capacity);
    }
    set_bit(size_, value);
    ++size_;
}

inline void Vector<bool>::pop_back() noexcept {
    assert(size_ > 0);
    if (size_ > 0) {
        --size_;
    }
}

inline bool Vector<bool>::back() const noexcept {
    assert(size_ > 0);
    return size_ > 0 ? get_bit(size_ - 1) : false;
}

inline bool Vector<bool>::front() const noexcept {
    assert(size_ > 0);
    return size_ > 0 ? get_bit(0) : false;
}

inline const unsigned char* Vector<bool>::data() const noexcept {
    return data_;
}

inline unsigned char* Vector<bool>::data() noexcept {
    return data_;
}

inline bool Vector<bool>::empty() const noexcept {
    return (size_ == 0);
}

inline size_t Vector<bool>::size() const noexcept {
    return size_;
}

inline size_t Vector<bool>::capacity() const noexcept {
    return capacity_;
}

inline void Vector<bool>::clear() noexcept {
    size_ = 0;
}

inline void Vector<bool>::change_capacity(size_t new_capacity) {
    size_t new_byte_count = (new_capacity + kBitsPerByte - 1) / kBitsPerByte;
    size_t new_size       = std::min(size_, new_capacity);
    unsigned char* new_data = new unsigned char[new_byte_count]();

    if (data_) {
        size_t copy_byte_count = (new_size + kBitsPerByte - 1) / kBitsPerByte;
        std::memcpy(new_data, data_, copy_byte_count);
        delete[] data_;
    }

    data_ = new_data;
    capacity_ = new_capacity;
    size_ = std::min(size_, new_capacity);
}

inline void Vector<bool>::set_bit(size_t index, bool value) {
    size_t byte_index = index / kBitsPerByte;
    size_t bit_index  = index % kBitsPerByte;
    
    if (value) {
        data_[byte_index] |= (1 << bit_index);
    }
    else {
        data_[byte_index] &= ~(1 << bit_index);
    }
}

inline bool Vector<bool>::get_bit(size_t index) const {
    size_t byte_index = index / kBitsPerByte;
    size_t bit_index  = index % kBitsPerByte;
    
    return (data_[byte_index] & (1 << bit_index)) != 0;
}
