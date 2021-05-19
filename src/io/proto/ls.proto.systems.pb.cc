// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ls.proto.systems.proto

#include "ls.proto.systems.pb.h"

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
namespace systems {
constexpr StateSpace::StateSpace(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : a_(nullptr)
  , b_(nullptr)
  , c_(nullptr)
  , d_(nullptr)
  , dt_(0)
  , isdiscrete_(false){}
struct StateSpaceDefaultTypeInternal {
  constexpr StateSpaceDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~StateSpaceDefaultTypeInternal() {}
  union {
    StateSpace _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT StateSpaceDefaultTypeInternal _StateSpace_default_instance_;
constexpr TransferFunction::TransferFunction(
  ::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized)
  : num_(nullptr)
  , den_(nullptr){}
struct TransferFunctionDefaultTypeInternal {
  constexpr TransferFunctionDefaultTypeInternal()
    : _instance(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized{}) {}
  ~TransferFunctionDefaultTypeInternal() {}
  union {
    TransferFunction _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT TransferFunctionDefaultTypeInternal _TransferFunction_default_instance_;
}  // namespace systems
}  // namespace proto
}  // namespace ls
static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_ls_2eproto_2esystems_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_ls_2eproto_2esystems_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_ls_2eproto_2esystems_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_ls_2eproto_2esystems_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, a_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, b_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, c_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, d_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, isdiscrete_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::StateSpace, dt_),
  0,
  1,
  2,
  3,
  5,
  4,
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::TransferFunction, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::TransferFunction, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::TransferFunction, num_),
  PROTOBUF_FIELD_OFFSET(::ls::proto::systems::TransferFunction, den_),
  0,
  1,
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 11, sizeof(::ls::proto::systems::StateSpace)},
  { 17, 24, sizeof(::ls::proto::systems::TransferFunction)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::systems::_StateSpace_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::ls::proto::systems::_TransferFunction_default_instance_),
};

