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


namespace {
    constexpr int baud_rate = 115200;
    constexpr size_t buffer_size = 60;
    //std::array<const MotorDriver*,4> motors = {&ConnectorM0,&ConnectorM1,&ConnectorM2,&ConnectorM3};
    const Connector* output_LEDs[6] = {
            &ConnectorIO0, &ConnectorIO1, &ConnectorIO2, &ConnectorIO3, &ConnectorIO4, &ConnectorIO5
    };
    std::uint8_t input[buffer_size+1];
}

namespace viam{
    auto setup() -> void {
        ConnectorUsb.Mode(Connector::USB_CDC);
        ConnectorUsb.Speed(baud_rate);
        ConnectorUsb.PortOpen();
    }

    auto reset_buffer() -> void {
        for(auto& i : input){
            i = (char)NULL;
        }
    }

    auto serial_read() -> void {
        auto i = 0u;
        while(i < buffer_size && ConnectorUsb.CharPeek() != -1) {
            input[i] = (std::uint8_t)ConnectorUsb.CharGet();
            i++;
            Delay_ms(1);
        }
    }

    void cycle(){
        WrappedRequest request = WrappedRequest_init_zero;
        WrappedResponse response = WrappedResponse_init_zero;
        SensorRequest sensor_request;
        MotorRequest motor_request;
        serial_read();
        std::uint8_t return_message[buffer_size];
        auto request_stream = pb_istream_from_buffer(input, buffer_size);
        auto response_stream = pb_ostream_from_buffer(return_message, sizeof(return_message));
        if(!pb_decode(&request_stream, WrappedRequest_fields, &request)){
            //TODO: Handle Error
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
                    //TODO: Error handling
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
                        ConnectorLed.State(true);
                        break;
                    case Action_GoFor:
                        ConnectorLed.State(false);
                        break;
                    case Action_GoTo:
                        ConnectorLed.State(true);
                        break;
                    case Action_ResetZeroPosition:
                        ConnectorLed.State(false);
                        break;
                    case Action_GetPosition:
                        ConnectorLed.State(true);
                        break;
                    case Action_Stop:
                        ConnectorLed.State(false);
                        break;
                    case Action_IsPowered:
                        ConnectorLed.State(true);
                        break;
                    case Action_IsMoving:
                        ConnectorLed.State(false);
                        break;
                    default:
                        ConnectorLed.State(false);
                        //TODO: Error handling
                }
        }
        if(!pb_encode(&response_stream, WrappedResponse_fields, &response)){
            //TODO: Error Handling
        }

        ConnectorUsb.Send(reinterpret_cast<const char *>(return_message), sizeof(return_message));

    }
}

