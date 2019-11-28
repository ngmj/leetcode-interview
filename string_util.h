#ifndef _STRING_UTIL_H_
#define _STRING_UTIL_H_
#include <algorithm>
#include <string>
#include <sstream>
#include <ctype.h>
#include <deque>

// map, unordered_map
template<class M>
inline std::string MapToString(const M &value_map) {
    std::ostringstream str;
    auto iter = value_map.begin();
    for ( ; iter != value_map.end(); iter++ ) {
        if (iter != value_map.begin() && iter != value_map.end()) {
            str << ", ";
        }
        str << (iter->first) << "-" << (iter->second);
    }
    return str.str();
}

// map, unordered_map
template<class M>
inline std::string SelfMapToString(const M &value_map) {
    std::ostringstream str;
    auto iter = value_map.begin();
    for (; iter != value_map.end(); iter++) {
        if (iter != value_map.begin() && iter != value_map.end()) {
            str << ", ";
        }
        str << iter->first << " - " << iter->second.ToString();
    }
    return str.str();
}


// vector, list, set, unordered_set
template<class V>
inline std::string VectorToString(const V &value_vec) {
    std::ostringstream str;
    auto iter = value_vec.begin();
    for (; iter != value_vec.end(); iter++) {
        if (iter != value_vec.begin() && iter != value_vec.end()) {
            str << ", ";
        }
        str << *iter;
    }
    return str.str();
}

// vector, list, set, unordered_set
template<class V>
inline std::string SelfVectorToString(const V &value_vec) {
    std::ostringstream str;
    auto iter = value_vec.begin();
    for (; iter != value_vec.end(); iter++) {
        if (iter != value_vec.begin() && iter != value_vec.end()) {
            str << ", ";
        }
        str << iter->ToString();
    }
    return str.str();
}

template<class S>
inline std::string SetToString( const S &value_set )
{
    return VectorToString<S>( value_set );
}

template<class S>
inline std::string SelfSetToString( const S &value_set )
{
    return SelfVectorToString<S>( value_set );
}

#endif // _STRING_UTIL_H_
