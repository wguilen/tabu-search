/*
 * https://en.wikipedia.org/wiki/Tabu_search
 * http://www.codeproject.com/Questions/145405/Tabu-Search-implementation
 * https://www.researchgate.net/publication/2430872_A_C_Implementation_of_Tabu_Search_for_k-Cardinality_Tree_Problem_Based_on_Generic_Programming_and_Component_Reuse
 */

#include "tabu.h"

namespace BuscaLocalNaoMonotona
{

    // Construtores

    Tabu::Tabu() : BuscaHeuristica("BLNM-Tabu") {}


    // Métodos

    void Tabu::definirNumeroTarefas(int numeroTarefas)
    {
        this->numeroTarefas = numeroTarefas;
    }

    void Tabu::definirReplicacao(int replicacao)
    {
        this->replicacao = replicacao;
    }

    void Tabu::atualizarListaTabu()
    {
        for (auto it = listaTabu.begin(); it != listaTabu.end();)
        {
            it->second = it->second - 1;

            if (it->second == 0)
            {
                listaTabu.erase(it++);
            }
            else
            {
                ++it;
            }
        }
    }

    void Tabu::executar()
    {
        listaTabu.clear();
        int iteracoes = 0;

        // Variáveis de log
        int iteracoesTotais = 0;
        std::chrono::high_resolution_clock::time_point tempoInicio = std::chrono::high_resolution_clock::now();

        // Calcula o tempo que as tarefas deverão permanecer na lista tabu
        float alfa = -1.0f;
        int tempo = -1;

        if (replicacao < this->alfa.size())
        {
            alfa = this->alfa[replicacao];
        }
        else
        {
            alfa = this->alfa[std::rand() % this->alfa.size()];
        }

        tempo = (int)(std::ceil(alfa * numeroTarefas));

        ProblemaDistribuicaoTarefas::Maquina* maquinaCritica = getMaquinaCritica();
        int makespan = maquinaCritica->calcularTempoExecucao();

        do
        {
            ++iteracoes;

            atualizarListaTabu();

            ProblemaDistribuicaoTarefas::Tarefa* tarefaCandidata = nullptr;

            for (ProblemaDistribuicaoTarefas::Tarefa* tarefa : maquinaCritica->obterTarefas())
            {
                if (0 == listaTabu.count(tarefa->getId()) &&
                        (nullptr == tarefaCandidata || tarefa->getTempoExecucao() < tarefaCandidata->getTempoExecucao()))
                {
                    tarefaCandidata = tarefa;
                }
            }

            if (nullptr == tarefaCandidata)
            {
                continue;
            }

            for (ProblemaDistribuicaoTarefas::Maquina* maquina : maquinas)
            {
                if ((maquina->calcularTempoExecucao() + tarefaCandidata->getTempoExecucao()) < makespan)
                {
                    // Transfere a tarefa
                    maquinaCritica->transferirTarefa(tarefaCandidata, maquina);

                    // Coloca-a na lista tabu
                    // int tempo = (int)(std::roundf(alfa[std::rand() % alfa.size()] * numeroTarefas));
                    listaTabu.insert(std::make_pair(tarefaCandidata->getId(), tempo));

                    // Obtém a próxima máquina crítica e atualiza o makespan
                    maquinaCritica = getMaquinaCritica();
                    makespan = maquinaCritica->calcularTempoExecucao();

                    // Reinicia o contador de iteracões para o critério de parada
                    // e incrementa o contador de iteracões totais (que levaram à uma melhora
                    // no makespan da máquina crítica)
                    iteracoes = 0;
                    ++iteracoesTotais;

                    break;
                }
            }
        } while (iteracoes < 1000);

        // Geração do registro de log
        std::chrono::high_resolution_clock::time_point tempoTermino = std::chrono::high_resolution_clock::now();
        auto tempoExecucao = std::chrono::duration_cast<std::chrono::milliseconds>(tempoTermino - tempoInicio).count();
        gerarRegistroLog(tempoExecucao, iteracoesTotais, maquinaCritica->calcularTempoExecucao(), std::to_string(alfa));
    }

}

