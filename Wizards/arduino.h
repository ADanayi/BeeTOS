/*
 * بسم الله الرحمن الرحیم
 * اللهم صل علی محمد و آل محمد
 * ---------------------------
 * Created on Sun Sep 17 2023
 *
 * Copyright (c) 2023 Abolfazl Danayi
 * adanayidet@gmail.com
 */

#pragma once

#include <Arduino.h>

#include "../B.h"

namespace B
{
    namespace B_arduino
    {
        void __root_loop();
        void __root_setup();
        Program prg{millis, __root_setup, __root_loop, "BeeLinuxProgram"};
    };
};

void loop()
{
    B::B_arduino::prg.join();
}

void B::B_arduino::__root_setup()
{
}

#define loop B::B_arduino::__root_loop
