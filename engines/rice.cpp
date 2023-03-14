
#include <array>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "chess.hpp"
#include "rice.h"

#if TAPERED

using namespace Chess;
using namespace std;


struct Trace
{
    int32_t material[12];
    int32_t psqt[12][64];

    int32_t rook_semi_open_file[2]{0,0};
    int32_t rook_open_file[2]{0,0};

    int32_t bishop_pair[2]{0, 0};

};

constexpr std::array<int32_t, 6> material = {S(82, 94), S(337, 281), S(365, 297), S(477, 512), S(1025, 936)};

constexpr int32_t bishop_pair = S(22, 88);
constexpr int32_t rook_semi_open_file = S(8, 7);
constexpr int32_t rook_open_file = S(16, 14);

constexpr int32_t psqt[12][64] = {
{
S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),
S(98,178),S(134,173),S(61,158),S(95,134),S(68,147),S(126,132),S(34,165),S(-11,187),
S(-6,94),S(7,100),S(26,85),S(31,67),S(65,56),S(56,53),S(25,82),S(-20,84),
S(-14,32),S(13,24),S(6,13),S(21,5),S(23,-2),S(12,4),S(17,17),S(-23,17),
S(-27,13),S(-2,9),S(-5,-3),S(12,-7),S(17,-7),S(6,-8),S(10,3),S(-25,-1),
S(-26,4),S(-4,7),S(-4,-6),S(-10,1),S(3,0),S(3,-5),S(33,-1),S(-12,-8),
S(-35,13),S(-1,8),S(-20,8),S(-23,10),S(-15,13),S(24,0),S(38,2),S(-22,-7),
S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),S(0,0),
},

{
S(-167,-58),S(-89,-38),S(-34,-13),S(-49,-28),S(61,-31),S(-97,-27),S(-15,-63),S(-107,-99),
S(-73,-25),S(-41,-8),S(72,-25),S(36,-2),S(23,-9),S(62,-25),S(7,-24),S(-17,-52),
S(-47,-24),S(60,-20),S(37,10),S(65,9),S(84,-1),S(129,-9),S(73,-19),S(44,-41),
S(-9,-17),S(17,3),S(19,22),S(53,22),S(37,22),S(69,11),S(18,8),S(22,-18),
S(-13,-18),S(4,-6),S(16,16),S(13,25),S(28,16),S(19,17),S(21,4),S(-8,-18),
S(-23,-23),S(-9,-3),S(12,-1),S(10,15),S(19,10),S(17,-3),S(25,-20),S(-16,-22),
S(-29,-42),S(-53,-20),S(-12,-10),S(-3,-5),S(-1,-2),S(18,-20),S(-14,-23),S(-19,-44),
S(-105,-29),S(-21,-51),S(-58,-23),S(-33,-15),S(-17,-22),S(-28,-18),S(-19,-50),S(-23,-64),
},

{
S(-29,-14),S(4,-21),S(-82,-11),S(-37,-8),S(-25,-7),S(-42,-9),S(7,-17),S(-8,-24),
S(-26,-8),S(16,-4),S(-18,7),S(-13,-12),S(30,-3),S(59,-13),S(18,-4),S(-47,-14),
S(-16,2),S(37,-8),S(43,0),S(40,-1),S(35,-2),S(50,6),S(37,0),S(-2,4),
S(-4,-3),S(5,9),S(19,12),S(50,9),S(37,14),S(37,10),S(7,3),S(-2,2),
S(-6,-6),S(13,3),S(13,13),S(26,19),S(34,7),S(12,10),S(10,-3),S(4,-9),
S(0,-12),S(15,-3),S(15,8),S(15,10),S(14,13),S(27,3),S(18,-7),S(10,-15),
S(4,-14),S(15,-18),S(16,-7),S(0,-1),S(7,4),S(21,-9),S(33,-15),S(1,-27),
S(-33,-23),S(-3,-9),S(-14,-23),S(-21,-5),S(-13,-9),S(-12,-16),S(-39,-5),S(-21,-17),
},

