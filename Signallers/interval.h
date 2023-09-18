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

#include "timeout.h"

namespace B
{
    namespace signallers
    {
        class Interval : public Timeout
        {
        public:
            Interval(unsigned long int interval, Core *core = nullptr) : Timeout{interval, core} {}

        protected:
            virtual void _on_executed() override
            {
                Timeout::_on_executed();
                restart(-1);
                __flag = true;
            }
        };
    };
};