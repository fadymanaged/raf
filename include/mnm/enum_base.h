#pragma once

namespace enum_base_details {

template <class T, class underlying, int n>
struct collect {
  static std::vector<const char*> c_str() {
    using integral_constant_t = typename T::template _integral_constant<n - 1>;
    std::vector<const char*> result = collect<T, underlying, n - 1>::c_str();
    result.push_back(T::_c_str(integral_constant_t()));
    return result;
  }
  template <class plain_t>
  static std::vector<plain_t> plain() {
    using integral_constant_t = typename T::template _integral_constant<n - 1>;
    std::vector<plain_t> result = collect<T, underlying, n - 1>::template plain<plain_t>();
    result.push_back(T::_plain(integral_constant_t()));
    return result;
  }
};

template <class T, class underlying>
struct collect<T, underlying, 0> {
  static std::vector<const char*> c_str() {
    return std::vector<const char*>();
  }
  template <class plain_t>
  static std::vector<plain_t> plain() {
    return std::vector<plain_t>();
  }
};

template <class _TSelf, int _numel, class _underlying, class _plain_t>
class EnumBase {
 protected:
  using TSelf = _TSelf;
  using underlying = _underlying;
  using plain_t = _plain_t;
  static constexpr int numel = _numel;
  EnumBase(_underlying _v) : v(_v) {
    CHECK(0 <= v && v < numel);
  }
  int v;

 public:
  const char* c_str() const {
    static std::vector<const char*> c_strs = collect<TSelf, underlying, numel>::c_str();
    return c_strs[v];
  }
  plain_t plain() const {
    static std::vector<plain_t> c_strs =
        collect<TSelf, underlying, numel>::template plain<plain_t>();
    return c_strs[v];
  }
};

}  // namespace enum_base_details

#define ENUM_DEF_HEADER(type, default_value, from_plain) \
  template <underlying v>                                \
  struct _integral_constant final {                      \
    template <underlying v2>                             \
    bool operator==(_integral_constant<v2>) const {      \
      return v == v2;                                    \
    }                                                    \
    template <underlying v2>                             \
    bool operator!=(_integral_constant<v2>) const {      \
      return v != v2;                                    \
    }                                                    \
    bool operator==(type other) const {                  \
      return v == other.v;                               \
    }                                                    \
    bool operator!=(type other) const {                  \
      return v != other.v;                               \
    }                                                    \
  };                                                     \
  type() : EnumBase(default_value) {                     \
  }                                                      \
  type(plain_t plain) : EnumBase(from_plain) {           \
  }                                                      \
  template <underlying _v>                               \
  bool operator==(_integral_constant<_v>) const {        \
    return v == _v;                                      \
  }                                                      \
  template <underlying _v>                               \
  bool operator!=(_integral_constant<_v>) const {        \
    return v != _v;                                      \
  }                                                      \
  bool operator==(type other) const {                    \
    return v == other.v;                                 \
  }                                                      \
  bool operator!=(type other) const {                    \
    return v != other.v;                                 \
  }                                                      \
  operator plain_t() const {                             \
    return plain();                                      \
  }

#define ENUM_DEF_ENTRY_WITH_NAME(type, name, value, plain_value, name_str) \
  type(_integral_constant<value>) : EnumBase(value) {                      \
  }                                                                        \
  using name = _integral_constant<value>;                                  \
  static constexpr plain_t _plain(_integral_constant<value>) {             \
    return plain_value;                                                    \
  }                                                                        \
  static const char* _c_str(_integral_constant<value>) {                   \
    static constexpr const char* result = name_str;                        \
    return result;                                                         \
  }

#define ENUM_DEF_ATTR(attr_name, attr_type, ...)     \
  attr_type attr_name() const {                      \
    static const attr_type result[] = {__VA_ARGS__}; \
    return result[v];                                \
  }

using enum_base_details::EnumBase;