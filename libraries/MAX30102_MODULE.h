
#ifndef MAX30102_MODULE
#define MAX30102_MODULE

class MAX30102_Module{
    public:
        MAX30102_Module();

        void setClock(unsigned long clock);
        void initialize_lcd();
        bool initialize_module();
        bool hasNewData();
        void readData();

        void lib_max30102(void);
    
};

#endif
