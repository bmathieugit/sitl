#ifndef __lib_file_hpp__
#define __lib_file_hpp__

#include "exception.hpp"
#include "meta.hpp"
#include <cstdio>
#include "span.hpp"
#include "string_view.hpp"

namespace lib
{
  BASIC_EXCEPTION(ios_exception)
  INHERITED_EXCEPTION(file_opening_failed, ios_exception)
  INHERITED_EXCEPTION(null_file_descriptor, ios_exception)
  INHERITED_EXCEPTION(opened_file_flushing_failed, ios_exception)
  INHERITED_EXCEPTION(opened_file_closing_failed, ios_exception)
  INHERITED_EXCEPTION(opened_file_writing_failed, ios_exception)

  struct file
  {
    std::FILE *fd = nullptr;

    file(std::FILE *f) noexcept : fd(f) {}

    inline bool opened() const
    {
      return fd == nullptr;
    }

    inline bool has_error() const
    {
      return fd == nullptr or
             std::ferror(fd) != 0;
    }

    inline bool eof() const
    {
      return fd == nullptr or
             std::feof(fd) != 0;
    }

    template <character char_t>
    void push_back(const char_t &c)
    {
      std::fputc(c, fd);
    }

    template <typename type_t, typename limit_t>
    inline void write(span<type_t, limit_t> s)
    {
      std::fwrite(s.data(), sizeof(type_t), s.size(), fd);
    }

    long size() const
    {
      std::fseek(fd, 0L, SEEK_END);
      long sz = std::ftell(fd);
      std::fseek(fd, 0L, SEEK_SET);
      return sz;
    }

    // template<typename type_t>
    // inline void read(basic_string<type_t>& out, lib::size_t nbbytes)
    // {
    //   std::fread(out.data(), nbbytes, fd);
    // }
  };

  inline file fopen(string_view filename, string_view mode)
  {
    file f(std::fopen(filename.data(), mode.data()));
    return f;
  }

  inline void fclose(file &f)
  {
    std::fclose(f.fd);
    f.fd = nullptr;
  }

  inline void fflush(file &f)
  {
    std::fflush(f.fd);
  }

  inline file cout(stdout);
  inline file cin(stdin);
  inline file cerr(stderr);
}

#endif
