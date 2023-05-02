/* Automatically generated nanopb header */
/* Generated by nanopb-0.4.8-dev */

#ifndef PB_MOTOR_PB_H_INCLUDED
#define PB_MOTOR_PB_H_INCLUDED
#include <pb.h>

#if PB_PROTO_HEADER_VERSION != 40
#error Regenerate this file with the current version of nanopb generator.
#endif

/* Enum definitions */
typedef enum _Action {
    Action_NoAction = 0,
    Action_SetPower = 1,
    Action_GoFor = 2,
    Action_GoTo = 3,
    Action_ResetZeroPosition = 4,
    Action_GetPosition = 5,
    Action_Stop = 6,
    Action_IsPowered = 7,
    Action_IsMoving = 8
} Action;

/* Struct definitions */
typedef struct _MotorRequest {
    Action action;
    bool has_power;
    float power;
    bool has_rpm;
    float rpm;
    bool has_revolutions;
    float revolutions;
    bool has_offset;
    float offset;
} MotorRequest;

typedef struct _MotorResponse {
    Action action;
    bool has_val_b;
    bool val_b;
    bool has_val_f;
    float val_f;
} MotorResponse;


#ifdef __cplusplus
extern "C" {
#endif

/* Helper constants for enums */
#define _Action_MIN Action_NoAction
#define _Action_MAX Action_IsMoving
#define _Action_ARRAYSIZE ((Action)(Action_IsMoving+1))

#define MotorRequest_action_ENUMTYPE Action

#define MotorResponse_action_ENUMTYPE Action


/* Initializer values for message structs */
#define MotorRequest_init_default                {_Action_MIN, false, 0, false, 0, false, 0, false, 0}
#define MotorResponse_init_default               {_Action_MIN, false, 0, false, 0}
#define MotorRequest_init_zero                   {_Action_MIN, false, 0, false, 0, false, 0, false, 0}
#define MotorResponse_init_zero                  {_Action_MIN, false, 0, false, 0}

/* Field tags (for use in manual encoding/decoding) */
#define MotorRequest_action_tag                  1
#define MotorRequest_power_tag                   2
#define MotorRequest_rpm_tag                     3
#define MotorRequest_revolutions_tag             4
#define MotorRequest_offset_tag                  5
#define MotorResponse_action_tag                 1
#define MotorResponse_val_b_tag                  2
#define MotorResponse_val_f_tag                  3

/* Struct field encoding specification for nanopb */
#define MotorRequest_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    action,            1) \
X(a, STATIC,   OPTIONAL, FLOAT,    power,             2) \
X(a, STATIC,   OPTIONAL, FLOAT,    rpm,               3) \
X(a, STATIC,   OPTIONAL, FLOAT,    revolutions,       4) \
X(a, STATIC,   OPTIONAL, FLOAT,    offset,            5)
#define MotorRequest_CALLBACK NULL
#define MotorRequest_DEFAULT NULL

#define MotorResponse_FIELDLIST(X, a) \
X(a, STATIC,   SINGULAR, UENUM,    action,            1) \
X(a, STATIC,   OPTIONAL, BOOL,     val_b,             2) \
X(a, STATIC,   OPTIONAL, FLOAT,    val_f,             3)
#define MotorResponse_CALLBACK NULL
#define MotorResponse_DEFAULT NULL

extern const pb_msgdesc_t MotorRequest_msg;
extern const pb_msgdesc_t MotorResponse_msg;

/* Defines for backwards compatibility with code written before nanopb-0.4.0 */
#define MotorRequest_fields &MotorRequest_msg
#define MotorResponse_fields &MotorResponse_msg

/* Maximum encoded size of messages (where known) */
#define MotorRequest_size                        22
#define MotorResponse_size                       9

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif
