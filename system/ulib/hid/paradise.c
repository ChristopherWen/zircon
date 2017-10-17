// Copyright 2017 The Fuchsia Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <assert.h>
#include <hid/paradise.h>
#include <zircon/errors.h>
#include <stdio.h>
#include <string.h>

static const uint8_t paradise_touch_report_desc[] = {
    0x05, 0x0D,        // Usage Page (Digitizer)
    0x09, 0x04,        // Usage (Touch Screen)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x0C,        //   Report ID (12)
    0x95, 0x01,        //   Report Count (1)
    0x75, 0x08,        //   Report Size (8)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x15, 0x00,        //   Logical Minimum (0)
    0x81, 0x03,        //   Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x54,        //   Usage (0x54)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x09, 0x22,        //   Usage (Finger)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x42,        //     Usage (Tip Switch)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x47,        //     Usage (0x47)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //     Report Count (5)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x10,        //     Report Size (16)
    0x09, 0x51,        //     Usage (0x51)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x65, 0x11,        //     Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30,        //     Usage (X)
    0x26, 0x80, 0x28,  //     Logical Maximum (10368)
    0x35, 0x00,        //     Physical Minimum (0)
    0x46, 0x20, 0x0A,  //     Physical Maximum (2592)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0xC0, 0x06,  //     Physical Maximum (1728)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0x00, 0x1B,  //     Logical Maximum (6912)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x09, 0x22,        //   Usage (Finger)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x42,        //     Usage (Tip Switch)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x47,        //     Usage (0x47)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //     Report Count (5)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x10,        //     Report Size (16)
    0x09, 0x51,        //     Usage (0x51)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x65, 0x11,        //     Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30,        //     Usage (X)
    0x26, 0x80, 0x28,  //     Logical Maximum (10368)
    0x35, 0x00,        //     Physical Minimum (0)
    0x46, 0x20, 0x0A,  //     Physical Maximum (2592)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0xC0, 0x06,  //     Physical Maximum (1728)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0x00, 0x1B,  //     Logical Maximum (6912)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x09, 0x22,        //   Usage (Finger)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x42,        //     Usage (Tip Switch)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x47,        //     Usage (0x47)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //     Report Count (5)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x10,        //     Report Size (16)
    0x09, 0x51,        //     Usage (0x51)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x65, 0x11,        //     Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30,        //     Usage (X)
    0x26, 0x80, 0x28,  //     Logical Maximum (10368)
    0x35, 0x00,        //     Physical Minimum (0)
    0x46, 0x20, 0x0A,  //     Physical Maximum (2592)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0xC0, 0x06,  //     Physical Maximum (1728)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0x00, 0x1B,  //     Logical Maximum (6912)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x09, 0x22,        //   Usage (Finger)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x42,        //     Usage (Tip Switch)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x47,        //     Usage (0x47)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //     Report Count (5)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x10,        //     Report Size (16)
    0x09, 0x51,        //     Usage (0x51)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x65, 0x11,        //     Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30,        //     Usage (X)
    0x26, 0x80, 0x28,  //     Logical Maximum (10368)
    0x35, 0x00,        //     Physical Minimum (0)
    0x46, 0x20, 0x0A,  //     Physical Maximum (2592)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0xC0, 0x06,  //     Physical Maximum (1728)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0x00, 0x1B,  //     Logical Maximum (6912)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x09, 0x22,        //   Usage (Finger)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x42,        //     Usage (Tip Switch)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x75, 0x01,        //     Report Size (1)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x47,        //     Usage (0x47)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x05,        //     Report Count (5)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x75, 0x10,        //     Report Size (16)
    0x09, 0x51,        //     Usage (0x51)
    0x95, 0x01,        //     Report Count (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x01,        //     Report Count (1)
    0x55, 0x0E,        //     Unit Exponent (-2)
    0x65, 0x11,        //     Unit (System: SI Linear, Length: Centimeter)
    0x09, 0x30,        //     Usage (X)
    0x26, 0x80, 0x28,  //     Logical Maximum (10368)
    0x35, 0x00,        //     Physical Minimum (0)
    0x46, 0x20, 0x0A,  //     Physical Maximum (2592)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x46, 0xC0, 0x06,  //     Physical Maximum (1728)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0x00, 0x1B,  //     Logical Maximum (6912)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x05, 0x0D,        //   Usage Page (Digitizer)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //   Logical Maximum (65534)
    0x75, 0x10,        //   Report Size (16)
    0x95, 0x01,        //   Report Count (1)
    0x09, 0x56,        //   Usage (0x56)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x0C,        //   Report ID (12)
    0x09, 0x55,        //   Usage (0x55)
    0x75, 0x08,        //   Report Size (8)
    0x95, 0x01,        //   Report Count (1)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0A,        //   Report ID (10)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x09, 0xC5,        //   Usage (0xC5)
    0x96, 0x00, 0x01,  //   Report Count (256)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection
    0x06, 0x11, 0xFF,  // Usage Page (Vendor Defined 0xFF11)
    0x09, 0x11,        // Usage (0x11)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x03,        //   Report ID (3)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x00,        //     Usage (0x00)
    0x75, 0x08,        //     Report Size (8)
    0x15, 0x00,        //     Logical Minimum (0)
    0x26, 0xFF, 0x00,  //     Logical Maximum (255)
    0x95, 0x27,        //     Report Count (39)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0x85, 0x02,        //   Report ID (2)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x01,        //   Report Count (1)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x03,        //   Report ID (3)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x3F,        //   Report Count (63)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x04,        //   Report ID (4)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x0F,        //   Report Count (15)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x07,        //   Report ID (7)
    0x09, 0x00,        //   Usage (0x00)
    0x96, 0x00, 0x01,  //   Report Count (256)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x08,        //   Report ID (8)
    0x09, 0x00,        //   Usage (0x00)
    0x96, 0x87, 0x00,  //   Report Count (135)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x09,        //   Report ID (9)
    0x09, 0x00,        //   Usage (0x00)
    0x96, 0x3F, 0x00,  //   Report Count (63)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0D,        //   Report ID (13)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x07,        //   Report Count (7)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection
    0x05, 0x0D,        // Usage Page (Digitizer)
    0x09, 0x0E,        // Usage (0x0E)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x0E,        //   Report ID (14)
    0x09, 0x23,        //   Usage (0x23)
    0xA1, 0x02,        //   Collection (Logical)
    0x09, 0x52,        //     Usage (0x52)
    0x09, 0x53,        //     Usage (0x53)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x0A,        //     Logical Maximum (10)
    0x75, 0x08,        //     Report Size (8)
    0x95, 0x02,        //     Report Count (2)
    0xB1, 0x02,        //     Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              //   End Collection
    0xC0,              // End Collection
    0x05, 0x0D,        // Usage Page (Digitizer)
    0x09, 0x02,        // Usage (Pen)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x06,        //   Report ID (6)
    0xA4,              //   Push
    0x09, 0x20,        //     Usage (Stylus)
    0xA1, 0x00,        //     Collection (Physical)
    0x09, 0x42,        //       Usage (Tip Switch)
    0x09, 0x44,        //       Usage (Barrel Switch)
    0x09, 0x45,        //       Usage (Eraser)
    0x09, 0x3C,        //       Usage (Invert)
    0x09, 0x5A,        //       Usage (0x5A)
    0x09, 0x32,        //       Usage (In Range)
    0x15, 0x00,        //       Logical Minimum (0)
    0x25, 0x01,        //       Logical Maximum (1)
    0x75, 0x01,        //       Report Size (1)
    0x95, 0x06,        //       Report Count (6)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x02,        //       Report Count (2)
    0x81, 0x03,        //       Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //       Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,        //       Usage (X)
    0x27, 0x40, 0x65, 0x00, 0x00,  //       Logical Maximum (25919)
    0x47, 0x40, 0x65, 0x00, 0x00,  //       Physical Maximum (25919)
    0x65, 0x11,        //       Unit (System: SI Linear, Length: Centimeter)
    0x55, 0x0D,        //       Unit Exponent (-3)
    0x75, 0x10,        //       Report Size (16)
    0x95, 0x01,        //       Report Count (1)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x31,        //       Usage (Y)
    0x27, 0x80, 0x43, 0x00, 0x00,  //       Logical Maximum (17279)
    0x47, 0x80, 0x43, 0x00, 0x00,  //       Physical Maximum (17279)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x45, 0x00,        //       Physical Maximum (0)
    0x65, 0x00,        //       Unit (None)
    0x55, 0x00,        //       Unit Exponent (0)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x30,        //       Usage (Tip Pressure)
    0x26, 0xFF, 0x07,  //       Logical Maximum (2047)
    0x75, 0x10,        //       Report Size (16)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //       Usage Page (Vendor Defined 0xFF00)
    0x09, 0x5B,        //       Usage (0x5B)
    0x16, 0x00, 0x80,  //       Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //       Logical Maximum (32767)
    0x75, 0x10,        //       Report Size (16)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x5B,        //       Usage (0x5B)
    0x17, 0x00, 0x00, 0x00, 0x80,  //       Logical Minimum (-2147483649)
    0x27, 0xFF, 0xFF, 0xFF, 0x7F,  //       Logical Maximum (2147483646)
    0x75, 0x20,        //       Report Size (32)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //       Usage Page (Vendor Defined 0xFF00)
    0x09, 0x00,        //       Usage (0x00)
    0x75, 0x08,        //       Report Size (8)
    0x26, 0xFF, 0x00,  //       Logical Maximum (255)
    0x15, 0x00,        //       Logical Minimum (0)
    0x81, 0x02,        //       Input (DVar,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x3B,        //       Usage (Battery Strength)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x65, 0x14,        //       Unit (System: English Rotation, Length: Centimeter)
    0x55, 0x00,        //       Unit Exponent (0)
    0x16, 0xA6, 0xFF,  //       Logical Minimum (-90)
    0x26, 0x5A, 0x00,  //       Logical Maximum (90)
    0x36, 0xA6, 0xFF,  //       Physical Minimum (-90)
    0x46, 0x5A, 0x00,  //       Physical Maximum (90)
    0x75, 0x08,        //       Report Size (8)
    0x09, 0x3D,        //       Usage (X Tilt)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x3E,        //       Usage (Y Tilt)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x15, 0x00,        //       Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //       Logical Maximum (65534)
    0x35, 0x00,        //       Physical Minimum (0)
    0x47, 0xFF, 0xFF, 0x00, 0x00,  //       Physical Maximum (65534)
    0x66, 0x01, 0x10,  //       Unit (System: SI Linear, Time: Seconds)
    0x55, 0x0C,        //       Unit Exponent (-4)
    0x75, 0x10,        //       Report Size (16)
    0x09, 0x56,        //       Usage (0x56)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //     End Collection
    0xB4,              //   Pop
    0x85, 0x13,        //   Report ID (19)
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x09, 0xC5,        //   Usage (0xC5)
    0x96, 0x00, 0x01,  //   Report Count (256)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection
    0x06, 0x11, 0xFF,  // Usage Page (Vendor Defined 0xFF11)
    0x09, 0x02,        // Usage (0x02)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x0B,        //   Report ID (11)
    0xA4,              //   Push
    0x09, 0x20,        //     Usage (0x20)
    0xA1, 0x00,        //     Collection (Physical)
    0x09, 0x42,        //       Usage (0x42)
    0x09, 0x44,        //       Usage (0x44)
    0x09, 0x45,        //       Usage (0x45)
    0x09, 0x3C,        //       Usage (0x3C)
    0x09, 0x5A,        //       Usage (0x5A)
    0x09, 0x32,        //       Usage (0x32)
    0x15, 0x00,        //       Logical Minimum (0)
    0x25, 0x01,        //       Logical Maximum (1)
    0x75, 0x01,        //       Report Size (1)
    0x95, 0x06,        //       Report Count (6)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x02,        //       Report Count (2)
    0x81, 0x03,        //       Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //       Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,        //       Usage (X)
    0x27, 0x40, 0x65, 0x00, 0x00,  //       Logical Maximum (25919)
    0x47, 0x40, 0x65, 0x00, 0x00,  //       Physical Maximum (25919)
    0x65, 0x11,        //       Unit (System: SI Linear, Length: Centimeter)
    0x55, 0x0D,        //       Unit Exponent (-3)
    0x75, 0x10,        //       Report Size (16)
    0x95, 0x01,        //       Report Count (1)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x31,        //       Usage (Y)
    0x27, 0x80, 0x43, 0x00, 0x00,  //       Logical Maximum (17279)
    0x47, 0x80, 0x43, 0x00, 0x00,  //       Physical Maximum (17279)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x45, 0x00,        //       Physical Maximum (0)
    0x65, 0x00,        //       Unit (None)
    0x55, 0x00,        //       Unit Exponent (0)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x30,        //       Usage (Tip Pressure)
    0x26, 0xFF, 0x07,  //       Logical Maximum (2047)
    0x75, 0x10,        //       Report Size (16)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //       Usage Page (Vendor Defined 0xFF00)
    0x09, 0x5B,        //       Usage (0x5B)
    0x16, 0x00, 0x80,  //       Logical Minimum (-32768)
    0x26, 0xFF, 0x7F,  //       Logical Maximum (32767)
    0x75, 0x10,        //       Report Size (16)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x5B,        //       Usage (0x5B)
    0x17, 0x00, 0x00, 0x00, 0x80,  //       Logical Minimum (-2147483649)
    0x27, 0xFF, 0xFF, 0xFF, 0x7F,  //       Logical Maximum (2147483646)
    0x75, 0x20,        //       Report Size (32)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x06, 0x00, 0xFF,  //       Usage Page (Vendor Defined 0xFF00)
    0x09, 0x00,        //       Usage (0x00)
    0x75, 0x08,        //       Report Size (8)
    0x26, 0xFF, 0x00,  //       Logical Maximum (255)
    0x15, 0x00,        //       Logical Minimum (0)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x0D,        //       Usage Page (Digitizer)
    0x09, 0x3B,        //       Usage (Battery Strength)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x65, 0x14,        //       Unit (System: English Rotation, Length: Centimeter)
    0x55, 0x00,        //       Unit Exponent (0)
    0x16, 0xA6, 0xFF,  //       Logical Minimum (-90)
    0x26, 0x5A, 0x00,  //       Logical Maximum (90)
    0x36, 0xA6, 0xFF,  //       Physical Minimum (-90)
    0x46, 0x5A, 0x00,  //       Physical Maximum (90)
    0x75, 0x08,        //       Report Size (8)
    0x09, 0x3D,        //       Usage (X Tilt)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x09, 0x3E,        //       Usage (Y Tilt)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x15, 0x00,        //       Logical Minimum (0)
    0x27, 0xFF, 0xFF, 0x00, 0x00,  //       Logical Maximum (65534)
    0x35, 0x00,        //       Physical Minimum (0)
    0x47, 0xFF, 0xFF, 0x00, 0x00,  //       Physical Maximum (65534)
    0x66, 0x01, 0x10,  //       Unit (System: SI Linear, Time: Seconds)
    0x55, 0x0C,        //       Unit Exponent (-4)
    0x75, 0x10,        //       Report Size (16)
    0x09, 0x56,        //       Usage (0x56)
    0x81, 0x02,        //       Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //     End Collection
    0xB4,              //   Pop
    0x06, 0x00, 0xFF,  //   Usage Page (Vendor Defined 0xFF00)
    0x75, 0x08,        //   Report Size (8)
    0x15, 0x00,        //   Logical Minimum (0)
    0x26, 0xFF, 0x00,  //   Logical Maximum (255)
    0x85, 0x05,        //   Report ID (5)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x3A,        //   Report Count (58)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x10,        //   Report ID (16)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x14,        //   Report Count (20)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x0F,        //   Report ID (15)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x27,        //   Report Count (39)
    0x81, 0x02,        //   Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x85, 0x0F,        //   Report ID (15)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x07,        //   Report Count (7)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x11,        //   Report ID (17)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x09,        //   Report Count (9)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x05,        //   Report ID (5)
    0x09, 0x00,        //   Usage (0x00)
    0x95, 0x08,        //   Report Count (8)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x10,        //   Report ID (16)
    0x09, 0x00,        //   Usage (0x00)
    0x96, 0x3F, 0x00,  //   Report Count (63)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0x85, 0x0B,        //   Report ID (11)
    0x09, 0x00,        //   Usage (0x00)
    0x96, 0x3F, 0x00,  //   Report Count (63)
    0xB1, 0x02,        //   Feature (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position,Non-volatile)
    0xC0,              // End Collection
    0x05, 0x01,        // Usage Page (Generic Desktop Ctrls)
    0x09, 0x02,        // Usage (Mouse)
    0xA1, 0x01,        // Collection (Application)
    0x85, 0x01,        //   Report ID (1)
    0x09, 0x01,        //   Usage (Pointer)
    0xA1, 0x00,        //   Collection (Physical)
    0x05, 0x09,        //     Usage Page (Button)
    0x19, 0x01,        //     Usage Minimum (0x01)
    0x29, 0x02,        //     Usage Maximum (0x02)
    0x15, 0x00,        //     Logical Minimum (0)
    0x25, 0x01,        //     Logical Maximum (1)
    0x95, 0x02,        //     Report Count (2)
    0x75, 0x01,        //     Report Size (1)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x95, 0x01,        //     Report Count (1)
    0x75, 0x06,        //     Report Size (6)
    0x81, 0x03,        //     Input (Const,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0x05, 0x01,        //     Usage Page (Generic Desktop Ctrls)
    0x09, 0x30,        //     Usage (X)
    0x09, 0x31,        //     Usage (Y)
    0x26, 0xFF, 0x7F,  //     Logical Maximum (32767)
    0x75, 0x10,        //     Report Size (16)
    0x95, 0x02,        //     Report Count (2)
    0x81, 0x02,        //     Input (Data,Var,Abs,No Wrap,Linear,Preferred State,No Null Position)
    0xC0,              //   End Collection
    0xC0,              // End Collection

    // 1064 bytes
};

