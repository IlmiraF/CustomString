#pragma once

#include <ostream>

class String {
public:
    String();
    String(const char*);
    String(const String&);
    String(String&&) noexcept;
    String& operator=(const String& other);
    String& operator=(String&& other) noexcept;
    ~String();

    size_t length() const noexcept;
    const char* get_data() const noexcept;

    char& operator[](const size_t pos) const;
    String& operator+=(const String& other);
    String& operator+=(const char* cstr);
    bool operator<(const String& other) const;

    friend const String operator+(const String& lstr, const String& rstr);
    friend const String operator+(const String& lstr, const char* rstr);
    friend const String operator+(const char* lstr, const String& rstr);

    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator>>(std::istream& is, String& str);

    friend bool operator==(const String& lstr, const String& rstr);
    friend bool operator==(const String& lstr, const char* rstr);
    friend bool operator!=(const String& lstr, const String& rstr);

private:

    size_t size = 0;
    char* data = nullptr;

    void clear() noexcept;
};