const char descriptor_table_protodef_ls_2eproto_2esystems_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026ls.proto.systems.proto\022\020ls.proto.syste"
  "ms\032\024ls.proto.eigen.proto\"\214\002\n\nStateSpace\022"
  "(\n\001A\030\001 \001(\0132\030.ls.proto.eigen.MatrixXdH\000\210\001"
  "\001\022(\n\001B\030\002 \001(\0132\030.ls.proto.eigen.MatrixXdH\001"
  "\210\001\001\022(\n\001C\030\003 \001(\0132\030.ls.proto.eigen.MatrixXd"
  "H\002\210\001\001\022(\n\001D\030\004 \001(\0132\030.ls.proto.eigen.Matrix"
  "XdH\003\210\001\001\022\027\n\nisDiscrete\030\005 \001(\010H\004\210\001\001\022\017\n\002dt\030\006"
  " \001(\001H\005\210\001\001B\004\n\002_AB\004\n\002_BB\004\n\002_CB\004\n\002_DB\r\n\013_is"
  "DiscreteB\005\n\003_dt\"z\n\020TransferFunction\022*\n\003n"
  "um\030\001 \001(\0132\030.ls.proto.eigen.VectorXdH\000\210\001\001\022"
  "*\n\003den\030\002 \001(\0132\030.ls.proto.eigen.VectorXdH\001"
  "\210\001\001B\006\n\004_numB\006\n\004_denb\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_ls_2eproto_2esystems_2eproto_deps[1] = {
  &::descriptor_table_ls_2eproto_2eeigen_2eproto,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_ls_2eproto_2esystems_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ls_2eproto_2esystems_2eproto = {
  false, false, 467, descriptor_table_protodef_ls_2eproto_2esystems_2eproto, "ls.proto.systems.proto", 
  &descriptor_table_ls_2eproto_2esystems_2eproto_once, descriptor_table_ls_2eproto_2esystems_2eproto_deps, 1, 2,
  schemas, file_default_instances, TableStruct_ls_2eproto_2esystems_2eproto::offsets,
  file_level_metadata_ls_2eproto_2esystems_2eproto, file_level_enum_descriptors_ls_2eproto_2esystems_2eproto, file_level_service_descriptors_ls_2eproto_2esystems_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable* descriptor_table_ls_2eproto_2esystems_2eproto_getter() {
  return &descriptor_table_ls_2eproto_2esystems_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY static ::PROTOBUF_NAMESPACE_ID::internal::AddDescriptorsRunner dynamic_init_dummy_ls_2eproto_2esystems_2eproto(&descriptor_table_ls_2eproto_2esystems_2eproto);
namespace ls {
namespace proto {
namespace systems {

// ===================================================================

class StateSpace::_Internal {
 public:
  using HasBits = decltype(std::declval<StateSpace>()._has_bits_);
  static const ::ls::proto::eigen::MatrixXd& a(const StateSpace* msg);
  static void set_has_a(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static const ::ls::proto::eigen::MatrixXd& b(const StateSpace* msg);
  static void set_has_b(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
  static const ::ls::proto::eigen::MatrixXd& c(const StateSpace* msg);
  static void set_has_c(HasBits* has_bits) {
    (*has_bits)[0] |= 4u;
  }
  static const ::ls::proto::eigen::MatrixXd& d(const StateSpace* msg);
  static void set_has_d(HasBits* has_bits) {
    (*has_bits)[0] |= 8u;
  }
  static void set_has_isdiscrete(HasBits* has_bits) {
    (*has_bits)[0] |= 32u;
  }
  static void set_has_dt(HasBits* has_bits) {
    (*has_bits)[0] |= 16u;
  }
};

const ::ls::proto::eigen::MatrixXd&
StateSpace::_Internal::a(const StateSpace* msg) {
  return *msg->a_;
}
const ::ls::proto::eigen::MatrixXd&
StateSpace::_Internal::b(const StateSpace* msg) {
  return *msg->b_;
}
const ::ls::proto::eigen::MatrixXd&
StateSpace::_Internal::c(const StateSpace* msg) {
  return *msg->c_;
}
const ::ls::proto::eigen::MatrixXd&
StateSpace::_Internal::d(const StateSpace* msg) {
  return *msg->d_;
}
void StateSpace::clear_a() {
  if (a_ != nullptr) a_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
void StateSpace::clear_b() {
  if (b_ != nullptr) b_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
void StateSpace::clear_c() {
  if (c_ != nullptr) c_->Clear();
  _has_bits_[0] &= ~0x00000004u;
}
void StateSpace::clear_d() {
  if (d_ != nullptr) d_->Clear();
  _has_bits_[0] &= ~0x00000008u;
}
StateSpace::StateSpace(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.systems.StateSpace)
}
StateSpace::StateSpace(const StateSpace& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_a()) {
    a_ = new ::ls::proto::eigen::MatrixXd(*from.a_);
  } else {
    a_ = nullptr;
  }
  if (from._internal_has_b()) {
    b_ = new ::ls::proto::eigen::MatrixXd(*from.b_);
  } else {
    b_ = nullptr;
  }
  if (from._internal_has_c()) {
    c_ = new ::ls::proto::eigen::MatrixXd(*from.c_);
  } else {
    c_ = nullptr;
  }
  if (from._internal_has_d()) {
    d_ = new ::ls::proto::eigen::MatrixXd(*from.d_);
  } else {
    d_ = nullptr;
  }
  ::memcpy(&dt_, &from.dt_,
    static_cast<size_t>(reinterpret_cast<char*>(&isdiscrete_) -
    reinterpret_cast<char*>(&dt_)) + sizeof(isdiscrete_));
  // @@protoc_insertion_point(copy_constructor:ls.proto.systems.StateSpace)
}

void StateSpace::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&a_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&isdiscrete_) -
    reinterpret_cast<char*>(&a_)) + sizeof(isdiscrete_));
}

StateSpace::~StateSpace() {
  // @@protoc_insertion_point(destructor:ls.proto.systems.StateSpace)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void StateSpace::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete a_;
  if (this != internal_default_instance()) delete b_;
  if (this != internal_default_instance()) delete c_;
  if (this != internal_default_instance()) delete d_;
}

void StateSpace::ArenaDtor(void* object) {
  StateSpace* _this = reinterpret_cast< StateSpace* >(object);
  (void)_this;
}
void StateSpace::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void StateSpace::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void StateSpace::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.systems.StateSpace)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000000fu) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(a_ != nullptr);
      a_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(b_ != nullptr);
      b_->Clear();
    }
    if (cached_has_bits & 0x00000004u) {
      GOOGLE_DCHECK(c_ != nullptr);
      c_->Clear();
    }
    if (cached_has_bits & 0x00000008u) {
      GOOGLE_DCHECK(d_ != nullptr);
      d_->Clear();
    }
  }
  if (cached_has_bits & 0x00000030u) {
    ::memset(&dt_, 0, static_cast<size_t>(
        reinterpret_cast<char*>(&isdiscrete_) -
        reinterpret_cast<char*>(&dt_)) + sizeof(isdiscrete_));
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* StateSpace::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .ls.proto.eigen.MatrixXd A = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_a(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .ls.proto.eigen.MatrixXd B = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_b(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .ls.proto.eigen.MatrixXd C = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          ptr = ctx->ParseMessage(_internal_mutable_c(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .ls.proto.eigen.MatrixXd D = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          ptr = ctx->ParseMessage(_internal_mutable_d(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional bool isDiscrete = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 40)) {
          _Internal::set_has_isdiscrete(&has_bits);
          isdiscrete_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional double dt = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 49)) {
          _Internal::set_has_dt(&has_bits);
          dt_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<double>(ptr);
          ptr += sizeof(double);
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

::PROTOBUF_NAMESPACE_ID::uint8* StateSpace::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.systems.StateSpace)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .ls.proto.eigen.MatrixXd A = 1;
  if (_internal_has_a()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::a(this), target, stream);
  }

  // optional .ls.proto.eigen.MatrixXd B = 2;
  if (_internal_has_b()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::b(this), target, stream);
  }

  // optional .ls.proto.eigen.MatrixXd C = 3;
  if (_internal_has_c()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        3, _Internal::c(this), target, stream);
  }

  // optional .ls.proto.eigen.MatrixXd D = 4;
  if (_internal_has_d()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        4, _Internal::d(this), target, stream);
  }

  // optional bool isDiscrete = 5;
  if (_internal_has_isdiscrete()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteBoolToArray(5, this->_internal_isdiscrete(), target);
  }

  // optional double dt = 6;
  if (_internal_has_dt()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteDoubleToArray(6, this->_internal_dt(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.systems.StateSpace)
  return target;
}

size_t StateSpace::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.systems.StateSpace)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    // optional .ls.proto.eigen.MatrixXd A = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *a_);
    }

    // optional .ls.proto.eigen.MatrixXd B = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *b_);
    }

    // optional .ls.proto.eigen.MatrixXd C = 3;
    if (cached_has_bits & 0x00000004u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *c_);
    }

    // optional .ls.proto.eigen.MatrixXd D = 4;
    if (cached_has_bits & 0x00000008u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *d_);
    }

    // optional double dt = 6;
    if (cached_has_bits & 0x00000010u) {
      total_size += 1 + 8;
    }

    // optional bool isDiscrete = 5;
    if (cached_has_bits & 0x00000020u) {
      total_size += 1 + 1;
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

void StateSpace::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.systems.StateSpace)
  GOOGLE_DCHECK_NE(&from, this);
  const StateSpace* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<StateSpace>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.systems.StateSpace)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.systems.StateSpace)
    MergeFrom(*source);
  }
}

