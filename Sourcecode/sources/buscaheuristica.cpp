#include "buscaheuristica.h"

namespace BuscaHeuristica
{

    // Construtores

    BuscaHeuristica::BuscaHeuristica(std::string nome) : nome(nome) {}
    BuscaHeuristica::BuscaHeuristica(std::string nome, std::vector<ProblemaDistribuicaoTarefas::Maquina*> maquinas): nome(nome), maquinas(maquinas) {}


    // Métodos

    void BuscaHeuristica::definirMaquinas(std::vector<ProblemaDistribuicaoTarefas::Maquina*> maquinas)
    {
        this->maquinas = maquinas;
    }

    void BuscaHeuristica::definirParametrosLog(const int& maquinas, const int& tarefas, const int& replicacao)
    {
        parametrosLog.clear();
        parametrosLog.insert(std::pair<std::string, int>("maquinas", maquinas));
        parametrosLog.insert(std::pair<std::string, int>("tarefas", tarefas));
        parametrosLog.insert(std::pair<std::string, int>("replicacao", replicacao));
    }

    ProblemaDistribuicaoTarefas::Maquina* BuscaHeuristica::getMaquinaCritica()
    {
        ProblemaDistribuicaoTarefas::Maquina* maquinaCritica { nullptr };

        for (ProblemaDistribuicaoTarefas::Maquina* maquina : maquinas)
        {
            if (nullptr == maquinaCritica ||
                    maquinaCritica->calcularTempoExecucao() < maquina->calcularTempoExecucao())
            {
                maquinaCritica = maquina;
            }
        }

        return maquinaCritica;
    }

    void BuscaHeuristica::gerarRegistroLog(const double& tempo, const int& iteracoes,
                                           const int& valor, const std::string& parametro)
    {
        std::stringstream registro;

        registro << nome;
        registro << "," << parametrosLog.at("tarefas");
        registro << "," << parametrosLog.at("maquinas");
        registro << "," << parametrosLog.at("replicacao");
        registro << "," << tempo;
        registro << "," << iteracoes;
        registro << "," << valor;
        registro << "," << parametro;

        log.push_back(registro.str());
    }

    void BuscaHeuristica::gerarLog(const std::string& arquivo)
    {
        std::ofstream arquivoSaida;
        arquivoSaida.open(arquivo, std::ios_base::app);

        for (std::string registro : log)
        {
            arquivoSaida << registro << std::endl;
        }

        arquivoSaida.close();
        log.clear();
    }

    void BuscaHeuristica::imprimirEstadoMaquinas()
    {
        std::cout << "Machine\tTasks\tProcTime" << std::endl;

        for (auto maquina : maquinas)
        {
            std::cout << maquina->getId() << "\t" << maquina->calcularTotalTarefas() << "\t" << maquina->calcularTempoExecucao() << std::endl;
        }
    }

}

