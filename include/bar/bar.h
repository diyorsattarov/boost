// Bar.h

#ifndef BAR_H
#define BAR_H

#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <sstream>
#include <string>

class Bar {
public:
    // Members of Bar
    std::string data;

    // Serialization function
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & data;
    }
};

template<typename T>
std::string serialize(const T& obj) {
    std::ostringstream archive_stream;
    boost::archive::text_oarchive archive(archive_stream);
    archive << obj;
    return archive_stream.str();
}

template<typename T>
T deserialize(const std::string& s) {
    T obj;
    std::istringstream archive_stream(s);
    boost::archive::text_iarchive archive(archive_stream);
    archive >> obj;
    return obj;
}

#endif