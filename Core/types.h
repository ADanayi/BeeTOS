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

namespace B
{
    class Core;

    namespace runnables
    {
        class Timeout;
        class Interval;
    };

    namespace signallers
    {
        class Timeout;
        class Interval;
    };

    enum class RunStateT
    {
        waiting,
        executing,
        delaying,
        finished
    };
};