void StateSpace::MergeFrom(const StateSpace& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.systems.StateSpace)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x0000003fu) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_a()->::ls::proto::eigen::MatrixXd::MergeFrom(from._internal_a());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_mutable_b()->::ls::proto::eigen::MatrixXd::MergeFrom(from._internal_b());
    }
    if (cached_has_bits & 0x00000004u) {
      _internal_mutable_c()->::ls::proto::eigen::MatrixXd::MergeFrom(from._internal_c());
    }
    if (cached_has_bits & 0x00000008u) {
      _internal_mutable_d()->::ls::proto::eigen::MatrixXd::MergeFrom(from._internal_d());
    }
    if (cached_has_bits & 0x00000010u) {
      dt_ = from.dt_;
    }
    if (cached_has_bits & 0x00000020u) {
      isdiscrete_ = from.isdiscrete_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void StateSpace::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.systems.StateSpace)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void StateSpace::CopyFrom(const StateSpace& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.systems.StateSpace)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool StateSpace::IsInitialized() const {
  return true;
}

void StateSpace::InternalSwap(StateSpace* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(StateSpace, isdiscrete_)
      + sizeof(StateSpace::isdiscrete_)
      - PROTOBUF_FIELD_OFFSET(StateSpace, a_)>(
          reinterpret_cast<char*>(&a_),
          reinterpret_cast<char*>(&other->a_));
}