bool is_paradise_touch_report_desc(const uint8_t* data, size_t len) {
    if (!data)
        return false;

    if (len != sizeof(paradise_touch_report_desc)) {
        return false;
    }

    return (memcmp(data, paradise_touch_report_desc, len) == 0);
}

zx_status_t setup_paradise_touch(int fd) {
    if (fd < 0)
        return ZX_ERR_INVALID_ARGS;

    return ZX_OK;
}

static const uint8_t paradise_touchpad_report_desc[] = {
    0x05, 0x0D,         /*  Usage Page (Digitizer),             */
    0x09, 0x05,         /*  Usage (Touchpad),                   */
    0xA1, 0x01,         /*  Collection (Application),           */
    0x85, 0x01,         /*      Report ID (1),                  */
    0x05, 0x09,         /*      Usage Page (Button),            */
    0x19, 0x01,         /*      Usage Minimum (01h),            */
    0x29, 0x01,         /*      Usage Maximum (01h),            */
    0x15, 0x00,         /*      Logical Minimum (0),            */
    0x25, 0x01,         /*      Logical Maximum (1),            */
    0x75, 0x01,         /*      Report Size (1),                */
    0x95, 0x01,         /*      Report Count (1),               */
    0x81, 0x02,         /*      Input (Variable),               */
    0x05, 0x0D,         /*      Usage Page (Digitizer),         */
    0x09, 0x54,         /*      Usage (Contact Count),          */
    0x75, 0x07,         /*      Report Size (7),                */
    0x95, 0x01,         /*      Report Count (1),               */
    0x81, 0x02,         /*      Input (Variable),               */
    0x09, 0x22,         /*      Usage (Finger),                 */
    0xA1, 0x02,         /*      Collection (Logical),           */
    0x09, 0x42,         /*          Usage (Tip Switch),         */
    0x15, 0x00,         /*          Logical Minimum (0),        */
    0x25, 0x01,         /*          Logical Maximum (1),        */
    0x75, 0x01,         /*          Report Size (1),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x32,         /*          Usage (In Range),           */
    0x75, 0x07,         /*          Report Size (7),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x51,         /*          Usage (Contact Identifier), */
    0x26, 0xFF, 0x7F,   /*          Logical Maximum (32767),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x01,         /*          Usage Page (Desktop),       */
    0x09, 0x30,         /*          Usage (X),                  */
    0x55, 0x0E,         /*          Unit Exponent (14),         */
    0x65, 0x11,         /*          Unit (Centimeter),          */
    0x35, 0x00,         /*          Physical Minimum (0),       */
    0x46, 0x06, 0x04,   /*          Physical Maximum (1030),    */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x31,         /*          Usage (Y),                  */
    0x46, 0xA8, 0x02,   /*          Physical Maximum (680),     */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x0D,         /*          Usage Page (Digitizer),     */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x09, 0x48,         /*          Usage (Width),              */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x09, 0x49,         /*          Usage (Height),             */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x30,         /*          Usage (Tip Pressure),       */
    0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
    0x75, 0x08,         /*          Report Size (8),            */
    0x81, 0x02,         /*          Input (Variable),           */
    0xC0,               /*      End Collection,                 */
    0x09, 0x22,         /*      Usage (Finger),                 */
    0xA1, 0x02,         /*      Collection (Logical),           */
    0x09, 0x42,         /*          Usage (Tip Switch),         */
    0x15, 0x00,         /*          Logical Minimum (0),        */
    0x25, 0x01,         /*          Logical Maximum (1),        */
    0x75, 0x01,         /*          Report Size (1),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x32,         /*          Usage (In Range),           */
    0x75, 0x07,         /*          Report Size (7),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x51,         /*          Usage (Contact Identifier), */
    0x26, 0xFF, 0x7F,   /*          Logical Maximum (32767),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x01,         /*          Usage Page (Desktop),       */
    0x09, 0x30,         /*          Usage (X),                  */
    0x55, 0x0E,         /*          Unit Exponent (14),         */
    0x65, 0x11,         /*          Unit (Centimeter),          */
    0x35, 0x00,         /*          Physical Minimum (0),       */
    0x46, 0x06, 0x04,   /*          Physical Maximum (1030),    */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x31,         /*          Usage (Y),                  */
    0x46, 0xA8, 0x02,   /*          Physical Maximum (680),     */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x0D,         /*          Usage Page (Digitizer),     */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x09, 0x48,         /*          Usage (Width),              */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x09, 0x49,         /*          Usage (Height),             */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x30,         /*          Usage (Tip Pressure),       */
    0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
    0x75, 0x08,         /*          Report Size (8),            */
    0x81, 0x02,         /*          Input (Variable),           */
    0xC0,               /*      End Collection,                 */
    0x09, 0x22,         /*      Usage (Finger),                 */
    0xA1, 0x02,         /*      Collection (Logical),           */
    0x09, 0x42,         /*          Usage (Tip Switch),         */
    0x15, 0x00,         /*          Logical Minimum (0),        */
    0x25, 0x01,         /*          Logical Maximum (1),        */
    0x75, 0x01,         /*          Report Size (1),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x32,         /*          Usage (In Range),           */
    0x75, 0x07,         /*          Report Size (7),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x51,         /*          Usage (Contact Identifier), */
    0x26, 0xFF, 0x7F,   /*          Logical Maximum (32767),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x01,         /*          Usage Page (Desktop),       */
    0x09, 0x30,         /*          Usage (X),                  */
    0x55, 0x0E,         /*          Unit Exponent (14),         */
    0x65, 0x11,         /*          Unit (Centimeter),          */
    0x35, 0x00,         /*          Physical Minimum (0),       */
    0x46, 0x06, 0x04,   /*          Physical Maximum (1030),    */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x31,         /*          Usage (Y),                  */
    0x46, 0xA8, 0x02,   /*          Physical Maximum (680),     */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x0D,         /*          Usage Page (Digitizer),     */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x09, 0x48,         /*          Usage (Width),              */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x09, 0x49,         /*          Usage (Height),             */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x30,         /*          Usage (Tip Pressure),       */
    0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
    0x75, 0x08,         /*          Report Size (8),            */
    0x81, 0x02,         /*          Input (Variable),           */
    0xC0,               /*      End Collection,                 */
    0x09, 0x22,         /*      Usage (Finger),                 */
    0xA1, 0x02,         /*      Collection (Logical),           */
    0x09, 0x42,         /*          Usage (Tip Switch),         */
    0x15, 0x00,         /*          Logical Minimum (0),        */
    0x25, 0x01,         /*          Logical Maximum (1),        */
    0x75, 0x01,         /*          Report Size (1),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x32,         /*          Usage (In Range),           */
    0x75, 0x07,         /*          Report Size (7),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x51,         /*          Usage (Contact Identifier), */
    0x26, 0xFF, 0x7F,   /*          Logical Maximum (32767),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x01,         /*          Usage Page (Desktop),       */
    0x09, 0x30,         /*          Usage (X),                  */
    0x55, 0x0E,         /*          Unit Exponent (14),         */
    0x65, 0x11,         /*          Unit (Centimeter),          */
    0x35, 0x00,         /*          Physical Minimum (0),       */
    0x46, 0x06, 0x04,   /*          Physical Maximum (1030),    */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x31,         /*          Usage (Y),                  */
    0x46, 0xA8, 0x02,   /*          Physical Maximum (680),     */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x0D,         /*          Usage Page (Digitizer),     */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x09, 0x48,         /*          Usage (Width),              */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x09, 0x49,         /*          Usage (Height),             */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x30,         /*          Usage (Tip Pressure),       */
    0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
    0x75, 0x08,         /*          Report Size (8),            */
    0x81, 0x02,         /*          Input (Variable),           */
    0xC0,               /*      End Collection,                 */
    0x09, 0x22,         /*      Usage (Finger),                 */
    0xA1, 0x02,         /*      Collection (Logical),           */
    0x09, 0x42,         /*          Usage (Tip Switch),         */
    0x15, 0x00,         /*          Logical Minimum (0),        */
    0x25, 0x01,         /*          Logical Maximum (1),        */
    0x75, 0x01,         /*          Report Size (1),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x32,         /*          Usage (In Range),           */
    0x75, 0x07,         /*          Report Size (7),            */
    0x95, 0x01,         /*          Report Count (1),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x51,         /*          Usage (Contact Identifier), */
    0x26, 0xFF, 0x7F,   /*          Logical Maximum (32767),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x01,         /*          Usage Page (Desktop),       */
    0x09, 0x30,         /*          Usage (X),                  */
    0x55, 0x0E,         /*          Unit Exponent (14),         */
    0x65, 0x11,         /*          Unit (Centimeter),          */
    0x35, 0x00,         /*          Physical Minimum (0),       */
    0x46, 0x06, 0x04,   /*          Physical Maximum (1030),    */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x31,         /*          Usage (Y),                  */
    0x46, 0xA8, 0x02,   /*          Physical Maximum (680),     */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x81, 0x02,         /*          Input (Variable),           */
    0x05, 0x0D,         /*          Usage Page (Digitizer),     */
    0x26, 0x80, 0x33,   /*          Logical Maximum (13184),    */
    0x09, 0x48,         /*          Usage (Width),              */
    0x75, 0x10,         /*          Report Size (16),           */
    0x81, 0x02,         /*          Input (Variable),           */
    0x26, 0x00, 0x22,   /*          Logical Maximum (8704),     */
    0x09, 0x49,         /*          Usage (Height),             */
    0x81, 0x02,         /*          Input (Variable),           */
    0x09, 0x30,         /*          Usage (Tip Pressure),       */
    0x26, 0xFF, 0x00,   /*          Logical Maximum (255),      */
    0x75, 0x08,         /*          Report Size (8),            */
    0x81, 0x02,         /*          Input (Variable),           */
    0xC0,               /*      End Collection,                 */
    0xC0                /*  End Collection                      */
};

bool is_paradise_touchpad_report_desc(const uint8_t* data, size_t len) {
    static_assert(sizeof(paradise_touchpad_t) == 62, "hid struct not packed");

    if (!data)
        return false;

    if (len != sizeof(paradise_touchpad_report_desc)) {
        return false;
    }

    return (memcmp(data, paradise_touchpad_report_desc, len) == 0);
}

zx_status_t setup_paradise_touchpad(int fd) {
    if (fd < 0)
        return ZX_ERR_INVALID_ARGS;

    return ZX_OK;
}
