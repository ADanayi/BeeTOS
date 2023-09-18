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
    namespace runnables
    {
        class Interval : public Timeout
        {
        public:
            explicit Interval(unsigned long int timeout_ms, void (*on_interval)(void), Core *core);
            void setInterval(unsigned long int timeout_ms)
            {
                this->_timeout_ms = timeout_ms;
            }

            void toggle()
            {
                if (this->finished())
                    return this->restart(-1);
                return this->cancel();
            }

        protected:
            virtual void _on_executed() override;
        };

        Interval::Interval(unsigned long int timeout_ms, void (*on_interval)(void), Core *core = nullptr) : Timeout{timeout_ms, on_interval, core}
        {
        }

        void Interval::_on_executed()
        {
            this->restart();
        }
    };
};