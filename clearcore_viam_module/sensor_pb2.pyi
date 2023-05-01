from google.protobuf.internal import enum_type_wrapper as _enum_type_wrapper
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Optional as _Optional, Union as _Union

Battery: SensorType
Counter: SensorType
DESCRIPTOR: _descriptor.FileDescriptor
NoSensor: SensorType
Temperature: SensorType

class SensorRequest(_message.Message):
    __slots__ = ["sensor"]
    SENSOR_FIELD_NUMBER: _ClassVar[int]
    sensor: SensorType
    def __init__(self, sensor: _Optional[_Union[SensorType, str]] = ...) -> None: ...

class SensorResponse(_message.Message):
    __slots__ = ["value"]
    VALUE_FIELD_NUMBER: _ClassVar[int]
    value: float
    def __init__(self, value: _Optional[float] = ...) -> None: ...

class SensorType(int, metaclass=_enum_type_wrapper.EnumTypeWrapper):
    __slots__ = []
