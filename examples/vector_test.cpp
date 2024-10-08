#include <iostream>
#include <ostream>
#include "vector"

#include "../containers/tgp_vector.h"

int TestType();
int TestBool();

int main() {
    return TestBool();

    std::string s1[] = {"str1", "str2", "str3", "str4", "str5", "str6", "str7", "str8", "str9", "str10", "str11", "str12", "str13", "str14", "str15", "str16"};
    tgp::Vector<std::string> vec;

    for (int i = 0; i < 16; i++) {
        vec.push_back(s1[i]);
        std::cout << "Index: "    << i            << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;
        std::cout << "Size: "     << vec.size()     << std::endl;
        std::cout << "Value: "    << static_cast<std::string>(vec[i]) << std::endl;
        vec[i] = "123";
        std::cout << std::endl;
    }

    vec.pop_back();
    std::cout << "After pop_back()" << std::endl;
    std::cout << "Size: "     << vec.size()     << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    vec.clear();
    std::cout << "After clear()" << std::endl;
    std::cout << "Size: "     << vec.size()     << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;

    vec.push_back("a");
    std::cout << "After push_back(\"a\")" << std::endl;
    std::cout << "Size: "     << vec.size()     << std::endl;
    std::cout << "Capacity: " << vec.capacity() << std::endl;
}

int TestBool() {
    bool t = true;
    bool f = false;

    tgp::Vector<bool> vec;

    for (int i = 0; i < 16; i++) {
        vec.push_back(i % 2 == 0 ? t : f);
        std::cout << "Index: "    << i            << std::endl;
        std::cout << "Capacity: " << vec.capacity() << std::endl;
        std::cout << "Size: "     << vec.size()     << std::endl;
        std::cout << "Value: "    << vec[i] << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "Value: "    << vec[i] << std::endl;
        vec[i] = 0;
    }

    std::cout << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "Value: "    << vec[i] << std::endl;
        vec[i] = 1;
    }

    std::cout << std::endl;
    for (int i = 0; i < 16; i++) {
        std::cout << "Value: "    << vec[i] << std::endl;
    }

    return 0;
}

#include <cmath>
#include <cstring>
#include <iostream>
#include <ostream>
#include <vector>

class Type {
public:
    Type() {
        std::cout << "Type Ctor" << std::endl;
    }

    Type(const Type& other) {
        std::cout << "Type copy Ctor" << std::endl;
    }
    
    ~Type() {
        std::cout << "Type Dtor" << std::endl;
    }

    Type& operator=(const Type& other) {
        std::cout << "Type operator=" << std::endl;
        return *this;
    }

    Type(const Type&& other) {
        std::cout << "Type move Ctor" << std::endl;
    }

    Type& operator=(Type&& other){
        std::cout << "Type move operator=" << std::endl;
        return *this;
    }
};

int TestType() {
    std::cout << "Creating vector of type" << std::endl << std::endl;
    std::vector<Type> v;
    v.reserve(4);

    std::cout << "Creating two types" << std::endl << std::endl;
    Type t1, t2;

    std::cout << "Pushing two types to vector" << std::endl << std::endl;
    v.push_back(t1);
    v.push_back(t2);

    std::cout << "Popping two types from vector" << std::endl << std::endl;
    v.pop_back();

    std::cout << "Destroying vector" << std::endl << std::endl;
    return 0;
}
