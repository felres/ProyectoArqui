#ifndef CPU_64
#define CPU_64
#include <iostream>
#include <queue>
#include <memory>
#include "../CacheDatos/CacheDatos.h"
#include "../CacheInstrucciones/CacheInstrucciones.h"

/**
 * @brief representa el tipo de registro.
 */
typedef int reg_t;
/**
 * @brief representa el tipo de indice para un registro. 
 */
typedef int reg_i; 

struct TCB{
    reg_t PC;
    reg_t reg[32];
    int id; 
    int cant_ciclos; 
};

class CPU{
    private:
        std::queue<TCB> roundRobin_queue;
        std::vector<TCB> hilos_terminados; 
        int quantum; 
        int thread_fin;
        int cant_ciclos = 0;
        int start_clock = 0;
        reg_t reloj = 0; 
        reg_t burst = 0; 
        reg_t reg[32];
        reg_t RL = -1;
        reg_t PC = 0;
        reg_t MAR = 0;
        reg_t thread_id = 0;
        inst_t IR;
        CacheInstrucciones *CI;
        MemoriaPrincipal *MP;
        CacheDatos *CD;
        /**
         * @brief decodifica @ref IR y ejecuta la instruccion.
         * @details a partir de los datos en @ref IR, decodifica cual instruccion debe 
         * correr y llama al metodo correspondiente de la isntruccion
         *  con sus valores correspondientes.
         */
        void decode_execute();
        /**
         * @brief carga los datos del TCB del hilo proximo a ejecutar. 
         * @details desencola el tcb de @ref roundRobin y carga los datos en los parametros del cpu, 
         * esto son los 32 registros, el PC, el id, y la cantidad de ciclos que ha ejecutado ese 
         * hilo. 
         */
        void load_context();
        /**
         * @brief guarda objeto TCB en @ref roundRobing_queue.
         * @details crea un objeto TCB y guarda los datos del cpu en ese TCB, luego lo
         * encola en @ref roundRobin_queue.
         */
        void store_context();
        /**
         * @brief guarda objeto TCB en @ref hilos_terminados. 
         * @details crea un objeto TCB y guarda los datos del cpu en ese TCB, luego los encola
         * en @ref roundRobin_queue, este TCB es de los hilos que ya han termiando su ejecucion. 
         */
        void store_terminated_context();
        /**
         * @brief reg[x1] <- reg[x2] + n
         * @param x1 indice del registro a guardar la suma.
         * @param x2 indice dle registro que suma.
         * @param n inmediato que suma.
         */
        void addi(reg_i x1, reg_i x2, int n);
        /**
         * @brief reg[x1] <- reg[x2] + reg[x3]
         * @param x1 indice del registro a guardar la suma.
         * @param x2 indice del registro que suma.
         * @param x3 indice del registro que suma. 
         */
        void add(reg_i x1, reg_i x2, reg_i x3);
        /**
         * @brief reg[x1] <- reg[x2] - reg[x3]
         * @param x1 indice del registro a guardar la resta.
         * @param x2 indice del registro que resta.
         * @param x3 indice del registro que resta. 
         */
        void sub(reg_i x1, reg_i x2, reg_i x3);
        /**
         * @brief reg[x1] <- reg[x2] * reg[x3]
         * @param x1 indice del registro a guardar la multiplicacion.
         * @param x2 indice del registro que multiplica.
         * @param x3 indice del registro que multiplica. 
         */
        void mul(reg_i x1, reg_i x2, reg_i x3);
        /**
         * @brief reg[x1] <- reg[x2] / reg[x3]
         * @param x1 indice del registro a guardar la division.
         * @param x2 indice del registro dividendo.
         * @param x3 indice del registro divisor. 
         */
        void div(reg_i x1, reg_i x2, reg_i x3);
        /**
         * @brief guarda en el @ref reg[x1] el valor en meoria de la direccion reg[x2] + n.
         * @details utiliza el metodo MP->lw() para pedir el dato.
         * @param x1 indice del registro a guardar el dato.
         * @param x2 indice del registro de la direccion.
         * @param n inmediato sumado a la direccion.
         */
        void lw(reg_i x1, reg_i x2, int n);
        /**
         * @brief guarda en memoria el valor en el registro reg[x1] en la direccion reg[x2] + n.
         * @param x2 indice del registro con la direccion.
         * @param x1 indice del registro con el dato a guardar.
         * @param n inmediate sumado a la direccion.
         */
        void sw(reg_i x2, reg_i x1, int n);
        /**
         * @brief salte a la reiccion @ref PC + n si reg[x1] == reg[x2].
         * @details si el valor de reg[x1] es igual a reg[x2] entonces @ref PC = PC + 4*n.
         * @param x1 indice del registro a comparar. 
         * @param x2 indice dle registor a comparar.
         * @param n inmediato suamdo al PC.
         */
        void beq(reg_i x1, reg_i x2, int n);
        /**
         * @brief salte a la reiccion @ref PC + n si reg[x1] != reg[x2].
         * @details si el valor de reg[x1] es diferente a reg[x2] entonces @ref PC = PC + 4*n.
         * @param x1 indice del registro a comparar. 
         * @param x2 indice dle registor a comparar.
         * @param n inmediato suamdo al PC.
         */
        void bne(reg_i x1, reg_i x2, int n);
        /**
         * @brief guarda en el @ref reg[x1] el valor en meoria de la direccion reg[x2] + n y 
         * asigna el valor de la direccion al registro @ref RL. 
         * @details utiliza el metodo MP->lr() para pedir el dato.
         * @param x1 indice del registro a guardar el dato.
         * @param x2 indice del registro de la direccion.
         * @param n inmediato sumado a la direccion.
         */
        void lr(reg_i x1, reg_i x2);
        /**
         * @brief guarda en memoria el valor en el registro reg[x1] en la direccion reg[x2] + n 
         * @details si el valor de RL es igual a la dirección donde se guardará el dato entonces este 
         * es guardado, si no, no se guarda y el valor del reg[x1] se cambia a 0. 
         * @param x2 indice del registro con la direccion.
         * @param x1 indice del registro con el dato a guardar.
         * @param n inmediate sumado a la direccion.
         */
        void sc(reg_i x2, reg_i x1, int n);
        /**
         * @brief guarda en reg[x1] el valor del @ref PC y asigana a PC += + n.
         * @param x1 indice del registro a donde guardar el PC.
         * @param n inmediato sumado al PC.
         */
        void jal(reg_i x1, int n);
        /**
         * @brief gurda en reg[x1] el valor del @ref PC y asigna a PC = reg[x2] + n.
         * 
         * @param x1 indice del registro a donde guardad el PC.
         * @param x2 indice del registro a sumar con el inmediate.
         * @param n inmediato suamdo con el registro dado para sumar a PC. 
         */
        void jalr(reg_i x1, reg_i x2, int n);


