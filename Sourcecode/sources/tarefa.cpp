#include "tarefa.h"

namespace ProblemaDistribuicaoTarefas
{

    Tarefa::Tarefa(int id, int tempoExecucao) : id(id), tempoExecucao(tempoExecucao)
    {
    }

    int Tarefa::getId()
    {
        return id;
    }

    int Tarefa::getTempoExecucao()
    {
        return tempoExecucao;
    }

}

