#ifndef MAQUINA_H
#define MAQUINA_H

#include <algorithm>
#include <cstdlib>
#include <vector>
#include "tarefa.h"

namespace ProblemaDistribuicaoTarefas
{

    class Maquina
    {

        private:
            int id;
            std::vector<Tarefa*> tarefas;

        public:
            Maquina(int);
            ~Maquina();
            int getId();
            void adicionarTarefa(Tarefa*);
            void instanciarTarefas(int);
            void limparTarefas();
            size_t calcularTotalTarefas();
            int calcularTempoExecucao();
            const std::vector<Tarefa*> obterTarefas();
            void transferirTarefa(Tarefa*, Maquina*);
            void transferirUltimaTarefa(Maquina*);

    };

}


#endif // MAQUINA_H