::PROTOBUF_NAMESPACE_ID::Metadata StateSpace::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2esystems_2eproto_getter, &descriptor_table_ls_2eproto_2esystems_2eproto_once,
      file_level_metadata_ls_2eproto_2esystems_2eproto[0]);
}

// ===================================================================

class TransferFunction::_Internal {
 public:
  using HasBits = decltype(std::declval<TransferFunction>()._has_bits_);
  static const ::ls::proto::eigen::VectorXd& num(const TransferFunction* msg);
  static void set_has_num(HasBits* has_bits) {
    (*has_bits)[0] |= 1u;
  }
  static const ::ls::proto::eigen::VectorXd& den(const TransferFunction* msg);
  static void set_has_den(HasBits* has_bits) {
    (*has_bits)[0] |= 2u;
  }
};

const ::ls::proto::eigen::VectorXd&
TransferFunction::_Internal::num(const TransferFunction* msg) {
  return *msg->num_;
}
const ::ls::proto::eigen::VectorXd&
TransferFunction::_Internal::den(const TransferFunction* msg) {
  return *msg->den_;
}
void TransferFunction::clear_num() {
  if (num_ != nullptr) num_->Clear();
  _has_bits_[0] &= ~0x00000001u;
}
void TransferFunction::clear_den() {
  if (den_ != nullptr) den_->Clear();
  _has_bits_[0] &= ~0x00000002u;
}
TransferFunction::TransferFunction(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:ls.proto.systems.TransferFunction)
}
TransferFunction::TransferFunction(const TransferFunction& from)
  : ::PROTOBUF_NAMESPACE_ID::Message(),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  if (from._internal_has_num()) {
    num_ = new ::ls::proto::eigen::VectorXd(*from.num_);
  } else {
    num_ = nullptr;
  }
  if (from._internal_has_den()) {
    den_ = new ::ls::proto::eigen::VectorXd(*from.den_);
  } else {
    den_ = nullptr;
  }
  // @@protoc_insertion_point(copy_constructor:ls.proto.systems.TransferFunction)
}

void TransferFunction::SharedCtor() {
::memset(reinterpret_cast<char*>(this) + static_cast<size_t>(
    reinterpret_cast<char*>(&num_) - reinterpret_cast<char*>(this)),
    0, static_cast<size_t>(reinterpret_cast<char*>(&den_) -
    reinterpret_cast<char*>(&num_)) + sizeof(den_));
}

TransferFunction::~TransferFunction() {
  // @@protoc_insertion_point(destructor:ls.proto.systems.TransferFunction)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void TransferFunction::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  if (this != internal_default_instance()) delete num_;
  if (this != internal_default_instance()) delete den_;
}

