#ifndef __PATH_H__
#define __PATH_H__

#include <CoreFoundation/CFBundle.h>
#include <stdexcept>

struct FileError : std::exception {
    char text[1000];
    FileError(char const* fmt, ...) __attribute__((format(printf,2,3))) {
        va_list ap;
        va_start(ap, fmt);
        vsnprintf(text, sizeof text, fmt, ap);
        va_end(ap);
    }
    char const* what() const throw() { return text; }
};

class Path
{
public:
    static std::string resourcePath(const std::string& filename);
private:
    static CFBundleRef m_mainbundle;
};

#endif
