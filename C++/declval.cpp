#include<typeinfo>
#include<iostream>

class HasMember {
public:
    HasMember()
    : m_member(0) {
    }
    int member() {
        return m_member;
    }
    void set_member(int value) {
        m_member = value;
    }
private:
    int m_member;
};

class DoesntHaveMember {
public:
    DoesntHaveMember()
    : m_member(0) {
    }
    void set_member(int value) {
        m_member = value;
    }
private:
    int m_member;
};

template<typename Klass>
void test_member() {
    if constexpr ( requires { std::declval<Klass>().member(); })
        std::cout << typeid(Klass).name() << " has member()" << std::endl;
    else
        std::cout << typeid(Klass).name() << " doesn't have member()" << std::endl;
}

int main(int argc, char** argv) {
    test_member<HasMember>();
    test_member<DoesntHaveMember>();
}
