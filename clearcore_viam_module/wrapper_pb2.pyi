import motor_pb2 as _motor_pb2
import sensor_pb2 as _sensor_pb2
import error_pb2 as _error_pb2
from google.protobuf import descriptor as _descriptor
from google.protobuf import message as _message
from typing import ClassVar as _ClassVar, Mapping as _Mapping, Optional as _Optional, Union as _Union

DESCRIPTOR: _descriptor.FileDescriptor

class WrappedRequest(_message.Message):
    __slots__ = ["motorRequest", "sensorRequest"]
    MOTORREQUEST_FIELD_NUMBER: _ClassVar[int]
    SENSORREQUEST_FIELD_NUMBER: _ClassVar[int]
    motorRequest: _motor_pb2.MotorRequest
    sensorRequest: _sensor_pb2.SensorRequest
    def __init__(self, sensorRequest: _Optional[_Union[_sensor_pb2.SensorRequest, _Mapping]] = ..., motorRequest: _Optional[_Union[_motor_pb2.MotorRequest, _Mapping]] = ...) -> None: ...

class WrappedResponse(_message.Message):
    __slots__ = ["errorResponse", "motorResponse", "sensorResponse", "status"]
    ERRORRESPONSE_FIELD_NUMBER: _ClassVar[int]
    MOTORRESPONSE_FIELD_NUMBER: _ClassVar[int]
    SENSORRESPONSE_FIELD_NUMBER: _ClassVar[int]
    STATUS_FIELD_NUMBER: _ClassVar[int]
    errorResponse: _error_pb2.ErrorResponse
    motorResponse: _motor_pb2.MotorResponse
    sensorResponse: _sensor_pb2.SensorResponse
    status: bool
    def __init__(self, status: bool = ..., sensorResponse: _Optional[_Union[_sensor_pb2.SensorResponse, _Mapping]] = ..., motorResponse: _Optional[_Union[_motor_pb2.MotorResponse, _Mapping]] = ..., errorResponse: _Optional[_Union[_error_pb2.ErrorResponse, _Mapping]] = ...) -> None: ...
