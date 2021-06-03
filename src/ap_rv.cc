#include "ap_rv.h"

APrv::APrv()
{
    printf("\t # RV Across #\n");
    this->lookup_and_init();
    this->lookup_or_init();
    this->lookup_xor_init();
    this->lookup_not_init();
    this->lookup_add_init();
    this->lookup_sub_init();
    this->lookup_mult_init();
}

APrv::~APrv()
{}

// Cr, R, B, A, wCr, wR
void APrv::lookup_and_init()
{
    this->lookup_and[0]	= new pass(0,0,0,0,0,0);
    this->lookup_and[1]	= new pass(0,0,0,1,0,0);
    this->lookup_and[2]	= new pass(0,0,1,0,0,0);
    this->lookup_and[3]	= new pass(0,0,1,1,0,1);

    //AND optimized
    this->lookup_and_opt[0]	= new pass(0,0,1,1,0,1);
}

void APrv::lookup_or_init()
{
    this->lookup_or[0]	= new pass(0,0,0,0,0,0);
    this->lookup_or[1]	= new pass(0,0,0,1,0,1);
    this->lookup_or[2]	= new pass(0,0,1,0,0,1);
    this->lookup_or[3]	= new pass(0,0,1,1,0,1);

    //OR optimized
    this->lookup_or_opt[0]	= new pass(0,0,0,0,0,0);
}

void APrv::lookup_xor_init()
{
    this->lookup_xor[0]	= new pass(0,0,0,0,0,0);
    this->lookup_xor[1]	= new pass(0,0,0,1,0,1);
    this->lookup_xor[2]	= new pass(0,0,1,0,0,1);
    this->lookup_xor[3]	= new pass(0,0,1,1,0,0);

    //XOR optimized
    this->lookup_xor_opt[0]	= new pass(0,0,0,1,0,1);
    this->lookup_xor_opt[0]	= new pass(0,0,1,0,0,1);
}

void APrv::lookup_not_init()
{
    this->lookup_not[0]	= new pass(0,0,0,0,0,1);
    this->lookup_not[1]	= new pass(0,0,0,1,0,0);
    
    //NOT optimized
    this->lookup_not_opt[0]	= new pass(0,0,0,0,0,1);
}

void APrv::lookup_add_init()
{
    this->lookup_add[0]	= new pass(0,0,1,1,1,0);
    this->lookup_add[1]	= new pass(0,0,0,1,0,1);
    this->lookup_add[2]	= new pass(1,0,0,0,0,1);
    this->lookup_add[3]	= new pass(1,0,1,0,1,0);
}


void APrv::lookup_sub_init()
{
    //order influences
    this->lookup_sub[0]	= new pass(1,0,1,0,0,0);
    this->lookup_sub[1]	= new pass(0,0,0,1,1,1);
    this->lookup_sub[2]	= new pass(1,0,0,0,1,1);
    this->lookup_sub[3]	= new pass(0,0,1,1,0,0);
}

void APrv::lookup_mult_init()
{
    this->lookup_mult[0] = new pass(0,1,1,1,1,0);
    this->lookup_mult[1] = new pass(0,0,1,1,0,1);
    this->lookup_mult[2] = new pass(1,0,0,1,0,1);
    this->lookup_mult[3] = new pass(1,1,0,1,1,0);
}

void APrv::lookup_relu_init()
{
    this->lookup_relu[0] = new pass(0,1,1,1,0,1);
}
