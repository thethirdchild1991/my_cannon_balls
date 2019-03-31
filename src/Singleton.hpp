#ifndef SINGLETON
#define SINGLETON

template<typename T>
class Singleton {
public:
    static T& instance();

    Singleton(const Singleton&) = delete;
    Singleton& operator= (const Singleton) = delete;

protected:
    struct token {};
    Singleton() {}
};

template<typename T>
T& Singleton<T>::instance(){
    static T instance;
    return instance;
}

// template<typename T>
// class Singleton
// {
// public:
//     Singleton() = delete;

//     Singleton(const Singleton &) = delete;

//     Singleton &operator=(const Singleton &) = delete;

//     static T &instance()
//     {
//         static T instance;
//         return instance;
//     }
// };

#endif