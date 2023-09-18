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

namespace B
{
    class Core
    {
    public:
        explicit Core() = delete;
        Core(Core &) = delete;
        Core(Core &&) = delete;
        Core(unsigned long int (*millis)(void), const char *const core_name = "no_name", bool choose_as_active_core = true);
        unsigned long int (*const millis)(void);
        // void delay(unsigned long ms);

        bool tic(); // Returns false if there are no more timeouts waiting to be executed! Useful for standby and low power scenarios
        void collect_homeless_entities();
        void join(); // Joins the core and returns when
        void resync_all(); // Resets the time. Useful at the startup!

        static Core *active_core();

    protected:
    private:
        const char *const __name;
        static Core *__active_core;
        runnables::Timeout *__cursor;
    };
};