{
S(32,13),S(42,10),S(32,18),S(51,15),S(63,12),S(9,12),S(31,8),S(43,5),
S(27,11),S(32,13),S(58,13),S(62,11),S(80,-3),S(67,3),S(26,8),S(44,3),
S(-5,7),S(19,7),S(26,7),S(36,5),S(17,4),S(45,-3),S(61,-5),S(16,-3),
S(-24,4),S(-11,3),S(7,13),S(26,1),S(24,2),S(35,1),S(-8,-1),S(-20,2),
S(-36,3),S(-26,5),S(-12,8),S(-1,4),S(9,-5),S(-7,-6),S(6,-8),S(-23,-11),
S(-45,-4),S(-25,0),S(-16,-5),S(-17,-1),S(3,-7),S(0,-12),S(-5,-8),S(-33,-16),
S(-44,-6),S(-16,-6),S(-20,0),S(-9,2),S(-1,-9),S(11,-9),S(-6,-11),S(-71,-3),
S(-19,-9),S(-13,2),S(1,3),S(17,-1),S(16,-5),S(7,-13),S(-37,4),S(-26,-20),
},

{
S(-28,-9),S(0,22),S(29,22),S(12,27),S(59,27),S(44,19),S(43,10),S(45,20),
S(-24,-17),S(-39,20),S(-5,32),S(1,41),S(-16,58),S(57,25),S(28,30),S(54,0),
S(-13,-20),S(-17,6),S(7,9),S(8,49),S(29,47),S(56,35),S(47,19),S(57,9),
S(-27,3),S(-27,22),S(-16,24),S(-16,45),S(-1,57),S(17,40),S(-2,57),S(1,36),
S(-9,-18),S(-26,28),S(-9,19),S(-10,47),S(-2,31),S(-4,34),S(3,39),S(-3,23),
S(-14,-16),S(2,-27),S(-11,15),S(-2,6),S(-5,9),S(2,17),S(14,10),S(5,5),
S(-35,-22),S(-8,-23),S(11,-30),S(2,-16),S(8,-16),S(15,-23),S(-3,-36),S(1,-32),
S(-1,-33),S(-18,-28),S(-9,-22),S(10,-43),S(-15,-5),S(-25,-32),S(-31,-20),S(-50,-41),
},

{
S(-65,-74),S(23,-35),S(16,-18),S(-15,-18),S(-56,-11),S(-34,15),S(2,4),S(13,-17),
S(29,-12),S(-1,17),S(-20,14),S(-7,17),S(-8,17),S(-4,38),S(-38,23),S(-29,11),
S(-9,10),S(24,17),S(2,23),S(-16,15),S(-20,20),S(6,45),S(22,44),S(-22,13),
S(-17,-8),S(-20,22),S(-12,24),S(-27,27),S(-30,26),S(-25,33),S(-14,26),S(-36,3),
S(-49,-18),S(-1,-4),S(-27,21),S(-39,24),S(-46,27),S(-44,23),S(-33,9),S(-51,-11),
S(-14,-19),S(-14,-3),S(-22,11),S(-46,21),S(-44,23),S(-30,16),S(-15,7),S(-27,-9),
S(1,-27),S(7,-11),S(-8,4),S(-64,13),S(-43,14),S(-16,4),S(9,-5),S(8,-17),
S(-15,-53),S(36,-34),S(12,-21),S(-54,-11),S(8,-28),S(-28,-14),S(24,-24),S(14,-43),
},
};

U64 FileMasks[64] = {
72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,72340172838076673ULL,144680345676153346ULL,289360691352306692ULL,578721382704613384ULL,1157442765409226768ULL,2314885530818453536ULL,4629771061636907072ULL,9259542123273814144ULL,};

// Check if a file is semi open for a given side
static inline bool IsSemiOpenFile(Board &board, Square sq, Color us)
{
    return (((us == White) ? board.piecesBB[WhitePawn] : board.piecesBB[BlackPawn]) & FileMasks[sq]) == 0;
}

// Check if a file is open
static inline bool IsOpenFile(Board &board, Square sq)
{
    return ((board.piecesBB[WhitePawn] | board.piecesBB[BlackPawn]) & FileMasks[sq]) == 0;
}

