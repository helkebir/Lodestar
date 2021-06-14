/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.4.5 */

#include "Vector.pb.h"
#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

PB_BIND(npb_Vector2d, npb_Vector2d, AUTO)


PB_BIND(npb_Vector2f, npb_Vector2f, AUTO)


PB_BIND(npb_Vector3d, npb_Vector3d, AUTO)


PB_BIND(npb_Vector3f, npb_Vector3f, AUTO)


PB_BIND(npb_Vector4d, npb_Vector4d, AUTO)


PB_BIND(npb_Vector4f, npb_Vector4f, AUTO)


PB_BIND(npb_Vector6d, npb_Vector6d, AUTO)


PB_BIND(npb_Vector6f, npb_Vector6f, AUTO)


PB_BIND(npb_Vector8d, npb_Vector8d, AUTO)


PB_BIND(npb_Vector8f, npb_Vector8f, AUTO)


PB_BIND(npb_Vector12d, npb_Vector12d, AUTO)


PB_BIND(npb_Vector12f, npb_Vector12f, AUTO)


PB_BIND(npb_Vector16d, npb_Vector16d, AUTO)


PB_BIND(npb_Vector16f, npb_Vector16f, AUTO)


PB_BIND(npb_Vector32d, npb_Vector32d, 2)


PB_BIND(npb_Vector32f, npb_Vector32f, AUTO)


PB_BIND(npb_Vector64d, npb_Vector64d, 2)


PB_BIND(npb_Vector64f, npb_Vector64f, 2)



#ifndef PB_CONVERT_DOUBLE_FLOAT
/* On some platforms (such as AVR), double is really float.
 * To be able to encode/decode double on these platforms, you need.
 * to define PB_CONVERT_DOUBLE_FLOAT in pb.h or compiler command line.
 */
PB_STATIC_ASSERT(sizeof(double) == 8, DOUBLE_MUST_BE_8_BYTES)
#endif
