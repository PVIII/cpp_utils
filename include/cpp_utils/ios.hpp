/** @brief iostream helpers.
 */

#ifndef IOS_H
#define IOS_H

#include <ios>
#include <sstream>
#include <streambuf>

template<class S> class ostream_capture
{
    S&                 stream_;
    std::streambuf*    old_buffer_;
    std::ostringstream redirect_;

  public:
    ostream_capture(S& stream) : stream_(stream), old_buffer_(stream.rdbuf())
    {
        stream_.rdbuf(redirect_.rdbuf());
    }
    ostream_capture(ostream_capture const&)  = delete;
    ostream_capture(ostream_capture&& other) = default;
    ~ostream_capture() { stream_.rdbuf(old_buffer_); }

    auto str() { return redirect_.str(); }
};

template<class S> auto make_ostream_capture(S& s)
{
    return ostream_capture<S>(s);
}

#endif /* IOS_H */
