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

#include "types.h"
#include "core_cls.h"
#include "../Runnables/timeout_cls.h"

// #include <iostream>

namespace B
{
    // void delay(unsigned long int ms, Core *core = nullptr)
    // {
    //     if (core == nullptr)
    //     {
    //         core = Core::active_core();
    //     }
    //     if (core != nullptr)
    //     {
    //         core->delay(ms);
    //     }
    // }

    bool Core::tic()
    {
        bool finished = true;
        __cursor = runnables::Timeout::_first();

        while (__cursor != nullptr)
        {
            if (__cursor->_core != this)
            {
                __cursor = __cursor->_next();
                continue;
            }

            finished = finished & (__cursor->__state == RunStateT::finished);

            if (__cursor->__state == RunStateT::delaying)
            {
                if (millis() - __cursor->_delay_tic_ms >= __cursor->_delay_timeout_ms)
                {
                    __cursor->__state = RunStateT::executing;
                }
                __cursor = __cursor->_next();
                continue;
            }

            if (__cursor->__state == RunStateT::waiting)
            {
                if (__cursor->_tic_ms == -1)
                {
                    __cursor->_tic_ms = millis();
                }
                else
                {
                    if (__cursor->_timeout_ms <= millis() - __cursor->_tic_ms)
                    {
                        __cursor->_on_executing();
                        __cursor->__state = RunStateT::executing;
                        if (__cursor->_on_timeout != nullptr)
                            __cursor->_on_timeout();
                        if (__cursor->__state == RunStateT::executing)
                        {
                            __cursor->__state = RunStateT::finished;
                            __cursor->_on_executed();
                        }
                    }
                }
            }

            __cursor = __cursor->_next();
        }
        __cursor = nullptr;

        return !finished;
    }

    Core::Core(unsigned long int (*millis)(void), const char *const core_name, bool choose_as_active_core) : __name{core_name},
                                                                                                             millis{millis}
    {
        if (choose_as_active_core)
            __active_core = this;
    }

    void Core::collect_homeless_entities()
    {
        runnables::Timeout *cursor = runnables::Timeout::_first();
        while (cursor != nullptr)
        {
            if (cursor->_core == nullptr)
            {
                cursor->_core = this;
            }
            cursor = cursor->_next();
        }
    }

    void Core::resync_all()
    {
        runnables::Timeout *cursor = runnables::Timeout::_first();
        auto ms = millis();
        while (cursor != nullptr)
        {
            if (cursor->_core == this)
            {
                cursor->_tic_ms = ms;
            }
            cursor = cursor->_next();
        }
    }

    // void Core::delay(unsigned long ms)
    // {
    //     auto tic_ms = millis();
    //     runnables::Timeout *const delayer = __cursor;
    //     if ((delayer == nullptr) || (delayer->__state != RunStateT::executing) || (delayer->_core != this))
    //     {
    //         return;
    //     }

    //     delayer->__state = RunStateT::delaying;
    //     delayer->_delay_tic_ms = millis();
    //     delayer->_delay_timeout_ms = ms;
    //     while (delayer->__state == RunStateT::delaying)
    //     {
    //         tic();
    //     }
    //     delayer->__state = RunStateT::executing;
    //     __cursor = delayer;
    // }

    void Core::join()
    {
        while (tic())
        {
        };
    }

    Core *Core::__active_core = nullptr;
    Core *Core::active_core()
    {
        return Core::__active_core;
    }
};