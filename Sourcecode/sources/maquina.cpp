#include "maquina.h"
#include <iostream>

namespace ProblemaDistribuicaoTarefas
{

    // Construtores & Destrutores

    Maquina::Maquina(int id) : id(id) {}

    Maquina::~Maquina()
    {
        limparTarefas();
    }


    // Métodos

    int Maquina::getId()
    {
        return id;
    }

    void Maquina::adicionarTarefa(Tarefa* tarefa)
    {
        tarefas.push_back(tarefa);
    }

    void Maquina::instanciarTarefas(int total)
    {
        limparTarefas();

        for (int i = 1; i <= total; ++i)
        {
            Tarefa* tarefa = new Tarefa(i, rand() % 100 + 1);
            adicionarTarefa(tarefa);
        }
    }

    void Maquina::transferirTarefa(Tarefa* tarefa, Maquina* maquinaDestino)
    {
        maquinaDestino->adicionarTarefa(tarefa);

        std::vector<Tarefa*>::iterator it = std::find_if(tarefas.begin(), tarefas.end(), [tarefa](Tarefa* t) -> bool
        {
            return t->getId() == tarefa->getId();
        });

        tarefas.erase(it);
    }

    void Maquina::transferirUltimaTarefa(Maquina* maquinaDestino)
    {
        maquinaDestino->adicionarTarefa(tarefas.back());
        tarefas.pop_back();
    }

    const std::vector<Tarefa*> Maquina::obterTarefas()
    {
        return tarefas;
    }

    void Maquina::limparTarefas()
    {
        for (auto it = tarefas.begin(); it != tarefas.end(); ++it)
        {
            delete *it;
        }

        tarefas.clear();
        tarefas.shrink_to_fit();
    }

    size_t Maquina::calcularTotalTarefas()
    {
        return tarefas.size();
    }

    int Maquina::calcularTempoExecucao()
    {
        int tempoExecucao = 0;

        for (auto tarefa : tarefas)
        {
            tempoExecucao += tarefa->getTempoExecucao();
        }

        return tempoExecucao;
    }

}
