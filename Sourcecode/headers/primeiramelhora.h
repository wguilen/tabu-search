#ifndef PRIMEIRAMELHORA_H
#define PRIMEIRAMELHORA_H

#include "buscaheuristica.h"

namespace BuscaLocalMonotona
{
    class PrimeiraMelhora: public BuscaHeuristica::BuscaHeuristica
    {

        private:
            ProblemaDistribuicaoTarefas::Maquina* buscarProximaMaquina(ProblemaDistribuicaoTarefas::Maquina*);
        public:
            PrimeiraMelhora();
            virtual void executar();

    };
}

#endif // PRIMEIRAMELHORA_H
