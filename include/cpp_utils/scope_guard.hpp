/** @brief Different types of RAII wrappers.
 */

#ifndef SCOPE_GUARD_H
#define SCOPE_GUARD_H

#include <exception>

/**
 * Calls the given functor exactly once on any exit from the current scope,
 * including exceptions.
 */
template<class Func> class exit_guard
{
    Func f_;
    // This variable is only necessary because there is a move constructor.
    bool active_ = true;

  public:
    explicit exit_guard(Func f) : f_(f) {}
    exit_guard(const exit_guard&) = delete;
    /**
     * Deactivates the moved from guard. This constructor is necessary for the
     * make_exit_guard function. This can be removed in C++17.
     */
    exit_guard(exit_guard&& other) : f_(other.f_) { other.active_ = false; }
    ~exit_guard()
    {
        if(active_) { f_(); }
    }

    exit_guard<Func>& operator=(exit_guard&& other) = delete;
    exit_guard<Func>& operator=(const exit_guard&) = delete;
};

template<class Func> exit_guard<Func> make_exit_guard(Func&& f)
{
    return exit_guard<Func>(std::forward<Func>(f));
}

namespace detail
{
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
} // namespace detail

/**
 * Calls the given functor exactly once on any exit from the current scope, that
 * is not caused by an exception.
 */
template<class Func>
struct on_return_guard : exit_guard<detail::if_not_unwinding_wrapper<Func>>
{
    explicit on_return_guard(Func&& f)
        : exit_guard<detail::if_not_unwinding_wrapper<Func>>(
              detail::if_not_unwinding_wrapper<Func>(std::forward<Func>(f)))
    {
    }
};

#endif /* SCOPE_GUARD_H */
