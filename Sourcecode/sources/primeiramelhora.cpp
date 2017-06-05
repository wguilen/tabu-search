#include "primeiramelhora.h"

namespace BuscaLocalMonotona
{

    // Construtores

    PrimeiraMelhora::PrimeiraMelhora() : BuscaHeuristica("BLM-PrimeiraMelhora") {}


    // Métodos

    ProblemaDistribuicaoTarefas::Maquina* PrimeiraMelhora::buscarProximaMaquina(ProblemaDistribuicaoTarefas::Maquina* maquina)
    {
        int tempoUltimaTarefa = maquina->obterTarefas().back()->getTempoExecucao();

        for (ProblemaDistribuicaoTarefas::Maquina* m : maquinas)
        {
            if ((m->getId() != maquina->getId()) &&
                    ((tempoUltimaTarefa + m->calcularTempoExecucao()) < maquina->calcularTempoExecucao()))
            {
                return m;
            }
        }

        return nullptr;
    }

    void PrimeiraMelhora::executar()
    {
        // Variáveis de log
        int iteracoes = 0;
        std::chrono::high_resolution_clock::time_point tempoInicio = std::chrono::high_resolution_clock::now();

        // Execução do algoritmo de busca
        ProblemaDistribuicaoTarefas::Maquina* maquina = getMaquinaCritica();

        do
        {
            ProblemaDistribuicaoTarefas::Maquina* proximaMaquina = buscarProximaMaquina(maquina);

            // Se a próxima máquina não existir, significa que não há como melhorar
            //  utilizando a PrimeiraMelhora
            if (nullptr == proximaMaquina)
            {
                break;
            }

            // Transfere a última tarefa para a máquina vizinha
            maquina->transferirUltimaTarefa(proximaMaquina);
            maquina = getMaquinaCritica();

            // Variáveis de log
            ++iteracoes;
        } while (true);

        // Geração do registro de log
        std::chrono::high_resolution_clock::time_point tempoTermino = std::chrono::high_resolution_clock::now();
        auto tempoExecucao = std::chrono::duration_cast<std::chrono::milliseconds>(tempoTermino - tempoInicio).count();
        gerarRegistroLog(tempoExecucao, iteracoes, maquina->calcularTempoExecucao(), "N/A");
    }

}

