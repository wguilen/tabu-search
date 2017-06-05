#ifndef TABU_H
#define TABU_H

#include "buscaheuristica.h"

namespace BuscaLocalNaoMonotona
{

    class Tabu: public BuscaHeuristica::BuscaHeuristica
    {

        private:
            int numeroTarefas;
            int replicacao;
            const std::vector<float> alfa { 0.01f, 0.02f, 0.03f, 0.04f, 0.05f, 0.06f, 0.07f, 0.08f, 0.09f };
            std::map<int, int> listaTabu; // Chave: ID da tarefa, Valor: Iteração final (para sair da lista)
            void atualizarListaTabu();

        public:
            Tabu();
            void definirNumeroTarefas(int);
            void definirReplicacao(int);
            virtual void executar();

    };
}

#endif // TABU_H
