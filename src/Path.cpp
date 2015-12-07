#include "Path.h"
#include <iostream>

std::string Path::resourcePath(const std::string& filename) {
    if (!m_mainbundle) { m_mainbundle = CFBundleGetMainBundle(); }
    CFURLRef resourceURL;

    resourceURL = CFBundleCopyResourceURL(m_mainbundle,
            CFStringCreateWithCString(NULL, filename.c_str(), kCFStringEncodingASCII),
            NULL, NULL);

    // Not in a bundle. Return location in ./resources/
    if (!resourceURL) {
        return "resources/" + filename;
    }

    char *fileUrl = new char[200];
    if (!CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*) fileUrl, 200)) {
        std::cout << "Failed to turn a bundle resource URL into filesystem path representation" << std::endl;
        return "resources/" + filename;
    }

    return std::string(fileUrl);
}

CFBundleRef Path::m_mainbundle;
