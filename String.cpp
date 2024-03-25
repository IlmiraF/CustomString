#include "String.h"
#include <iostream>
#include <ostream>
#include <cstring>
using namespace std;

String::String() : size(0), data(nullptr) {}

String::String(const char* cstr)
{
	size = strlen(cstr);
	data = new char[size + 1];
	strncpy_s(data, size + 1, cstr, size);
}

String::String(const String& str)
{
	size = str.size;
	data = new char[size + 1];
	strncpy_s(data, size + 1, str.data, size);
}

String::String(String&& str) noexcept
{
	clear();

	size = str.size;
	data = str.data;
	str.size = 0;
	str.data = nullptr;
}

String& String::operator=(const String& str)
{
	clear();

	size = str.size;
	data = new char[size + 1];
	strncpy_s(data, size + 1, str.data, size);
	return *this;
}

String& String::operator=(String&& str) noexcept
{
	clear();

	size = str.size;
	data = str.data;
	str.size = 0;
	str.data = nullptr;

	return *this;
}

char& String::operator[](const size_t index) const
{
	return data[index];
}

String& String::operator+=(const String& str) 
{
	const size_t s_len = std::strlen(str.data);
	for (size_t i = 0; i < s_len; ++i) {
		data[size] = str.data[i];
		size++;
		data[size] = '\0';
	}
	return *this;
}

String& String::operator+=(const char* cstr)
{
	const size_t s_len = std::strlen(cstr);
	for (size_t i = 0; i < s_len; ++i) {
		data[size] = cstr[i];
		size++;
		data[size] = '\0';
	}

	return *this;
}

bool String::operator<(const String& str) const
{
	const size_t cmp_len = std::min(size, str.size);
	return (std::strncmp(data, str.data, cmp_len) < 0);
}

const String operator+(const String& lstr, const String& rstr)
{
	String str;
	str.size = lstr.length() + rstr.length();
	str.data = new char[str.size + 1];
	std::memcpy(str.data, lstr.get_data(), lstr.length());
	std::memcpy(str.data + lstr.length(), rstr.get_data(), rstr.length());
	str.data[str.size] = '\0';
	return str;
}

const String operator+(const String& lstr, const char* rstr)
{
	return (lstr + String(rstr));
}

const String operator+(const char* lstr, const String& rstr)
{
	return (String(lstr) + rstr);
}

istream& operator>>(istream& is, String& str)
{
	char* buff = new char[1000];
	memset(&buff[0], 0, sizeof(buff));
	is >> buff;
	str = String{buff};
	delete[] buff;
	return is;
}

ostream& operator<<(ostream& os, const String& str)
{
	os << str.get_data();
	return os;
}

bool operator==(const String& lstr, const String& rstr)
{
	const size_t llen = lstr.length();
	const size_t rlen = rstr.length();
	if ((llen == 0) && (rlen == 0)) {
		return true;
	}
	if ((lstr.data == nullptr) || (rstr.data == nullptr)) {
		return false;
	}
	return !std::strncmp(lstr.data, rstr.data, std::min(llen, rlen));
}

bool operator==(const String& lstr, const char* rstr)
{
	return (lstr == String(rstr));
}

bool operator!=(const String& lstr, const String& rstr)
{
	return !(lstr == rstr);
}

size_t String::length() const noexcept
{
	return size;
}

const char* String::get_data() const noexcept
{
	return data;
}

void String::clear() noexcept
{
	if (data != nullptr)
		delete[] data;

	size = 0;
}

String::~String()
{
	clear();
}