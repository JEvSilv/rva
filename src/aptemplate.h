#include <map>
#include <vector>
#include <fstream>
#include <stdint.h>
#include <stdio.h>

#define set_bit(x,y) x |= (1 << y)
#define clear_bit(x,y) x &= ~(1<< y)
#define read_bit(x,y) ((0u == (x & (1<<y)))?0u:1u)
#define toggle_bit(x,y) (x ^= (1<<y))

class APTemplate {
    public:
        APTemplate();
        ~APTemplate();

        struct pass
        {
    	    pass(bool Cr, bool R, bool B, bool A, bool wCr, bool wR):Cr(Cr), R(R), B(B), A(A), wCr(wCr), wR(wR){}
	        bool Cr:1;
            bool R:1;
	        bool B:1;
	        bool A:1;
	        bool wCr:1;
    	    bool wR:1;
        };

        // recording and calculating ops
        struct info_op 
        {
            info_op(std::string op, uint32_t op_qt):op(op), op_qt(op_qt)
            {
                this->cycles = 0;
                this->comp_count = 0;
                this->wr_count = 0;
                this->op_qt = 0;
                this->mismatch = 0;
                this->match = 0;
                this->cycle_w = false;
            }
        
            std::ofstream myfile;
            std::string op;
            uint32_t op_qt;
            uint32_t cycles;
            uint32_t comp_count;
            uint32_t wr_count;
            uint32_t match;
            uint32_t mismatch;
            bool cycle_w;
            
            void open_file(bool log_mode)
            {
                if(log_mode)
                    this->myfile.open(op);
            }

            void print_info() {
                //printf("%s\n", op);
                printf("op_qt: %u\n", op_qt);
                printf("cycles: %u\n", cycles);
                printf("comp_count: %u\n", comp_count);
                printf("wr_count: %u\n", wr_count);
                printf("match: %u\n", match);
                printf("mismatch: %u\n", mismatch);
            }

            void info_plot() {
                this->myfile << "| ----- Report ----- |" << std::endl;
                this->myfile << "- Operations: " << this->op_qt << std::endl;
                this->myfile << "- Cycles: " << this->cycles << std::endl;
                this->myfile << "- Comparisons: " << this->comp_count << std::endl;
                this->myfile << "- Writings: " << this->wr_count << std::endl;
                this->myfile << "-----------------------------" << std::endl;
                this->myfile.close();
            }

        };

        uint32_t op_id;
        std::map<uint32_t, info_op*> info_ops_m;
        bool log_mode;
        
        void reset();

        void set_mask(uint32_t r_k, uint32_t cr_k, uint32_t bit_A, uint32_t bit_B);
        void set_key(std::map<uint32_t, pass*> lut, uint32_t pass, uint32_t r_k, uint32_t cr_k, uint32_t bit_A, uint32_t bit_B);

        template <typename T> void compare(T* A, T* B, T* R, bool* Cr, bool* Tag)
        {
            // Selecting
            uint32_t Cr_masked = 0;
            uint32_t R_k_masked = 0;
            uint32_t B_masked   = 0;
            uint32_t A_masked   = 0;

            if(B != NULL)
                B_masked  = *B & this->mask_B;

            if(A != NULL)
                A_masked  = *A & this->mask_A;

            if(Cr == NULL)
            {
                R_k_masked = *R & this->mask_R;
                Cr_masked = *R & this->mask_Cr;
            } else
            {
                Cr_masked = *Cr & this->mask_Cr;
            }
    
            // Comparing
            uint32_t B_res   = this->key_B ^ B_masked;
            uint32_t A_res   = this->key_A ^ A_masked;
            uint32_t R_k_res = this->key_R ^ R_k_masked;
            uint32_t Cr_res  = this->key_Cr ^ Cr_masked;
    
            this->info_ops_m[op_id]->comp_count++;

            if(B_res == 0 && A_res == 0 && R_k_res == 0 && Cr_res == 0)
            {
                *Tag = true;
                this->info_ops_m[op_id]->match++;
            } else {
                this->info_ops_m[op_id]->mismatch++;       
            }
        };