    public: 
        /**
         * @brief Construct a new CPU object
         * @param quantum valor del cuantum con el que se realizan los cambios de constexto. 
         */
        CPU(int quantum);
        /**
         * @brief inicializa la ejecucion de los hilos y sus instrucciones. 
         * @details a partir de los TCB en @ref roudnRobin_queue, carga el contexto de cada hilo,
         * y ejecuta las instrucciones a partir de su PC.  LLeva un conteo de la cantidad de cilos
         * ejecutados en un contesto @ref burst, y cuando @ref burst llega al valor del @ref quantum, 
         * se realiza el cambio de contexto al guardar el TCB del hilo acutal y cargar el del siguiente
         * a ejecutar. Cuando un hilo termina, su TCB es guardado en @ref hilos_terminados. El cpu deja
         * de ejecutar instrucciones cuando la cola @ref roundRobing_queue ese vacia. 
         */
        void cpu_init();
        /**
         * @brief carga de memoria las isntrucciones de los hilos.
         * @details por cada hilo, pide a @ref MemoriaPrincipal que carge las intrucciones 
         * de ese hilo y guarda en un TCB el PC donde comienza su priemra isntrucciones, luego 
         * encola este TCB en @ref roundRobing_queue. 
         * @param cant_hilos cantidad de hilos con los que el programa correra. 
         */
        void load_memory(int cant_hilos);
        /**
         * @brief imprime datos de los hilos que corrieron.
         * @details imprimri los registros y cantidad de ciclos que duro correindo de cada hilo.
         */
        void printHilos();
        /**
         * @brief instancia los punteros de los objetos de memoria.
         * @param CI cache instrucciones a utilizar.
         * @param MP memoria principal a utilizar. 
         * @param CD cache de datos a utilizar. 
         */
        void set_ptr(CacheInstrucciones * CI, MemoriaPrincipal *MP, CacheDatos *CD);


};
#endif