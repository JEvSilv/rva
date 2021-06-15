#include "aptemplate.h"

APTemplate::APTemplate()
{
    this->op_id = 0;
    this->log_mode = false;
}

APTemplate::~APTemplate()
{}

void APTemplate::register_op(std::string op_name)
{
    std::string _op = op_name+ "_" + std::to_string(this->op_id);
    this->info_ops_m[this->op_id] = new info_op(_op, this->mem_size);
    this->info_ops_m[this->op_id]->open_file(this->log_mode);
}

void APTemplate::set_cycles(uint32_t c)
{
    this->info_ops_m[this->op_id]->cycles = c;
}

void APTemplate::reset()
{
    this->input_addr_a  = 0;
    this->input_addr_b  = 0;
    this->input_addr  = 0;
    this->output_addr = 0;
    this->key         = 0;
    this->mask        = 0;
    this->mem_size    = 0;
    this->factor      = 0;
    this->key_B       = 0;
    this->key_A       = 0;
    this->key_Cr      = 0;        
    this->mask_B      = 0; 
    this->mask_A      = 0;
    this->mask_Cr     = 0; 
}

void APTemplate::set_mask(uint32_t r_k, uint32_t cr_k, uint32_t bit_A, uint32_t bit_B)
{
    this->mask_A  = 0;
    this->mask_B  = 0;
    this->mask_Cr = 0;
    this->mask_R  = 0;

    set_bit(this->mask_A, bit_A);
    set_bit(this->mask_B, bit_B);
    set_bit(this->mask_Cr, cr_k);
    set_bit(this->mask_R, r_k);
}

void APTemplate::set_key(std::map<uint32_t, pass*> lut, uint32_t pass, uint32_t r_k, uint32_t cr_k, uint32_t bit_A, uint32_t bit_B)
{
    this->key_A  = 0;
    this->key_B  = 0;
    this->key_Cr = 0;
    this->key_R  = 0;

    if(lut[pass]->A)
	    set_bit(this->key_A, bit_A);
	
    if(lut[pass]->B)
	    set_bit(this->key_B, bit_B);

    if(lut[pass]->Cr)
	    set_bit(this->key_Cr, cr_k);

    if(lut[pass]->R)
	    set_bit(this->key_R, r_k);
}
