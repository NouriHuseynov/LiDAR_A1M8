/*
 *  RPLIDAR SDK
 *
 *  Copyright (c) 2009 - 2014 RoboPeak Team
 *  http://www.robopeak.com
 *  Copyright (c) 2014 - 2019 Shanghai Slamtec Co., Ltd.
 *  http://www.slamtec.com
 *
 */
/*
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

#include "main.h"

// Commands
//-----------------------------------------

// Commands without payload and response
#define RPLIDAR_CMD_STOP               0x25
#define RPLIDAR_CMD_SCAN               0x20
#define RPLIDAR_CMD_FORCE_SCAN         0x21
#define RPLIDAR_CMD_RESET              0x40


// Commands without payload but have response
#define RPLIDAR_CMD_GET_DEVICE_INFO    0x50
#define RPLIDAR_CMD_GET_DEVICE_HEALTH  0x52

#define RPLIDAR_CMD_GET_SAMPLERATE     0x59 //added in fw 1.17

// Commands with payload and have response
#define RPLIDAR_CMD_EXPRESS_SCAN       0x82 //added in fw 1.17

// Payloads
// ------------------------------------------
typedef struct _rplidar_payload_express_scan_t {
    uint8_t   working_mode;
    uint16_t  working_flags;
    uint16_t  param;
} __attribute__((packed)) rplidar_payload_express_scan_t;

#if defined(_WIN32)
#pragma pack()
#endif
