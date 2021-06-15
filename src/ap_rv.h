#include "aptemplate.h"
// implement logic operations behaviors
class APrv : public APTemplate
{
    public:
        APrv();
        ~APrv();
         
        void lookup_and_init();
        void lookup_or_init();
        void lookup_xor_init();
        void lookup_not_init();

        void lookup_add_init();
        void lookup_mult_init();
        void lookup_sub_init();
        void lookup_relu_init();       

        //logic
        template <typename T> void _and(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] &= this->factor;
            }
        };

        template <typename T> void __and(T* mem) {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            this->word_size = word_size;

            for (i = 0; i < op_size; i++) {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }

            for(bit = 0; bit < word_size; bit++) {
        	    for(pass = 0; pass < 4; pass++) {
            	    for(word = 0; word < op_size; word++) {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_and, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                this->write<T>(this->lookup_and, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));
	                }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
	            }	
            }
	        
            if(log_mode)
                info_ops_m[op_id]->info_plot();
        }

        template <typename T> void __or(T* mem)
        {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            this->word_size = word_size;           

            for (i = 0; i < op_size; i++) {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }

            for(bit = 0; bit < word_size; bit++) {
        	    for(pass = 0; pass < 4; pass++) {
            	    for(word = 0; word < op_size; word++) {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_or, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                this->write<T>(this->lookup_or, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));
	                }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
	            }	
            }
	        
            if(log_mode)
                info_ops_m[op_id]->info_plot();
        };

        template <typename T> void _or(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] |= this->factor;
            }
        };

        template <typename T> void _xor(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] ^= this->factor;
            }
        };

        template <typename T> void __xor(T* mem)
        {
            std::vector<T*> R_v, B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            this->word_size = word_size;
            
            for (i = 0; i < op_size; i++) {
                //C_v
                R_v.push_back(new T(0)); 
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }

            for(bit = 0; bit < word_size; bit++) {
        	    for(pass = 0; pass < 4; pass++) {
            	    for(word = 0; word < op_size; word++) {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_xor, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                this->write<T>(this->lookup_xor, pass, bit, 0, Cr_v.at(word), R_v.at(word), Tag_v.at(word));
	                }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }
                    this->info_ops_m[op_id]->cycles++;
	            }	
            }
            
            for(int i = 0; i < op_size; i++) {
                *B_v.at(i) = *R_v.at(i);
            }

            if(log_mode)
                info_ops_m[op_id]->info_plot();
        };

        template <typename T> void _not(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] = ~mem[i];
            }
        };

        template <typename T> void __not(T* mem)
        {
            std::vector<T*> A_v, R_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            this->word_size = word_size;
            
            for (i = 0; i < op_size; i++) {
                A_v.push_back(&mem[i]); 
                R_v.push_back(new T(0)); 
        	    Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }
            
            for(bit = 0; bit < word_size; bit++) {
        	    for(pass = 0; pass < 2; pass++) {
            	    for(word = 0; word < op_size; word++) {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_not, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), NULL, NULL, Cr_v.at(word), Tag_v.at(word)); 
                        
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                
                        this->write<T>(this->lookup_not, pass, bit, 0, Cr_v.at(word), R_v.at(word), Tag_v.at(word));
	                
                    }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
	            }	
            }

            for(int i = 0; i < op_size; i++) {
                *A_v.at(i) = *R_v.at(i);
            }
            
            if(log_mode)
                info_ops_m[op_id]->info_plot();
        };

        template <typename T> void _sll(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] <<= this->factor;
            }
        };

        template <typename T> void _srl(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] >>= this->factor;
            }
        };

        //arith
        template <typename T> void add(T* mem) {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
            this->word_size = word_size;

            for (i = 0; i < op_size; i++) {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }
	
            for(bit = 0; bit < word_size; bit++) {
        	    for(pass = 0; pass < 4; pass++) {
            	    for(word = 0; word < op_size; word++) {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_add, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                this->write<T>(this->lookup_add, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));
	                }
            
                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
	            }	
            }

            if(log_mode)
	            info_ops_m[op_id]->info_plot();
        };

        template <typename T> void sub(T* mem)
        {
            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t word_size = 8 * sizeof(T);
            uint32_t bit, pass, word, i;
            this->word_size = word_size;

            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    Cr_v.push_back(new bool(0));
	            Tag_v.push_back(new bool(0));
            }
            
	        for(bit = 0; bit < word_size; bit++)
            {
        	for(pass = 0; pass < 4; pass++)
	        {
            	    for(word = 0; word < op_size; word++)
	            {
        	        this->set_mask(bit, 0, bit, bit);		
	        	this->set_key(this->lookup_sub, pass, bit, 0, bit, bit);

		        this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 

                        if(log_mode) {
            		    this->tracing_add(bit, pass, word, *Tag_v.at(word), mem);		
                        }
                
                        this->write<T>(this->lookup_sub, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));

                    }

                    if(this->info_ops_m[op_id]->cycle_w) {
                        this->info_ops_m[op_id]->cycles++;
                        this->info_ops_m[op_id]->cycle_w = false;
                    }

                    this->info_ops_m[op_id]->cycles++;
               	}	
            }
            
            if(log_mode)
	            info_ops_m[op_id]->info_plot();
        };
        
        template <typename T> void inverter(T* mem) {
            /*
             uint32_t op_size = this->mem_size/2;
             T aux[op_size];
             uint32_t i, j, index_b, index_e;
              
             for(i = 0; i < this->mem_size; i++) {
                printf("%d ", mem[i]);
             }
             printf("\n");
             

             for(i = op_size; i > 0; i--) {
                 if(mem[i-1] > 0) {
                     index_e = i;
                     break;
                 }
             }

             for(i = 0; i < op_size; i++) {
                 if(mem[i] >  0) {
                     index_b = i;
                     break;
                 }
             }
             
             j = index_b;
             for(i = index_e; i > index_b; i--) {
                 aux[j] = mem[i-1];
                 j++;
             }
          
             for(i = index_b; i < index_e; i++) {
                 mem[i] = aux[i];
             }
                
             
             int sum = 0;
             for(i = 0; i < op_size; i++) {
                sum += mem[i]*mem[i+op_size];
                printf("%d * %d => %d\n", mem[i], mem[i+op_size], mem[i]*mem[i+op_size]);
             }
             printf("Sum: %d\n", sum);           
             printf("-------------------------\n");           
             */
             return;
        }

        template <typename T> void mult(T* mem) {
            std::vector<T*> B_v, A_v;
            std::vector<T*> R_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base  = op_size;
            uint32_t bit_A, bit_B, pass, word, i;
            uint32_t r_k, cr_k;
            this->word_size = sizeof(T) * 8;
            //uint32_t range = 4;
            //
            uint32_t range = (8 * sizeof(T))/2;
            //uint32_t range = (8 * sizeof(T));

            r_k  = 0;
            cr_k =  range - 1;
               
            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
        	    R_v.push_back(new T(0));
        	    Tag_v.push_back(new bool(0));
            }

            for(bit_A = 0; bit_A < range; bit_A++) {
              cr_k++; 
              for(bit_B = 0; bit_B < range; bit_B++) {
              r_k = bit_A + bit_B;
        	  for(pass = 0; pass < 4; pass++) {
                  for(word = 0; word < op_size; word++) {
        		  this->set_mask(r_k, cr_k, bit_A, bit_B);	
        		  this->set_key(this->lookup_mult, pass, r_k, cr_k, bit_A, bit_B);
                          this->compare(A_v.at(word), B_v.at(word), R_v.at(word), NULL, Tag_v.at(word));
                          if(log_mode) {
                            this->tracing_mult(bit_A, pass, word, *Tag_v.at(word), mem, R_v);
                          }
                          this->write(this->lookup_mult, pass, r_k, cr_k, NULL, R_v.at(word), Tag_v.at(word));
        	      }
        
                  if(this->info_ops_m[op_id]->cycle_w) {
                    this->info_ops_m[op_id]->cycles++;
                    this->info_ops_m[op_id]->cycle_w = false;
                  }

                      this->info_ops_m[op_id]->cycles++;
  	          }	
               }
            }

            for(i = 0; i < op_size; i++)
            {
                mem[i] = *R_v.at(i);
            }
            
            if(log_mode)
       	        info_ops_m[op_id]->info_plot();
        };

        template <typename T> void relu(T* mem) {
            // printf("RELU\n");
            std::vector<T*> B_v, A_v;
            std::vector<T*> R_v;
            std::vector<bool*> Tag_v;
            uint32_t op_size = this->mem_size/2;
            uint32_t base  = op_size;
            int i;               
            for (i = 0; i < op_size; i++) 
            {
                A_v.push_back(&mem[i]); 
                B_v.push_back(&mem[base + i]); 
            	Tag_v.push_back(new bool(0));
            }
            // printf("RELU 2\n");           
            // Indentify 0x800 
            this->key_A = 0; 
            this->mask_A = 0xFFF;
            for(auto &a : A_v) {
                if((*a & mask_A) == 0) {
                    //printf("antes: %d\n", *a);
                    *a = 0x80000000;
                    //printf("depois: %d\n", *a);
                }
            }
           
            this->key_A = 0x80000000; 
            this->mask_A = 0x80000000;

            this->mask_B = 0x1;
            this->key_B = 0x1;  
            uint32_t masked_A = 0;
            for (i = 0; i < op_size; i++) 
            {
                masked_A = this->mask_A & *A_v.at(i);
                if(masked_A == this->key_A) {
                    *B_v.at(i) = 0;
                    // printf("%d | %d\n",i, *B_v.at(i));
                }
            }               

            // printf("RELU 3\n");                        

            for(i = 0; i < op_size; i++)
            {
                mem[i] = *B_v.at(i);
            }
            
            this->info_ops_m[op_id]->cycles = 3;

       	    info_ops_m[op_id]->info_plot();
        };


        template <typename T> void div(T* mem)
        {
            uint32_t op_size = this->mem_size/2;
            uint32_t base    = op_size;

            for(uint32_t i = 0; i < op_size; i++)
            {
                mem[i] = mem[i] / mem[base + i];
            }
        };
       
        template <typename T> void print_bit_mem(T* mem) 
        {
            int w_s = (sizeof(T)*8) - 1;

            for(int i = 0; i < this->mem_size; i++)
            {
                printf("m[%d]: ", i);
                for(int j = w_s; j >= 0; j--)
                    printf("%d", read_bit(mem[i], j));
                printf("\n");
            }
        }

        template <typename T> void print_mem(T* mem) 
        {
            int w_s = (sizeof(T)*8) - 1;

            for(int i = 0; i < this->mem_size; i++)
            {
                printf("m[%d]: %d\n", i, mem[i]); 
            }
        }

        //others
        template <typename T> void set_rva(T* mem)
        {
            for(uint32_t i = 0; i < this->mem_size; i++)
            {
                mem[i] = this->factor;
            }
        };      
        
        //behavior
        template <typename T> void accum_rva_b(T* mem) {
            uint32_t i;
            printf("ACCUM Behavior\n");
            for(i = 1; i < this->mem_size; i++) 
            {
                mem[0] += mem[i];
            }
        }
        
        template <typename T> void accum_rva(T* mem)
        {
            uint32_t m_s = (uint32_t) mem_size;


            std::vector<T*> B_v, A_v;
            std::vector<bool*> Cr_v;
            std::vector<bool*> Tag_v;

            while(1) {
            //printf("m_s: %d\n", m_s);
            uint32_t op_size = m_s/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);
                        
            for (i = 0; i < op_size; i++) 
            {
                B_v.push_back(&mem[i]); 
                A_v.push_back(&mem[base + i]); 
            	Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
            }
	        
            //printf("-----------------\n");

            if (m_s & 1) {
                //printf("e impar\n");
                A_v.push_back(&mem[m_s-1]); 
                B_v.push_back(new T(0)); 
            	Cr_v.push_back(new bool(0));
        	    Tag_v.push_back(new bool(0));
                op_size++;
                m_s++;
            }
            /*
            printf("DEPOIS DA VER M_S: %d\n", m_s);
            for (i = 0; i < op_size; i++) 
            {
                printf("A: %d - B: %d\n", *A_v.at(i), *B_v.at(i));
            }           
            */

            for(bit = 0; bit < word_size; bit++)
            {
        	    for(pass = 0; pass < 4; pass++)
	            {
            	    for(word = 0; word < op_size; word++)
	                {
        		        this->set_mask(bit, 0, bit, bit);		
	        	        this->set_key(this->lookup_add, pass, bit, 0, bit, bit);
		                this->compare<T>(A_v.at(word), B_v.at(word), NULL, Cr_v.at(word), Tag_v.at(word)); 
                        if(log_mode) {
    	        	        this->tracing_add<T>(bit, pass, word, *Tag_v.at(word), mem);	
                        }	
		                this->write<T>(this->lookup_add, pass, bit, 0, Cr_v.at(word), B_v.at(word), Tag_v.at(word));
	                }
            
                if(this->info_ops_m[op_id]->cycle_w) {
                    this->info_ops_m[op_id]->cycles++;
                    this->info_ops_m[op_id]->cycle_w = false;
                }

                this->info_ops_m[op_id]->cycles++;
	            }	
            }

            /*
            for (i = 0; i < op_size; i++) 
            {
                printf("R-> A: %d - B: %d\n", *A_v.at(i), *B_v.at(i));
            }           
            */
            for (i = 0; i < op_size; i++)
                mem[i] = *B_v.at(i);

            m_s = m_s / 2;
            
            if(m_s == 1)
                break;
            
            B_v.clear();
            A_v.clear();
            Cr_v.clear();
            Tag_v.clear();
            }//while brackets
    	        
            info_ops_m[op_id]->info_plot();
            
        };      
        
        template <typename T> void scount_rva(T* mem) {
            std::vector<T*> B_v, A_v;
            uint32_t op_size = this->mem_size/2;
            this->info_ops_m[op_id]->op_qt = op_size;
            uint32_t base    = op_size;
            uint32_t bit, pass, word, i;
            uint32_t word_size = 8 * sizeof(T);

            //interpretar como se fosse o elemento 0 o minha chave
            //1 ciclo para setar outro pra pesquisar
            key_A = mem[0];
            key_B = 1;
            mask_A = 0xFF;
            mask_B = 1;
            
            for (i = 0; i < op_size; i++) 
            {
                A_v.push_back(&mem[i]); 
                B_v.push_back(&mem[base + i]); 
            }                
            
            for (i = 0; i < op_size; i++) {
                if(*A_v.at(i) == key_A) {
                    *B_v.at(i) = 1;
                } 
            }
/*
            for (i = 0; i < op_size; i++) {
                if((*A_v.at(i) & mask_A) ^ key_A == 0) {
                    *B_v.at(i) = (*B_v.at(i) | (mask_B & key_B));
                } 
            }
*/
            //print_bit_mem<T>(mem);
            for(i = 0; i < op_size; i++)
            {
                mem[i] = *B_v.at(i);
            }            


            //acumulando
            //printf("----------------\n");
            this->mem_size = op_size;
            this->accum_rva(mem);
            //print_bit_mem<T>(mem);
        }

        template <typename T> void copy_rva(T* mem)
        {
            if(this->factor == 1)
                this->copy_rva_inv(mem);
            return;
        };                      

        template <typename T> void copy_rva_inv(T* mem)
        {
            uint32_t op_size = this->mem_size;
             T aux[op_size];
             uint32_t i, j, index_b, index_e;
             /* 
             for(i = 0; i < this->mem_size; i++) {
                printf("%d ", mem[i]);
             }
             printf("\n");
             */
             for(i = op_size; i > 0; i--) {
                 if(mem[i-1] > 0) {
                     index_e = i;
                     break;
                 }
             }

             for(i = 0; i < op_size; i++) {
                 if(mem[i] >  0) {
                     index_b = i;
                     break;
                 }
             }
             
             j = index_b;
             for(i = index_e; i > index_b; i--) {
                 aux[j] = mem[i-1];
                 j++;
             }
          
             for(i = index_b; i < index_e; i++) {
                 mem[i] = aux[i];
             }
            return;
        };                      


        std::map<uint32_t, pass*> lookup_and;
        std::map<uint32_t, pass*> lookup_and_opt;

        std::map<uint32_t, pass*> lookup_or;
        std::map<uint32_t, pass*> lookup_or_opt;

        std::map<uint32_t, pass*> lookup_xor;
        std::map<uint32_t, pass*> lookup_xor_opt;

        std::map<uint32_t, pass*> lookup_not;
        std::map<uint32_t, pass*> lookup_not_opt;

        std::map<uint32_t, pass*> lookup_add;
        std::map<uint32_t, pass*> lookup_mult;
        std::map<uint32_t, pass*> lookup_sub;
        std::map<uint32_t, pass*> lookup_relu;
};
