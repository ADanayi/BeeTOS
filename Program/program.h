/*
 * بسم الله الرحمن الرحیم
 * اللهم صل علی محمد و آل محمد
 * ---------------------------
 * Created on Sun Sep 17 2023
 *
 * Copyright (c) 2023 Abolfazl Danayi
 * adanayidet@gmail.com
 */

#include "../Core/core.h"
#include "../Runnables/interval.h"

namespace B
{
    class Program : private Core
    {
    public:
        explicit Program(unsigned long (*millis)(void), void (*setup)(), void (*loop)(), const char *program_name = "unnamed_program") : Core(millis, program_name, true),
                                                                                                                                         __root{0, loop, this},
                                                                                                                                         __setup{setup} {};
        Program(Program &) = delete;
        Program(Program &&) = delete;

        void join()
        {
            __setup();
            this->collect_homeless_entities();
            this->resync_all();
            while (this->tic())
                this->collect_homeless_entities();
        }

    private:
        runnables::Interval __root;
        void (*const __setup)();
    };
};