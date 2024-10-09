#ifndef CONTAINERS_TGP_DYNAMIC_ALLOCATION_H_
#define CONTAINERS_TGP_DYNAMIC_ALLOCATION_H_

template <typename T>
class DynamicAllocation {
public:
    DynamicAllocation()
        : byte_data_(nullptr),
          size_(0),
          capacity_(0)
    {}

    DynamicAllocation(const DynamicAllocation& other)
        : byte_data_(nullptr),
          size_    (0),
          capacity_(0) {
        reserve(other.capacity());
        for (size_t i = 0; i < other.size(); i++) {
            new (get_element(i)) T(*other.get_element(i));
        }
        size_ = other.size_;
    }

    ~DynamicAllocation() {
        destroy_range(0, size_);
        ::operator delete(byte_data_);
    }

    DynamicAllocation& operator=(const DynamicAllocation& other) {
        if (this != &other) {
            destroy_range(0, size_);
            ::operator delete(byte_data_);
            new(this) DynamicAllocation(other);
        }
        return *this;
    }

    T* get_element(size_t index) const noexcept {
        assert(index < capacity_);
        return reinterpret_cast<T*>(byte_data_ + index * sizeof(T));
    }

    void construct_at(size_t index, const T& value) {
        assert(index < capacity_);
        new (get_element(index)) T(value);
    }

    void destroy_range(size_t start, size_t end) noexcept {
        for (size_t i = start; i < end; ++i) {
            get_element(i)->~T();
        }
    }

    T*       data()       { return reinterpret_cast<      T*>(byte_data_); }
    const T* data() const { return reinterpret_cast<const T*>(byte_data_); }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            change_capacity(new_capacity);
        }
    }

    void shrink_to_fit() {
        if (capacity_ > size_) {
            change_capacity(size_);
        }
    }

    void push_back(const T& value) {
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : static_cast<size_t>(capacity_ * kGrowFactor);
            try {
                DynamicAllocation tmp;
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
            catch (std::exception& e) {
                throw MakeException<tgp::RuntimeError>("Bad push_back.", &e); 
            }
            catch (...) {
                throw;
            }
        }

        construct_at(size_, value);
        size_++;
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
            data()[size_].~T();
        }
    }

    size_t size()     const { return size_; }
    size_t capacity() const { return capacity_; }

    void clear() {
        for (size_t i = 0; i < size_; ++i) {
            data()[i].~T();
        }
        size_ = 0;
    }

    void change_capacity(size_t new_capacity) {
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

private:
    constexpr static double kGrowFactor = 2.;

    std::byte* byte_data_;
    size_t size_;
    size_t capacity_;
};

template <>
class DynamicAllocation<bool> {
public:
    DynamicAllocation()
        : size_(0),
          capacity_(0),
          data_(nullptr)
    {}

    DynamicAllocation(const DynamicAllocation& other)
        : size_    (other.size_),
          capacity_(other.capacity_),
          data_(nullptr) {
        if (other.data_) {
            data_ = static_cast<uint8_t*>(::operator new(capacity_ / 8 + 1));
            std::memcpy(data_, other.data_, capacity_ / 8 + 1);
        }
    }

    ~DynamicAllocation() {
        ::operator delete(data_);
    }

    DynamicAllocation& operator=(const DynamicAllocation& other) {
        if (this != &other) {
            ::operator delete(data_);
            size_ = other.size_;
            capacity_ = other.capacity_;
            if (other.data_) {
                data_ = static_cast<uint8_t*>(::operator new(capacity_ / 8 + 1));
                std::memcpy(data_, other.data_, capacity_ / 8 + 1);
            } else {
                data_ = nullptr;
            }
        }
        return *this;
    }

    bool get_element(size_t index) const noexcept {
        assert(index < capacity_);
        printf("get_element: %zu\n", index);

        size_t byte_index = index / 8;
        size_t bit_index  = index % 8;

        return (data_[byte_index] >> bit_index) & 1;
    }

    void set_element(size_t index, bool value) {
        assert(index < capacity_);

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
        if (size_ == capacity_) {
            size_t new_capacity = capacity_ == 0 ? 1 : static_cast<size_t>(capacity_ * kGrowFactor);
            reserve(new_capacity);
        }
        set_element(size_, value);
        ++size_;
    }

    void reserve(size_t new_capacity) {
        if (new_capacity > capacity_) {
            size_t new_byte_capacity = new_capacity / 8 + 1;
            uint8_t* new_data = static_cast<uint8_t*>(::operator new(new_byte_capacity));
            std::memset(new_data, 0, new_byte_capacity);
            if (data_) {
                std::memcpy(new_data, data_, capacity_ / 8 + 1);
                ::operator delete(data_);
            }
            data_ = new_data;
            capacity_ = new_capacity;
        }
    }

    void pop_back() {
        if (size_ > 0) {
            --size_;
        }
    }

    void clear() noexcept {
        size_ = 0;
    }

    size_t size() const noexcept {
        return size_;
    }

    size_t capacity() const noexcept {
        return capacity_;
    }

private:
    constexpr static double kGrowFactor = 2.;

    size_t size_;
    size_t capacity_;
    uint8_t* data_;
};

#endif // CONTAINERS_TGP_DYNAMIC_ALLOCATION_H_
