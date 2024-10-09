#ifndef CONTAINERS_TGP_STATIC_ALLOCATION_H_
#define CONTAINERS_TGP_STATIC_ALLOCATION_H_

template <typename T, size_t Size>
class StaticAllocation {
public:
    StaticAllocation() = default;
    StaticAllocation           (const StaticAllocation& other) = default;
    StaticAllocation& operator=(const StaticAllocation& other) = default;
    ~StaticAllocation() = default;

    T* get_element(size_t index) noexcept {
        assert(index < Size);
        return &data_[index];
    }

    void construct_at(size_t index, const T& value) {
        assert(index < Size);
        new (get_element(index)) T(value);
    }

    void destroy_range(size_t start, size_t end) noexcept {
        for (size_t i = start; i < end; i++) {
            get_element(i)->~T();
        }
    }

    T*       data()       { return data_; }
    const T* data() const { return data_; }

    void reserve(size_t new_capacity) {
        throw MakeException<tgp::RuntimeError>("Cannot reserve more than static capacity.");
    }

    void shrink_to_fit() {
        throw MakeException<tgp::RuntimeError>("Cannot shrink to fit a static buffer.");
    }

    void push_back(const T& value) {
        if (size_ >= Size) {
            throw MakeException<tgp::RuntimeError>("Cannot push_back more than static capacity.");
        }
        new(data_ + size_) T(value);
        ++size_;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            data_[size_].~T();
        }
    }

    size_t size()     const { return size_; }
    size_t capacity() const { return Size; }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data()[i].~T();
        }
        size_ = 0;
    }

private:
    T data_[Size];
    size_t size_ = 0;
};

template <size_t Size>
class StaticAllocation<bool, Size> {
public:
    StaticAllocation() = default;

    bool get_element(size_t index) const noexcept {
        assert(index < Size);

        size_t byte_index = index / 8;
        size_t bit_index  = index % 8;
        return (data_[byte_index] >> bit_index) & 1;
    }

    void set_element(size_t index, bool value) {
        assert(index < Size);
        size_t byte_index = index / 8;
        size_t bit_index  = index % 8;
        if (value) {
            data_[byte_index] |= (1 << bit_index);
        }
        else {
            data_[byte_index] &= ~(1 << bit_index);
        }
    }

    void push_back(bool value) {
        if (size_ >= Size) {
            throw MakeException<tgp::RuntimeError>("Cannot push_back more than static capacity.");
        }
        set_element(size_, value);
        ++size_;
    }

    void pop_back() {
        assert(size_ > 0);
        if (size_ > 0) {
            --size_;
        }
    }

    size_t     size() const noexcept { return size_; }
    size_t capacity() const noexcept { return Size; }

    void clear() noexcept {
        size_ = 0;
    }

private:
    uint8_t data_[(Size + 7) / 8]{};
    size_t size_ = 0;
};

#endif // CONTAINERS_TGP_STATIC_ALLOCATION_H_
