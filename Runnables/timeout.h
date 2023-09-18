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
#include "../Core/core.h"
#include "timeout_cls.h"

namespace B
{
    namespace runnables
    {
        Timeout::Timeout(unsigned long timeout_ms, void (*const on_timeout)(void), Core *core) : _on_timeout{on_timeout}
        {
            _core = (core == nullptr) ? Core::active_core() : core;

            _timeout_ms = timeout_ms;
            __next = nullptr;

            if (__first == nullptr)
            {
                __prev = nullptr;
                __first = this;
            }
            else
            {
                __prev = __last;
                __last->__next = this;
            }
            __last = this;
            restart();
        }

        RunStateT Timeout::state()
        {
            return __state;
        }

        Timeout::~Timeout()
        {
            if (this == Timeout::__first)
            {
                if (this == Timeout::__last)
                {
                    Timeout::__first = nullptr;
                    Timeout::__last = nullptr;
                }
                else
                {
                    Timeout::__first = this->__next;
                    Timeout::__first->__prev = nullptr;
                }
                return;
            }

            if (this == Timeout::__last)
            {
                Timeout::__last = this->__prev;
                Timeout::__last->__next = nullptr;
                return;
            }

            Timeout *p = this->__prev;
            Timeout *n = this->__next;
            p->__next = n;
            n->__prev = p;
        }

        // void Timeout::delay(unsigned long ms)
        // {
        //     if (_core == nullptr)
        //         return;
        //     if (__state != RunStateT::executing)
        //         return;
        //     _core->delay(ms);
        // }

        Timeout::operator bool() const
        {
            return this->__state != RunStateT::finished;
        }

        bool Timeout::scheduled()
        {
            return this->__state != RunStateT::finished;
        }

        bool Timeout::finished()
        {
            return this->__state == RunStateT::finished;
        }

        void Timeout::toggle()
        {
            if (this->finished())
                return this->restart(-1);
            return this->cancel();
        }

        void Timeout::restart(unsigned long timeout_ms)
        {
            this->_timeout_ms = (timeout_ms == -1) ? _timeout_ms : timeout_ms;
            this->__state = RunStateT::waiting;
            this->_tic_ms = (_core != nullptr) ? _core->millis() : -1;
            _on_restarted();
        }

        void Timeout::cancel()
        {
            this->__state = RunStateT::finished;
        }

        Timeout *Timeout::__first = nullptr;
        Timeout *Timeout::__last = nullptr;

        Timeout *Timeout::_first()
        {
            return __first;
        }
        Timeout *Timeout::_last()
        {
            return __last;
        }
        Timeout *Timeout::_next()
        {
            return __next;
        }
        Timeout *Timeout::_prev()
        {
            return __prev;
        }

    };
};