from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor
GoFor: Action
GoTo: Action
IsMoving: Action
IsPowered: Action
NoAction: Action
SetPower: Action
Stop: Action
getPosition: Action
resetZeroPosition: Action

class MotorRequest(_message.Message):
    __slots__ = ["action", "offset", "power", "revolutions", "rpm"]
    ACTION_FIELD_NUMBER: _ClassVar[int]
    OFFSET_FIELD_NUMBER: _ClassVar[int]
    POWER_FIELD_NUMBER: _ClassVar[int]
    REVOLUTIONS_FIELD_NUMBER: _ClassVar[int]
    RPM_FIELD_NUMBER: _ClassVar[int]
    action: Action
    offset: float
    power: float
    revolutions: float
    rpm: float
    def __init__(self, action: _Optional[_Union[Action, str]] = ..., power: _Optional[float] = ..., rpm: _Optional[float] = ..., revolutions: _Optional[float] = ..., offset: _Optional[float] = ...) -> None: ...

class MotorResponse(_message.Message):
    __slots__ = ["action", "val_b", "val_f"]
    ACTION_FIELD_NUMBER: _ClassVar[int]
    VAL_B_FIELD_NUMBER: _ClassVar[int]
    VAL_F_FIELD_NUMBER: _ClassVar[int]
    action: Action
    val_b: bool
    val_f: float
    def __init__(self, action: _Optional[_Union[Action, str]] = ..., val_b: bool = ..., val_f: _Optional[float] = ...) -> None: ...

class Action(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = []
