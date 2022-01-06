// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ls.proto.eigen.proto

#include "ls.proto.eigen.pb.h"

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
namespace eigen {
constexpr VectorXd::VectorXd(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : coeff_()
  , size_(0){}
struct VectorXdDefaultTypeInternal {
  constexpr VectorXdDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~VectorXdDefaultTypeInternal() {}
  union {
    VectorXd _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT VectorXdDefaultTypeInternal _VectorXd_default_instance_;
constexpr MatrixXd::MatrixXd(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : row_()
  , rows_(0)
  , cols_(0){}
struct MatrixXdDefaultTypeInternal {
  constexpr MatrixXdDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~MatrixXdDefaultTypeInternal() {}
  union {
    MatrixXd _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT MatrixXdDefaultTypeInternal _MatrixXd_default_instance_;
}  // namespace eigen
}  // namespace proto
}  // namespace ls
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ls_2eproto_2eeigen_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ls_2eproto_2eeigen_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ls_2eproto_2eeigen_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ls_2eproto_2eeigen_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::VectorXd, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::VectorXd, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::VectorXd, coeff_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::VectorXd, size_),
  ~0u,
  0,
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::MatrixXd, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::MatrixXd, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::MatrixXd, row_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::MatrixXd, rows_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::eigen::MatrixXd, cols_),
  ~0u,
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 7, sizeof(::ls::proto::eigen::VectorXd)},
  { 9, 17, sizeof(::ls::proto::eigen::MatrixXd)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::eigen::_VectorXd_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::eigen::_MatrixXd_default_instance_),
};

const char descriptor_table_protodef_ls_2eproto_2eeigen_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\024ls.proto.eigen.proto\022\016ls.proto.eigen\"5"
  "\n\010VectorXd\022\r\n\005coeff\030\001 \003(\001\022\021\n\004size\030\002 \001(\005H"
  "\000\210\001\001B\007\n\005_size\"i\n\010MatrixXd\022%\n\003row\030\001 \003(\0132\030"
  ".ls.proto.eigen.VectorXd\022\021\n\004rows\030\002 \001(\005H\000"
  "\210\001\001\022\021\n\004cols\030\003 \001(\005H\001\210\001\001B\007\n\005_rowsB\007\n\005_cols"
  "b\006proto3"
  ;
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ls_2eproto_2eeigen_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ls_2eproto_2eeigen_2eproto = {
  false, false, 208, descriptor_table_protodef_ls_2eproto_2eeigen_2eproto, "ls.proto.eigen.proto", 
  &descriptor_table_ls_2eproto_2eeigen_2eproto_once, nullptr, 0, 2,
  schemas, file_default_instances, TableStruct_ls_2eproto_2eeigen_2eproto::offsets,
  file_level_metadata_ls_2eproto_2eeigen_2eproto, file_level_enum_descriptors_ls_2eproto_2eeigen_2eproto, file_level_service_descriptors_ls_2eproto_2eeigen_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ls_2eproto_2eeigen_2eproto_getter() {
  return &descriptor_table_ls_2eproto_2eeigen_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ls_2eproto_2eeigen_2eproto(&descriptor_table_ls_2eproto_2eeigen_2eproto);
namespace ls {
namespace proto {
namespace eigen {

// ===================================================================

class VectorXd::_Internal {
 public:
  using HasBits = decltype(std::declval<VectorXd>()._has_bits_);
  static void set_has_size(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
};

VectorXd::VectorXd(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  coeff_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.eigen.VectorXd)
}
VectorXd::VectorXd(const VectorXd& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      coeff_(from.coeff_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  size_ = from.size_;
  // @@protoc_insertion_point(copy_constructor:ls.proto.eigen.VectorXd)
}

void VectorXd::SharedCtor() {
size_ = 0;
}

VectorXd::~VectorXd() {
  // @@protoc_insertion_point(destructor:ls.proto.eigen.VectorXd)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void VectorXd::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void VectorXd::ArenaDtor(void* object) {
  VectorXd* _this = reinterpret_cast< VectorXd* >(object);
  (void)_this;
}
void VectorXd::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void VectorXd::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void VectorXd::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.eigen.VectorXd)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  coeff_.Clear();
  size_ = 0;
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* VectorXd::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated double coeff = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::PackedDoubleParser(_internal_mutable_coeff(), ptr, ctx);
          CHK_(ptr);
        } else if (static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 9) {
          _internal_add_coeff(::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr));
          ptr += sizeof(double);
        } else goto handle_unusual;
        continue;
      // optional int32 size = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_size(&has_bits);
          size_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* VectorXd::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.eigen.VectorXd)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated double coeff = 1;
  if (this->_internal_coeff_size() > 0) {
    target = stream->WriteFixedPacked(1, _internal_coeff(), target);
  }

  // optional int32 size = 2;
  if (_internal_has_size()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_size(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.eigen.VectorXd)
  return target;
}

size_t VectorXd::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.eigen.VectorXd)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated double coeff = 1;
  {
    unsigned int count = static_cast<unsigned int>(this->_internal_coeff_size());
    size_t data_size = 8UL * count;
    if (data_size > 0) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
            static_cast<::PROTOBUF_NAMESPACE_ID::int32>(data_size));
    }
    total_size += data_size;
  }

  // optional int32 size = 2;
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_size());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void VectorXd::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.eigen.VectorXd)
  GOOGLE_DCHECK_NE(&from, this);
  const VectorXd* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<VectorXd>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.eigen.VectorXd)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.eigen.VectorXd)
    MergeFrom(*source);
  }
}

