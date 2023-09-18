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

#include "../Core/types.h"
#include "../Core/core_cls.h"

namespace B
{
    namespace runnables
    {
        class Timeout
        {
            friend class B::Core;

        public:
            explicit Timeout(unsigned long timeout_ms, void (*const on_timeout)(void), Core *core = nullptr);

            Timeout(Timeout &) = delete;
            Timeout(Timeout &&) = delete;

            ~Timeout();

            RunStateT state();
            void restart(unsigned long timeout_ms = -1);
            void cancel();
            bool scheduled();
            bool finished();
            virtual void toggle();
            // void delay(unsigned long ms);

            operator bool() const;

        protected:
            unsigned long _timeout_ms;
            unsigned long _tic_ms;
            unsigned long _delay_tic_ms;
            unsigned long _delay_timeout_ms;
            Core *_core;
            void (*const _on_timeout)(void);

            static Timeout *_first();
            static Timeout *_last();
            Timeout *_next();
            Timeout *_prev();

            virtual void _on_executing(){};
            virtual void _on_executed(){};
            virtual void _on_restarted(){};

        private:
            static Timeout *__first;
            static Timeout *__last;
            Timeout *__next;
            Timeout *__prev;
            RunStateT __state;
        };
    };
};
