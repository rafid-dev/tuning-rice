#ifndef RICE_H
#define RICE_H

#include "../base.h"
#include <string>
#include <vector>

// parameters_t get_initial_parameters();
// int get_fen_eval_result(const std::string& fen);
// void print_parameters(const parameters_t& parameters);

#if TAPERED


namespace Rice
{
    class RiceEval
    {
    public:
        constexpr static bool includes_additional_score = true;

        static parameters_t get_initial_parameters();
        static EvalResult get_fen_eval_result(const std::string& fen);
        static void print_parameters(const parameters_t& parameters);
    };
}

#endif

#endif