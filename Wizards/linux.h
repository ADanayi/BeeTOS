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

#include <sys/time.h>
#include <stdio.h>
#include <unistd.h>

#include "../B.h"

void setup();
void loop();

namespace B
{
    namespace B_linux
    {
        struct timeval __millis_start;

        void init_millis()
        {
            gettimeofday(&__millis_start, NULL);
        };

        unsigned long int millis()
        {
            long mtime, seconds, useconds;
            struct timeval end;
            gettimeofday(&end, NULL);
            seconds = end.tv_sec - __millis_start.tv_sec;
            useconds = end.tv_usec - __millis_start.tv_usec;

            mtime = ((seconds) * 1000 + useconds / 1000.0) + 0.5;
            return mtime;
        };

        void __setup()
        {
            init_millis();
            setup();
        }

        Program prg{millis, __setup, loop, "BeeLinuxProgram"};
    };
};

int main()
{
    B::B_linux::prg.join();
}