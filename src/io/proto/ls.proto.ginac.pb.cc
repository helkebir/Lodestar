// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ls.proto.ginac.proto

#include "ls.proto.ginac.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG
namespace ls {
namespace proto {
namespace ginac {
constexpr symbol::symbol(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : name_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct symbolDefaultTypeInternal {
  constexpr symbolDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~symbolDefaultTypeInternal() {}
  union {
    symbol _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT symbolDefaultTypeInternal _symbol_default_instance_;
constexpr ex::ex(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : symbols_()
  , archive_(&::PROTOBUF_NAMESPACE_ID::internal::fixed_address_empty_string){}
struct exDefaultTypeInternal {
  constexpr exDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~exDefaultTypeInternal() {}
  union {
    ex _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT exDefaultTypeInternal _ex_default_instance_;
constexpr lst::lst(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : expressions_(){}
struct lstDefaultTypeInternal {
  constexpr lstDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~lstDefaultTypeInternal() {}
  union {
    lst _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT lstDefaultTypeInternal _lst_default_instance_;
}  // namespace ginac
}  // namespace proto
}  // namespace ls
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ls_2eproto_2eginac_2eproto[3];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ls_2eproto_2eginac_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ls_2eproto_2eginac_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ls_2eproto_2eginac_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::symbol, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::symbol, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::symbol, name_),
  0,
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::ex, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::ex, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::ex, archive_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::ex, symbols_),
  0,
  ~0u,
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::lst, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::ginac::lst, expressions_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 6, sizeof(::ls::proto::ginac::symbol)},
  { 7, 14, sizeof(::ls::proto::ginac::ex)},
  { 16, -1, sizeof(::ls::proto::ginac::lst)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::ginac::_symbol_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::ginac::_ex_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::ginac::_lst_default_instance_),
};

const char descriptor_table_protodef_ls_2eproto_2eginac_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024ls.proto.ginac.proto\022\016ls.proto.ginac\"$"
  "\n\006symbol\022\021\n\004name\030\001 \001(\tH\000\210\001\001B\007\n\005_name\"O\n\002"
  "ex\022\024\n\007archive\030\001 \001(\014H\000\210\001\001\022\'\n\007symbols\030\002 \003("
  "\0132\026.ls.proto.ginac.symbolB\n\n\010_archive\".\n"
  "\003lst\022\'\n\013expressions\030\001 \003(\0132\022.ls.proto.gin"
  "ac.exb\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ls_2eproto_2eginac_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ls_2eproto_2eginac_2eproto = {
  false, false, 213, descriptor_table_protodef_ls_2eproto_2eginac_2eproto, "ls.proto.ginac.proto", 
  &descriptor_table_ls_2eproto_2eginac_2eproto_once, nullptr, 0, 3,
  schemas, file_default_instances, TableStruct_ls_2eproto_2eginac_2eproto::offsets,
  file_level_metadata_ls_2eproto_2eginac_2eproto, file_level_enum_descriptors_ls_2eproto_2eginac_2eproto, file_level_service_descriptors_ls_2eproto_2eginac_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ls_2eproto_2eginac_2eproto_getter() {
  return &descriptor_table_ls_2eproto_2eginac_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ls_2eproto_2eginac_2eproto(&descriptor_table_ls_2eproto_2eginac_2eproto);
namespace ls {
namespace proto {
namespace ginac {

// ===================================================================

class symbol::_Internal {
 public:
  using HasBits = decltype(std::declval<symbol>()._has_bits_);
  static void set_has_name(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

symbol::symbol(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.ginac.symbol)
}
symbol::symbol(const symbol& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_name()) {
    name_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_name(), 
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:ls.proto.ginac.symbol)
}

void symbol::SharedCtor() {
name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

symbol::~symbol() {
  // @@protoc_insertion_point(destructor:ls.proto.ginac.symbol)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void symbol::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void symbol::ArenaDtor(void* object) {
  symbol* _this = reinterpret_cast< symbol* >(object);
  (void)_this;
}
void symbol::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void symbol::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void symbol::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.ginac.symbol)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    name_.ClearNonDefaultToEmpty();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* symbol::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional string name = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "ls.proto.ginac.symbol.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* symbol::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.ginac.symbol)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional string name = 1;
  if (_internal_has_name()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "ls.proto.ginac.symbol.name");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_name(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.ginac.symbol)
  return target;
}

size_t symbol::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.ginac.symbol)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // optional string name = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void symbol::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.ginac.symbol)
  GOOGLE_DCHECK_NE(&from, this);
  const symbol* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<symbol>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.ginac.symbol)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.ginac.symbol)
    MergeFrom(*source);
  }
}

void symbol::MergeFrom(const symbol& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.ginac.symbol)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_has_name()) {
    _internal_set_name(from._internal_name());
  }
}

void symbol::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.ginac.symbol)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void symbol::CopyFrom(const symbol& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.ginac.symbol)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool symbol::IsInitialized() const {
  return true;
}

void symbol::InternalSwap(symbol* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata symbol::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2eginac_2eproto_getter, &descriptor_table_ls_2eproto_2eginac_2eproto_once,
      file_level_metadata_ls_2eproto_2eginac_2eproto[0]);
}

