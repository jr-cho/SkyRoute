#ifndef AIRPORT_UTILS_H
#define AIRPORT_UTILS_H

inline bool isSameAirport(const char* a, const char* b) {
    return (a[0] == b[0] && a[1] == b[1] && a[2] == b[2] && a[3] == b[3]);
}

inline void copyCode(char* dest, const char* src) {
    for (int i = 0; i < 3; i++) dest[i] = src[i];
    dest[3] = '\0';
}

#endif // AIRPORT_UTILS_H

