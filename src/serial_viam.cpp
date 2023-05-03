//
// Created by Jorge Guerra on 4/25/23.
//

#include "serial_viam.hpp"
#include <ClearCore.h>
#include <array>
#include <pb.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include <sensor.pb.h>
#include <motor.pb.h>
#include <wrapper.pb.h>
#include <cstdint>
#include <array>
#include <optional>


namespace {
    constexpr int baud_rate = 115200;
    constexpr size_t buffer_size = 60;
    //std::array<const MotorDriver*,4> motors = {&ConnectorM0,&ConnectorM1,&ConnectorM2,&ConnectorM3};
    Connector* output_LEDs[6] = {
            &ConnectorIO0, &ConnectorIO1, &ConnectorIO2, &ConnectorIO3, &ConnectorIO4, &ConnectorIO5
    };
    // std::uint8_t input[buffer_size+1];
    bool is_powered = false;
    bool is_moving = false;
    float current_power = 0.0;
    float current_position = 0.0;
}

namespace viam{
    auto setup() -> void {
        ConnectorUsb.Mode(Connector::USB_CDC);
        ConnectorUsb.Speed(baud_rate);
        ConnectorUsb.PortOpen();
    }


    auto read_buffer() -> std::optional<std::array<std::uint8_t, buffer_size>>
    {
        if(ConnectorUsb.CharPeek() == -1){
            return {};
        }
        std::array<std::uint8_t, buffer_size> input{};
        for(auto& i:input){
            if(ConnectorUsb.CharPeek() == -1){
                break;
            }
            i = static_cast<std::uint8_t>(ConnectorUsb.CharGet());
        }
        return input;
    }

    void Error_Handler(int led){
        output_LEDs[led]->State(true);
    }



    void cycle(){
        WrappedRequest request = WrappedRequest_init_zero;
        WrappedResponse response = WrappedResponse_init_zero;
        SensorRequest sensor_request;
        MotorRequest motor_request;
        std::uint8_t return_message[buffer_size];
        auto input = read_buffer();
        if(input.has_value()){
            auto request_stream = pb_istream_from_buffer(input.value().data(), input.value().size());
            auto status = pb_decode(&request_stream, WrappedRequest_fields, &request);
            auto response_stream = pb_ostream_from_buffer(return_message, sizeof(return_message));
            if(!status){
                Error_Handler(0);
            }
            switch (request.which_msg){
                case WrappedRequest_sensorRequest_tag:
                    sensor_request = request.msg.sensorRequest;
                    if(sensor_request.sensor == SensorType_Temperature){
                        response.msg.sensorResponse.value = 1000;
                        response.status = true;
                    }else if (sensor_request.sensor == SensorType_Battery) {
                        response.msg.sensorResponse.value = 2000;
                        response.status = true;
                    }else if (sensor_request.sensor == SensorType_Counter) {
                        response.msg.sensorResponse.value = 3000;
                        response.status = true;
                    }else{
                        Error_Handler(1);
                    }
                    break;
                case WrappedRequest_motorRequest_tag:
                    motor_request = request.msg.motorRequest;
                    response.which_msg = WrappedResponse_motorResponse_tag;
                    response.msg.motorResponse.action = motor_request.action;
                    switch(motor_request.action){
                        case Action_NoAction:
                            break;
                        case Action_SetPower:
                            if (motor_request.has_power) {
                                if (motor_request.power == 0.0) {
                                    is_moving = false;
                                    is_powered = false;
                                } else {
                                    is_moving = true;
                                    is_powered = true;
                                }
                                current_power = motor_request.power;
                                response.msg.motorResponse.has_val_f = true;
                                response.msg.motorResponse.val_f = current_power;
                                response.status = true;
                            } else {
                                Error_Handler(2);
                            }
                        case Action_GoFor:
                            response.status = true;
                            break;
                        case Action_GoTo:
                            response.status = true;
                            break;
                        case Action_ResetZeroPosition:
                            response.status = true;
                            break;
                        case Action_GetPosition:
                            response.msg.motorResponse.has_val_f = true;
                            response.msg.motorResponse.val_f = current_position;
                            response.status = true;
                            break;
                        case Action_Stop:
                            response.status = true;
                            break;
                        case Action_IsPowered:
                            response.msg.motorResponse.has_val_b = true;
                            response.msg.motorResponse.has_val_f = true;
                            response.msg.motorResponse.val_b = is_powered;
                            response.msg.motorResponse.val_f = current_power;
                            response.status = true;
                            break;
                        case Action_IsMoving:
                            response.msg.motorResponse.has_val_b = true;
                            response.msg.motorResponse.val_b = is_moving;
                            response.status = true;
                            break;
                        default:
                            Error_Handler(3);
                    }
            }
            if(!pb_encode(&response_stream, WrappedResponse_fields, &response)){
                //TODO: Error Handling
                Error_Handler(4);
            }
            ConnectorUsb.Send(reinterpret_cast<const char *>(return_message), response_stream.bytes_written);
        }
    }
}