void TransferFunction::ArenaDtor(void* object) {
  TransferFunction* _this = reinterpret_cast< TransferFunction* >(object);
  (void)_this;
}
void TransferFunction::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void TransferFunction::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}

void TransferFunction::Clear() {
// @@protoc_insertion_point(message_clear_start:ls.proto.systems.TransferFunction)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      GOOGLE_DCHECK(num_ != nullptr);
      num_->Clear();
    }
    if (cached_has_bits & 0x00000002u) {
      GOOGLE_DCHECK(den_ != nullptr);
      den_->Clear();
    }
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* TransferFunction::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  _Internal::HasBits has_bits{};
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // optional .ls.proto.eigen.VectorXd num = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_num(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // optional .ls.proto.eigen.VectorXd den = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          ptr = ctx->ParseMessage(_internal_mutable_den(), ptr);
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

::PROTOBUF_NAMESPACE_ID::uint8* TransferFunction::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:ls.proto.systems.TransferFunction)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // optional .ls.proto.eigen.VectorXd num = 1;
  if (_internal_has_num()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::num(this), target, stream);
  }

  // optional .ls.proto.eigen.VectorXd den = 2;
  if (_internal_has_den()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        2, _Internal::den(this), target, stream);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:ls.proto.systems.TransferFunction)
  return target;
}

size_t TransferFunction::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:ls.proto.systems.TransferFunction)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    // optional .ls.proto.eigen.VectorXd num = 1;
    if (cached_has_bits & 0x00000001u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *num_);
    }

    // optional .ls.proto.eigen.VectorXd den = 2;
    if (cached_has_bits & 0x00000002u) {
      total_size += 1 +
        ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
          *den_);
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

void TransferFunction::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:ls.proto.systems.TransferFunction)
  GOOGLE_DCHECK_NE(&from, this);
  const TransferFunction* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<TransferFunction>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:ls.proto.systems.TransferFunction)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:ls.proto.systems.TransferFunction)
    MergeFrom(*source);
  }
}

void TransferFunction::MergeFrom(const TransferFunction& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:ls.proto.systems.TransferFunction)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000003u) {
    if (cached_has_bits & 0x00000001u) {
      _internal_mutable_num()->::ls::proto::eigen::VectorXd::MergeFrom(from._internal_num());
    }
    if (cached_has_bits & 0x00000002u) {
      _internal_mutable_den()->::ls::proto::eigen::VectorXd::MergeFrom(from._internal_den());
    }
  }
}

void TransferFunction::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:ls.proto.systems.TransferFunction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void TransferFunction::CopyFrom(const TransferFunction& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:ls.proto.systems.TransferFunction)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool TransferFunction::IsInitialized() const {
  return true;
}

void TransferFunction::InternalSwap(TransferFunction* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(TransferFunction, den_)
      + sizeof(TransferFunction::den_)
      - PROTOBUF_FIELD_OFFSET(TransferFunction, num_)>(
          reinterpret_cast<char*>(&num_),
          reinterpret_cast<char*>(&other->num_));
}

::PROTOBUF_NAMESPACE_ID::Metadata TransferFunction::GetMetadata() const {
  return ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(
      &descriptor_table_ls_2eproto_2esystems_2eproto_getter, &descriptor_table_ls_2eproto_2esystems_2eproto_once,
      file_level_metadata_ls_2eproto_2esystems_2eproto[1]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace systems
}  // namespace proto
}  // namespace ls
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::ls::proto::systems::StateSpace* Arena::CreateMaybeMessage< ::ls::proto::systems::StateSpace >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::systems::StateSpace >(arena);
}
template<> PROTOBUF_NOINLINE ::ls::proto::systems::TransferFunction* Arena::CreateMaybeMessage< ::ls::proto::systems::TransferFunction >(Arena* arena) {
  return Arena::CreateMessageInternal< ::ls::proto::systems::TransferFunction >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