// ===================================================================

class ex::_Internal {
 public:
  using HasBits = decltype(std::declval<ex>()._has_bits_);
  static void set_has_archive(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

ex::ex(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  symbols_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.ginac.ex)
}
ex::ex(const ex& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      symbols_(from.symbols_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  archive_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (from._internal_has_archive()) {
    archive_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, from._internal_archive(), 
      GetArena());
  }
  // @@protoc_insertion_point(copy_constructor:ls.proto.ginac.ex)
}

void ex::SharedCtor() {
archive_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

ex::~ex() {
  // @@protoc_insertion_point(destructor:ls.proto.ginac.ex)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void ex::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  archive_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void ex::ArenaDtor(void* object) {
  ex* _this = reinterpret_cast< ex* >(object);
  (void)_this;
}
void ex::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void ex::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void ex::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.ginac.ex)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  symbols_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    archive_.ClearNonDefaultToEmpty();
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* ex::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional bytes archive = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          auto str = _internal_mutable_archive();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // repeated .ls.proto.ginac.symbol symbols = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_symbols(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<18>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  _has_bits_.Or(has_bits);
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* ex::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.ginac.ex)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional bytes archive = 1;
  if (_internal_has_archive()) {
    target = stream->WriteBytesMaybeAliased(
        1, this->_internal_archive(), target);
  }

  // repeated .ls.proto.ginac.symbol symbols = 2;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_symbols_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(2, this->_internal_symbols(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.ginac.ex)
  return target;
}

size_t ex::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.ginac.ex)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .ls.proto.ginac.symbol symbols = 2;
  total_size += 1UL * this->_internal_symbols_size();
  for (const auto& msg : this->symbols_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  // optional bytes archive = 1;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_archive());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void ex::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.ginac.ex)
  GOOGLE_DCHECK_NE(&from, this);
  const ex* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<ex>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.ginac.ex)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.ginac.ex)
    MergeFrom(*source);
  }
}

void ex::MergeFrom(const ex& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.ginac.ex)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  symbols_.MergeFrom(from.symbols_);
  if (from._internal_has_archive()) {
    _internal_set_archive(from._internal_archive());
  }
}

void ex::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.ginac.ex)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void ex::CopyFrom(const ex& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.ginac.ex)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool ex::IsInitialized() const {
  return true;
}

void ex::InternalSwap(ex* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  symbols_.InternalSwap(&other->symbols_);
  archive_.Swap(&other->archive_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
}

::PROTOBUF_NAMESPACE_ID::Metadata ex::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2eginac_2eproto_getter, &descriptor_table_ls_2eproto_2eginac_2eproto_once,
      file_level_metadata_ls_2eproto_2eginac_2eproto[1]);
}

// ===================================================================

class lst::_Internal {
 public:
};

lst::lst(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  expressions_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.ginac.lst)
}
lst::lst(const lst& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      expressions_(from.expressions_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:ls.proto.ginac.lst)
}

void lst::SharedCtor() {
}

lst::~lst() {
  // @@protoc_insertion_point(destructor:ls.proto.ginac.lst)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void lst::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void lst::ArenaDtor(void* object) {
  lst* _this = reinterpret_cast< lst* >(object);
  (void)_this;
}
void lst::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void lst::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void lst::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.ginac.lst)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  expressions_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* lst::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .ls.proto.ginac.ex expressions = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_expressions(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag == 0) || ((tag & 7) == 4)) {
          CHK_(ptr);
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* lst::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.ginac.lst)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .ls.proto.ginac.ex expressions = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_expressions_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_expressions(i), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.ginac.lst)
  return target;
}

size_t lst::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.ginac.lst)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .ls.proto.ginac.ex expressions = 1;
  total_size += 1UL * this->_internal_expressions_size();
  for (const auto& msg : this->expressions_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void lst::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.ginac.lst)
  GOOGLE_DCHECK_NE(&from, this);
  const lst* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<lst>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.ginac.lst)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.ginac.lst)
    MergeFrom(*source);
  }
}

void lst::MergeFrom(const lst& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.ginac.lst)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  expressions_.MergeFrom(from.expressions_);
}

void lst::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.ginac.lst)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void lst::CopyFrom(const lst& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.ginac.lst)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool lst::IsInitialized() const {
  return true;
}

void lst::InternalSwap(lst* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  expressions_.InternalSwap(&other->expressions_);
}

::PROTOBUF_NAMESPACE_ID::Metadata lst::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2eginac_2eproto_getter, &descriptor_table_ls_2eproto_2eginac_2eproto_once,
      file_level_metadata_ls_2eproto_2eginac_2eproto[2]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace ginac
}  // namespace proto
}  // namespace ls
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ls::proto::ginac::symbol* Arena::CreateMaybeMessage< ::ls::proto::ginac::symbol >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::ginac::symbol >(arena);
}
template<> PROTOBUF_NOINLINE ::ls::proto::ginac::ex* Arena::CreateMaybeMessage< ::ls::proto::ginac::ex >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::ginac::ex >(arena);
}
template<> PROTOBUF_NOINLINE ::ls::proto::ginac::lst* Arena::CreateMaybeMessage< ::ls::proto::ginac::lst >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::ginac::lst >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
