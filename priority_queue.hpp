#ifndef MY_PRIORITY_QUEUE_HPP
#define MY_PRIORITY_QUEUE_HPP

#include <vector>
#include <algorithm>
#include <functional>

template<
    class T,
    class Container = std::vector<T>,
    class Compare = std::less<typename Container::value_type>
>

class priority_queue {
public:
    using container_type = Container;
    using value_compare = Compare;
    using value_type = typename Container::value_type;
    using size_type = typename Container::size_type;
    using reference = typename Container::reference;
    using const_reference = typename Container::const_reference;

protected:
    Container c;
    Compare comp;

public:
    priority_queue(const Compare& compare = Compare(), const Container& cont = Container())
        : c(cont), comp(compare) {
        std::make_heap(c.begin(), c.end(), comp);
    }

    priority_queue(const priority_queue& other) : c(other.c), comp(other.comp) {
        std::make_heap(c.begin(), c.end(), comp);
    }

    priority_queue(priority_queue&& other) noexcept : c(std::move(other.c)), comp(std::move(other.comp)) {
        std::make_heap(c.begin(), c.end(), comp);
    }

    ~priority_queue() = default;

    priority_queue& operator=(const priority_queue& other) {
        if (this != &other) {
            c = other.c;
            comp = other.comp;
            std::make_heap(c.begin(), c.end(), comp);
        }
        return *this;
    }

    priority_queue& operator=(priority_queue&& other) noexcept {
        if (this != &other) {
            c = std::move(other.c);
            comp = std::move(other.comp);
            std::make_heap(c.begin(), c.end(), comp);
        }
        return *this;
    }

    const_reference top() const {
        return c.front();
    }

    bool empty() const {
        return c.empty();
    }

    size_type size() const {
        return c.size();
    }

    void push(const value_type& value) {
        c.push_back(value);
        std::push_heap(c.begin(), c.end(), comp);
    }

    void push(value_type&& value) {
        c.push_back(std::move(value));
        std::push_heap(c.begin(), c.end(), comp);
    }

    template <class... Args>
    void emplace(Args&&... args) {
        c.emplace_back(std::forward<Args>(args)...);
        std::push_heap(c.begin(), c.end(), comp);
    }

    void pop() {
        std::pop_heap(c.begin(), c.end(), comp);
        c.pop_back();
    }

    void swap(priority_queue& other) noexcept {
        std::swap(c, other.c);
        std::swap(comp, other.comp);
    }

    friend void swap(priority_queue& lhs, priority_queue& rhs) noexcept {
        lhs.swap(rhs);
    }
};

#endif 
