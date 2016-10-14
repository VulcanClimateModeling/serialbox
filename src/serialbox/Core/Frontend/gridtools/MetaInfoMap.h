//===-- serialbox/Core/Frontend/gridtools/MetaInfoMap.h -----------------------------*- C++ -*-===//
//
//                                    S E R I A L B O X
//
// This file is distributed under terms of BSD license.
// See LICENSE.txt for more information
//
//===------------------------------------------------------------------------------------------===//
//
/// \file
/// This file contains the gridtools implementation of the meta-information.
///
//===------------------------------------------------------------------------------------------===//

#ifndef SERIALBOX_CORE_FRONTEND_GRIDTOOLS_META_INFO_MAP_H
#define SERIALBOX_CORE_FRONTEND_GRIDTOOLS_META_INFO_MAP_H

#include "serialbox/Core/Frontend/gridtools/Exception.h"
#include "serialbox/Core/Frontend/gridtools/MetaInfoValue.h"
#include "serialbox/Core/MetaInfoMap.h"
#include <memory>

namespace serialbox {

namespace gridtools {

/// \brief Hash-map of meta-information of the form ´key = value´ pair or
/// ´key = {value1, ..., valueN}´
///
/// They keys are strings (std::string), while the values can be booleans, integers (32 and 64 bit),
/// floating point numbers (32 and 64 bit) or strings.
class meta_info_map {
public:
  /// \brief Type of the underlying hash-map
  using map_type = MetaInfoMap::map_type;

  /// \brief Type of an entry of the MetaInfoMap (`std::pair<std::string, MetaInfoValue>`)
  using value_type = map_type::value_type;

  /// \brief Type of the key (`std::string`)
  using key_type = map_type::key_type;

  /// \brief Type of the value (`MetaInfoMap::Value`)
  using mapped_type = map_type::mapped_type;

  /// \brief An unsigned integral type (`std::size_t`)
  using size_type = map_type::size_type;

  /// \brief A forward iterator to `value_type`
  using iterator = map_type::iterator;

  /// \brief A forward iterator to `const value_type`
  using const_iterator = map_type::const_iterator;

  /// \brief Default constructor (empty map)
  meta_info_map() : mapImpl_(std::make_shared<MetaInfoMap>()) {}

  /// \brief Construct from initalizer-list
  ///
  /// \b Example:
  /// \code
  ///   meta_info_map m({{"key1", meta_info_value(4.0)}, {"key2", meta_info_value(2))}});
  /// \endcode
  explicit meta_info_map(std::initializer_list<value_type> list)
      : mapImpl_(std::make_shared<MetaInfoMap>(list)) {}

  /// \brief Construct with MetaInfoMap (internal use)
  explicit meta_info_map(const std::shared_ptr<MetaInfoMap>& map) { mapImpl_ = map; }

  /// \brief Copy constructor
  ///
  /// This performs a \i shallow copy, meaning the objects share the same underlying MetaInfoMap.
  /// To deep copy the object call meta_info_map::clone().
  ///
  /// \b Example
  /// \code
  ///   meta_info_map m1 = {{"key1", meta_info_value(4.0)}, {"key2", meta_info_value(2))}};
  ///   meta_info_map m2 = m1;
  ///
  ///   m1.clear();
  ///   assert(m2.empty()); // m1 and m2 do share the same MetaInfoMap, hence m2 is empty as well
  /// \endcode
  ///
  /// \see meta_info_map::clone()
  meta_info_map(const meta_info_map&) = default;

  /// \brief Move constructor
  meta_info_map(meta_info_map&&) = default;

  /// \brief Copy assignment
  ///
  /// This performs a \i shallow copy, meaning the objects share the same underlying MetaInfoMap.
  /// To deep copy the object call meta_info_map::clone().
  ///
  /// \b Example
  /// \code
  ///   meta_info_map m1 = {{"key1", meta_info_value(4.0)}, {"key2", meta_info_value(2))}};
  ///   meta_info_map m2 = m1;
  ///
  ///   m1.clear();
  ///   assert(m2.empty()); // m1 and m2 do share the same MetaInfoMap, hence m2 is empty as well
  /// \endcode
  ///
  /// \see meta_info_map::clone
  meta_info_map& operator=(const meta_info_map&) = default;

  /// \brief Move assignment
  meta_info_map& operator=(meta_info_map&&) = default;

  /// \brief Construct from initalizer-list
  ///
  /// \b Example:
  /// \code
  ///   meta_info_map m1 = {{"key1", meta_info_value(4.0)}, {"key2", meta_info_value(2))}};
  /// \endcode
  meta_info_map& operator=(std::initializer_list<value_type> list) {
    mapImpl_ = std::make_shared<MetaInfoMap>(list);
    return (*this);
  }

  /// \brief Clone the current meta_info_map object by performing a deep copy
  ///
  /// \Example: To deep copy a meta_info_map
  /// \code
  ///   meta_info_map m1 = {{"key1", double(4)}, {"key2", int(2)}};
  ///   meta_info_map m2 = m1.clone();
  ///
  ///   m1.clear();
  ///   assert(!m2.empty()); // m1 and m2 do NOT share the same MetaInfoMap, hence m2 is not empty
  /// \endcode
  meta_info_map clone() const { return meta_info_map(std::make_shared<MetaInfoMap>(*mapImpl_)); }

