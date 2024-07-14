#include <stdio.h>
#include <math.h>

// 제어 변수 정의 및 선언
double Vsa, Isa, DV, DV_1, DV_new, diff_P;
int TUpdate;
double Psa, flag;
double T1, T2;
static int i = 0;
static double Psa_old = 0, Vsa_old = 0, Vref = 0., Isa_old, Duty = 0, B, dP, dV = 0;

double Verr, Duty_old, Verr_old, Verr_int = 0;
double Kp = 0.0380, Ki = 0.0380;
double delta_V = 0, delta_l = 0, Dslope = 0, slope = 0;
double Ts = 0.001;

double Voc = 23.8;
double W = 0.66 * 23.8;
double Z = 0.94 * 23.8;


__declspec(dllexport) void simuser(double t, double dt, double* in, double* out)
{

    Vsa = in[0];
    Isa = in[1];
    DV = in[2];
    TUpdate = in[3];

    diff_P = (floor((fabs(Psa - Psa_old) + 0.5) * 1000)) / 10;


    i = 3 * t / Ts;

    if (i % TUpdate == 0)
    {

        Psa = Vsa * Isa;
        dP = Psa - Psa_old;
        dV = Vsa - Vsa_old;


        //  Improved Algorithm

        if (Vsa < W) {
            Vref = Vref + 1;
        }
        else {
            if (Vsa > Z) {
                Vref = Vref - 1;
            }
            else {
                if (Psa >= Psa_old) {
                    if (Vsa > Vsa_old) Vref = Vref + 0.15;
                    else               Vref = Vref - 0.15;
                }
                else {
                    if (Vsa > Vsa_old) Vref = Vref - 0.15;
                    else               Vref = Vref + 0.15;
                }
            }
        }

        Psa_old = Psa;
        Vsa_old = Vsa;

    } // end of MPPT

 // Current Controller
    Verr = Vsa - Vref;
    Verr_int += Ki * Verr;

    Duty = Kp * Verr + Ki * Verr_int;

    Duty_old = Duty;
    Verr_old = Verr;

    out[0] = Duty;
    out[1] = Verr;
    out[2] = Vref;

}


// P & O Algorithm

//if (Psa >= Psa_old) {
//    if (Vsa > Vsa_old) Vref = Vref + DV;
//    else               Vref = Vref - DV;
//}
//else {
//    if (Vsa > Vsa_old) Vref = Vref - DV;
//    else               Vref = Vref + DV;
//}