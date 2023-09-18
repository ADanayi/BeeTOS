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

#include "../Runnables/timeout.h"

namespace B
{
    namespace signallers
    {
        class Timeout : public B::runnables::Timeout
        {
        public:
            Timeout(unsigned long timeout_ms = 0, Core *core = nullptr) : B::runnables::Timeout(timeout_ms, nullptr, core)
            {
            }

            operator bool const()
            {
                if (__flag)
                {
                    __flag = false;
                    return true;
                }
                return false;
            }

        protected:
            virtual void _on_executed() override
            {
                __flag = true;
            }

            virtual void _on_restarted() override
            {
                __flag = false;
            }

            bool __flag;

        private:
        };
    };
};