  /// \brief Check if key exists in the map
  ///
  /// \param key  Key to be searched for
  ///
  /// \return True iff the key is present
  template <class StringType>
  bool has_key(StringType&& key) const noexcept {
    return mapImpl_->hasKey(std::forward<StringType>(key));
  }

  /// \brief Get vector of strings of all available keys
  ///
  /// To get the corresponding TypeIDs, use ´meta_info_map::types()´.
  ///
  /// \return vector of strings of all keys
  ///
  /// \see
  /// meta_info_map::types
  std::vector<std::string> keys() const { return mapImpl_->keys(); }

  /// \brief Get vector of all available keys
  ///
  /// To get the corresponding keys, use ´meta_info_map::keys()´.
  ///
  /// \return vector of TypeIDs of all elements
  ///
  /// \see meta_info_map::keys
  std::vector<TypeID> types() const { return mapImpl_->types(); }

  /// \brief Search the container for an element with a key equivalent to ´key´ and return an
  /// iterator to it if found, otherwise it returns an iterator to meta_info_map::end
  ///
  /// \param key  Key to be searched for
  ///
  /// \return An iterator to the element, if an element with specified key is found, or
  /// meta_info_map::end otherwise
  /// @{
  template <class StringType>
  iterator find(StringType&& key) noexcept {
    return mapImpl_->find(std::forward<StringType>(key));
  }
  template <class StringType>
  const_iterator find(StringType&& key) const noexcept {
    return mapImpl_->find(std::forward<StringType>(key));
  }
  /// @}

  /// \brief Insert a new element in the map
  ///
  /// The element is inserted only if its key is not equivalent to the key of any other element
  /// already in the map (keys in a MetaInfoMap are unique).
  ///
  /// \param key    Key of the new element
  /// \param value  Object to be copied to (or moved as) the value of the new element
  ///
  /// \return Value indicating whether the element was successfully inserted or not
  template <class KeyType, class ValueType>
  bool insert(KeyType&& key, ValueType&& value) noexcept {
    return mapImpl_->insert(std::forward<KeyType>(key), std::forward<ValueType>(value));
  }

  /// \brief Convert value of element with key ´key´ to type ´T´
  ///
  /// If the type ´T´ is different than the internally stored type, the function does its best to
  /// convert the value to ´T´ in a meaningful way.
  ///
  /// \param key    Key of the new element
  ///
  /// \return Copy of the value of the element as type ´T´
  ///
  /// \throw exception  Key ´key´ does not exist or conversion results in truncation of the value
  ///
  /// \see MetaInfoValue::as
  template <class ValueType, class KeyType>
  ValueType as(KeyType&& key) const {
    return mapImpl_->at(std::forward<KeyType>(key)).template as<ValueType>();
  }

  /// \brief Removes from the MetaInfoMap either a single element or a range of
  /// elements [first,last)
  /// @{
  iterator erase(const_iterator position) { return mapImpl_->erase(position); }
  size_type erase(const key_type& key) { return mapImpl_->erase(key); }
  iterator erase(const_iterator first, const_iterator last) { return mapImpl_->erase(first, last); }
  /// @}

  /// \brief Return a reference to mapped value given by key
  /// @{
  mapped_type& operator[](const key_type& key) noexcept { return mapImpl_->operator[](key); }
  mapped_type& operator[](key_type&& key) noexcept { return mapImpl_->operator[](key); }
  /// @}

  /// \brief Return a reference to mapped value given by key
  ///
  /// \throw exception  No mapped value with given key exists
  /// @{
  mapped_type& at(const key_type& key) { return mapImpl_->at(key); }
  const mapped_type& at(const key_type& key) const { return mapImpl_->at(key); }
  /// @}

  /// \brief Returns the number of elements in the meta_info_map
  std::size_t size() const noexcept { return mapImpl_->size(); }

  /// \brief Returns a bool value indicating whether the meta_info_map is empty, i.e. whether its
  /// size is 0
  bool empty() const noexcept { return mapImpl_->empty(); }

  /// \brief All the elements in the meta_info_map are dropped: their destructors are called, and
  /// they are removed from the container, leaving it with a size of 0
  void clear() noexcept { mapImpl_->clear(); }

  /// \brief Returns an iterator pointing to the first element in the meta_info_map_map
  iterator begin() noexcept { return mapImpl_->begin(); }
  const_iterator begin() const noexcept { return mapImpl_->begin(); }

  /// \brief Returns an iterator pointing to the past-the-end element in the meta_info_map_map
  iterator end() noexcept { return mapImpl_->end(); }
  const_iterator end() const noexcept { return mapImpl_->end(); }

  /// \brief Swap with other
  void swap(meta_info_map& other) noexcept { mapImpl_->swap(*other.mapImpl_); }

  /// \brief Test for equality
  bool operator==(const meta_info_map& right) const noexcept {
    return (*mapImpl_ == *right.mapImpl_);
  }

  /// \brief Test for inequality
  bool operator!=(const meta_info_map& right) const noexcept { return (!(*this == right)); }

  /// \brief Convert to stream
  template <class StreamType>
  friend std::ostream& operator<<(StreamType&& stream, const meta_info_map& s) {
    return (stream << *s.mapImpl_);
  }

private:
  std::shared_ptr<MetaInfoMap> mapImpl_;
};

} // namespace gridtools

} // namespace serialbox

#endif