        template <typename T> void write(std::map<uint32_t, pass*> lut, uint32_t pass, uint32_t r_k, uint32_t cr_k, bool* Cr, T* R, bool* Tag)
        {
            if(*Tag)
            {
                if(Cr == NULL)
                {
                    lut[pass]->wCr ? set_bit(*R, cr_k) : clear_bit(*R, cr_k);
                }
                else 
                {
                    lut[pass]->wCr ? *Cr = 1 : *Cr = 0;
                }

        	    lut[pass]->wR  ? set_bit(*R, r_k)  : clear_bit(*R, r_k);
                this->info_ops_m[op_id]->wr_count++;
                this->info_ops_m[op_id]->cycle_w = true;
                *Tag = false;
            }
        }; 

        template <typename T> void tracing_mult(uint32_t bit, uint32_t pass, uint32_t word, bool tag, T* mem,  std::vector<T*> R_v)
        {
            info_op *i_o = this->info_ops_m[op_id];
            i_o->myfile << "\tBit: " << (unsigned) bit << " | " << "Pass: " << (unsigned) pass << std::endl;
            i_o->myfile << "\tWord: " << (unsigned) word << " | " << "Tag: " << tag << std::endl;
            i_o->myfile << "----------------------------------------"<< std::endl;
            i_o->myfile << "\tMask_A: ";
            this->print_bit_n(this->mask_A);
            i_o->myfile << "\tMask_B: ";
            this->print_bit_n(this->mask_B);
            i_o->myfile << "\tKey_A: ";
            this->print_bit_n(this->key_A);
            i_o->myfile << "\tKey_B: ";
            this->print_bit_n(this->key_B);
            i_o->myfile << "\tKey_Cr: ";
            this->print_bit_n(this->key_Cr);
            i_o->myfile << "\tKey_R: ";
            this->print_bit_n(this->key_R);
            i_o->myfile << "----------------------------------------"<< std::endl << std::endl;
            uint32_t i = 0;
            for(i = 0; i < this->mem_size; i++)
            {
        	i_o->myfile << "mem[" << (unsigned) i << "]: ";
        	this->print_bit_n(mem[i]); 
            }
            i_o->myfile << std::endl;
            i_o->myfile << "# Results #" << std::endl;
            i = 0;
            for (auto r : R_v)
            {
         	i_o->myfile << "R_v[" <<(unsigned) i << "]: ";
        	this->print_bit_n(*R_v.at(i));        
                i++;
            }
            i_o->myfile << "----------------------------------------"<< std::endl;
        };

        template <typename T> void tracing_add(uint32_t bit, uint32_t pass, uint32_t word, bool tag, T* mem)
        {
            info_op *i_o = this->info_ops_m[op_id];
            i_o->myfile << "\tBit: " << (unsigned) bit << " | " << "Pass: " << (unsigned) pass << std::endl;
            i_o->myfile << "\tWord: " << (unsigned) word << " | " << "Tag: " << tag << std::endl;
            i_o->myfile << "----------------------------------------"<< std::endl;
            i_o->myfile << "\tMask_A: ";
            this->print_bit_n(this->mask_A);
            i_o->myfile << "\tMask_B: ";
            this->print_bit_n(this->mask_B);
            i_o->myfile << "\tKey_A: ";
            this->print_bit_n(this->key_A);
            i_o->myfile << "\tKey_B: ";
            this->print_bit_n(this->key_A);
            i_o->myfile << "----------------------------------------"<< std::endl << std::endl;
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
        	i_o->myfile << "mem[" << (unsigned) i << "]: ";
        	this->print_bit_n(mem[i]); 
            }
            i_o->myfile << std::endl;
            i_o->myfile << "# ---------------------------------------- #"<< std::endl;
        };
        
        template <typename T> void print_mem(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                this->info_ops_m[op_id]->myfile << "mem[" << (unsigned) i << "] =>  " << (unsigned) mem[i] << std::endl;
                printf("mem[%u] => %u\n", i, mem[i]);
            }
        };

        void print_bit_n(uint32_t n)
        {
            for(int i = this->word_size-1; i >= 0; i--) {
                this->info_ops_m[op_id]->myfile << (int) read_bit(n,i);
                //printf("%d", read_bit(n,i));
            }
	        //printf("\n");
            this->info_ops_m[op_id]->myfile << std::endl;
        };

        void register_op(std::string op_name);
        void set_cycles(uint32_t c);
        
        uint32_t input_addr_a, input_addr_b;
        uint32_t input_addr, output_addr;
        uint8_t word_size;
        uint64_t mem_size, key, mask, factor, key_R, key_A, key_B, key_Cr, mask_R, mask_A, mask_B, mask_Cr;

};