void VectorXd::MergeFrom(const VectorXd& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.eigen.VectorXd)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  coeff_.MergeFrom(from.coeff_);
  if (from._internal_has_size()) {
    _internal_set_size(from._internal_size());
  }
}

void VectorXd::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.eigen.VectorXd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void VectorXd::CopyFrom(const VectorXd& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.eigen.VectorXd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool VectorXd::IsInitialized() const {
  return true;
}

void VectorXd::InternalSwap(VectorXd* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  coeff_.InternalSwap(&other->coeff_);
  swap(size_, other->size_);
}

::PROTOBUF_NAMESPACE_ID::Metadata VectorXd::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2eeigen_2eproto_getter, &descriptor_table_ls_2eproto_2eeigen_2eproto_once,
      file_level_metadata_ls_2eproto_2eeigen_2eproto[0]);
}

// ===================================================================

class MatrixXd::_Internal {
 public:
  using HasBits = decltype(std::declval<MatrixXd>()._has_bits_);
  static void set_has_rows(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static void set_has_cols(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

MatrixXd::MatrixXd(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena),
  row_(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.eigen.MatrixXd)
}
MatrixXd::MatrixXd(const MatrixXd& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_),
      row_(from.row_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&rows_, &from.rows_,
    static_cast<size_t>(reinterpret_cast<char*>(&cols_) -
    reinterpret_cast<char*>(&rows_)) + sizeof(cols_));
  // @@protoc_insertion_point(copy_constructor:ls.proto.eigen.MatrixXd)
}

void MatrixXd::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&rows_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&cols_) -
    reinterpret_cast<char*>(&rows_)) + sizeof(cols_));
}

MatrixXd::~MatrixXd() {
  // @@protoc_insertion_point(destructor:ls.proto.eigen.MatrixXd)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void MatrixXd::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void MatrixXd::ArenaDtor(void* object) {
  MatrixXd* _this = reinterpret_cast< MatrixXd* >(object);
  (void)_this;
}
void MatrixXd::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MatrixXd::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void MatrixXd::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.eigen.MatrixXd)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  row_.Clear();
  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    ::memset(&rows_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&cols_) -
        reinterpret_cast<char*>(&rows_)) + sizeof(cols_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MatrixXd::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // repeated .ls.proto.eigen.VectorXd row = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr -= 1;
          do {
            ptr += 1;
            ptr = ctx->ParseMessage(_internal_add_row(), ptr);
            CHK_(ptr);
            if (!ctx->DataAvailable(ptr)) break;
          } while (::PROTOBUF_NAMESPACE_ID::internal::ExpectTag<10>(ptr));
        } else goto handle_unusual;
        continue;
      // optional int32 rows = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          _Internal::set_has_rows(&has_bits);
          rows_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional int32 cols = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          _Internal::set_has_cols(&has_bits);
          cols_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* MatrixXd::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.eigen.MatrixXd)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated .ls.proto.eigen.VectorXd row = 1;
  for (unsigned int i = 0,
      n = static_cast<unsigned int>(this->_internal_row_size()); i < n; i++) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(1, this->_internal_row(i), target, stream);
  }

  // optional int32 rows = 2;
  if (_internal_has_rows()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_rows(), target);
  }

  // optional int32 cols = 3;
  if (_internal_has_cols()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_cols(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.eigen.MatrixXd)
  return target;
}

size_t MatrixXd::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.eigen.MatrixXd)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated .ls.proto.eigen.VectorXd row = 1;
  total_size += 1UL * this->_internal_row_size();
  for (const auto& msg : this->row_) {
    total_size +=
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(msg);
  }

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional int32 rows = 2;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_rows());
    }

    // optional int32 cols = 3;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
          this->_internal_cols());
    }

  }
  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MatrixXd::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.eigen.MatrixXd)
  GOOGLE_DCHECK_NE(&from, this);
  const MatrixXd* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MatrixXd>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.eigen.MatrixXd)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.eigen.MatrixXd)
    MergeFrom(*source);
  }
}

void MatrixXd::MergeFrom(const MatrixXd& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.eigen.MatrixXd)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  row_.MergeFrom(from.row_);
  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      rows_ = from.rows_;
    }
    if (cached_has_bits & 0x00000002u) {
      cols_ = from.cols_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void MatrixXd::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.eigen.MatrixXd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MatrixXd::CopyFrom(const MatrixXd& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.eigen.MatrixXd)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MatrixXd::IsInitialized() const {
  return true;
}

void MatrixXd::InternalSwap(MatrixXd* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  row_.InternalSwap(&other->row_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MatrixXd, cols_)
      + sizeof(MatrixXd::cols_)
      - PROTOBUF_FIELD_OFFSET(MatrixXd, rows_)>(
          reinterpret_cast<char*>(&rows_),
          reinterpret_cast<char*>(&other->rows_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MatrixXd::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2eeigen_2eproto_getter, &descriptor_table_ls_2eproto_2eeigen_2eproto_once,
      file_level_metadata_ls_2eproto_2eeigen_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace eigen
}  // namespace proto
}  // namespace ls
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ls::proto::eigen::VectorXd* Arena::CreateMaybeMessage< ::ls::proto::eigen::VectorXd >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::eigen::VectorXd >(arena);
}
template<> PROTOBUF_NOINLINE ::ls::proto::eigen::MatrixXd* Arena::CreateMaybeMessage< ::ls::proto::eigen::MatrixXd >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::eigen::MatrixXd >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>