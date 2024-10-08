template <typename T>
class VectorProxy;

template <typename T>
class Vector;

template <>
class VectorProxy<bool> {
public:
    VectorProxy(Vector<bool>& vec, size_t index);

    VectorProxy& operator=(bool value);
    operator bool() const;

private:
    Vector<bool>& vec_;
    size_t index_;
};

template <>
class Vector<bool> {
public:
    Vector();
    ~Vector();
    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    bool at(size_t index) const;
    VectorProxy<bool> operator[](size_t index);
    bool operator[](size_t index) const;

    void reserve(size_t capacity);
    void shrink_to_fit();

    void push_back(bool value);
    void pop_back() noexcept;

    bool back() const noexcept;
    bool front() const noexcept;

    const unsigned char* data() const noexcept;
    unsigned char* data() noexcept;

    bool empty() const noexcept;

    size_t size() const noexcept;
    size_t capacity() const noexcept;

    void clear() noexcept;

    friend class VectorProxy<bool>;

private:
    static constexpr float kGrowFactor = 2.f;
    static constexpr size_t kBitsPerByte = 8;

    void change_capacity(size_t new_capacity);
    void set_bit(size_t index, bool value);
    bool get_bit(size_t index) const;

    unsigned char* data_;
    size_t size_;
    size_t capacity_;
};

#include "tgp_vector_bool.tpp"