static Trace Evaluate(Board& board){
    Trace trace;

    U64 white_pieces = board.Us(White);
    U64 black_pieces = board.Us(Black);

    while (white_pieces)
    {
        Square sq = poplsb(white_pieces);
        Piece p = board.pieceAtB(sq);

        trace.material[p]++;
        trace.psqt[p][sq^56]++;

        if (p == WhiteRook)
        {
            // Rook semi open file bonus
            if (IsSemiOpenFile(board, sq, White))
            {
                trace.rook_semi_open_file[0]++;
            }
            // Rook open file bonus
            else if (IsOpenFile(board, sq))
            {
                trace.rook_open_file[0]++;                
            }
        }
    }

    while (black_pieces)
    {
        Square sq = poplsb(black_pieces);
        Piece p = board.pieceAtB(sq);

        trace.material[p]++;
        trace.psqt[p][sq]++;

        if (p == WhiteRook)
        {
            // Rook semi open file bonus
            if (IsSemiOpenFile(board, sq, Black))
            {
                trace.rook_semi_open_file[1]++;
            }
            // Rook open file bonus
            else if (IsOpenFile(board, sq))
            {
                trace.rook_open_file[1]++;                
            }
        }
    }

    if (popcount(board.piecesBB[WhiteBishop]) > 1)
    {
        trace.bishop_pair[0] = 1;
    }else{
        trace.bishop_pair[0] = 0;
    }
    if (popcount(board.piecesBB[BlackBishop]) > 1)
    {
        trace.bishop_pair[1] = 1;
    }else{
        trace.bishop_pair[1] = 0;
    }
    
    return trace;
}

static coefficients_t get_coefficients(Trace trace)
{
    coefficients_t coefficients;
    get_coefficient_array(coefficients, trace.material, 12);
    get_coefficient_array_2d(coefficients, trace.psqt, 12, 64);

    get_coefficient_single(coefficients, trace.rook_semi_open_file);
    get_coefficient_single(coefficients, trace.rook_open_file);

    get_coefficient_single(coefficients, trace.bishop_pair);
    return coefficients;
}

parameters_t Rice::RiceEval::get_initial_parameters()
{
    parameters_t parameters;
    get_initial_parameter_array(parameters, material, 12);
    get_initial_parameter_array_2d(parameters, psqt, 12, 64);

    get_initial_parameter_single(parameters, rook_semi_open_file);
    get_initial_parameter_single(parameters, rook_open_file);

    get_initial_parameter_single(parameters, bishop_pair);
    return parameters;
}

EvalResult Rice::RiceEval::get_fen_eval_result(const string& fen)
{
    Board position(fen);
    Trace trace = Evaluate(position);
    EvalResult result;
    result.coefficients = get_coefficients(trace);
    result.score = 0;
    return result;
}

static void print_parameter(std::stringstream& ss, const pair_t parameter)
{
    ss << "S(" << parameter[static_cast<int32_t>(PhaseStages::Midgame)] << ", " << parameter[static_cast<int32_t>(PhaseStages::Endgame)] << ")";
}

static void print_single(std::stringstream& ss, const parameters_t& parameters, int& index, const std::string& name)
{
    ss << "constexpr int " << name << " = ";
    print_parameter(ss, parameters[index]);
    ss << ";" << endl;
    index++;
}

static void print_array(std::stringstream& ss, const parameters_t& parameters, int& index, const std::string& name, int count)
{
    ss << "constexpr int " << name << "[] = {";
    for (auto i = 0; i < count; i++)
    {
        print_parameter(ss, parameters[index]);
        index++;

        if (i != count - 1)
        {
            ss << ", ";
        }
    }
    ss << "};" << endl;
}

static void print_array_2d(std::stringstream& ss, const parameters_t& parameters, int& index, const std::string& name, int count1, int count2)
{
    ss << "const int " << name << "[][" << count2 << "] = {\n";
    for (auto i = 0; i < count1; i++)
    {
        ss << "    {";
        for (auto j = 0; j < count2; j++)
        {
            print_parameter(ss, parameters[index]);
            index++;

            if (j != count2 - 1)
            {
                ss << ", ";
            }
        }
        ss << "},\n";
    }
    ss << "};\n";
}

void Rice::RiceEval::print_parameters(const parameters_t& parameters)
{
    int index = 0;
    stringstream ss;
    print_array(ss, parameters, index, "material", 12);
    print_array_2d(ss, parameters, index, "psqt", 12, 64);
    print_single(ss, parameters, index, "RookSemiOpenFile");
    print_single(ss, parameters, index, "RookOpenFile");
    print_single(ss, parameters, index, "bishop_pair");
    cout << ss.str() << "\n";
}

#endif
