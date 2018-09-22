/** @brief Different types of RAII wrappers.
 */

#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <exception>

template<class Func> class exit_guard
{
    Func f_;
    bool active_ = true;

  public:
    explicit exit_guard(Func&& f) : f_(std::forward<Func>(f)) {}
    exit_guard(const exit_guard&) = delete;
    exit_guard(exit_guard&& other) : f_(other.f_) { other.active_ = false; }
    ~exit_guard() noexcept(noexcept(f_()))
    {
        if(active_) { f_(); }
    }
    exit_guard<Func>& operator=(const exit_guard&) = delete;
    exit_guard<Func>& operator                     =(exit_guard&& other)
    {
        f_            = other.f_;
        active_       = other.active_;
        other.active_ = false;
    }
};

template<class Func> exit_guard<Func> make_exit_guard(Func&& f)
{
    return exit_guard<Func>(std::forward<Func>(f));
}

template<class Func> struct if_not_unwinding_wrapper
{
    int  exception_count_ = std::uncaught_exceptions();
    Func f_;

  public:
    constexpr explicit if_not_unwinding_wrapper(Func&& f) : f_(f) {}
    constexpr void operator()()
    {
        if(exception_count_ == std::uncaught_exceptions()) { f_(); }
    }
};

template<class Func>
struct on_return_guard : exit_guard<if_not_unwinding_wrapper<Func>>
{
    explicit on_return_guard(Func&& f)
        : exit_guard<if_not_unwinding_wrapper<Func>>(
              if_not_unwinding_wrapper<Func>(std::forward<Func>(f)))
    {
    }
};

#endif /* SCOPE_GUARD_H */
