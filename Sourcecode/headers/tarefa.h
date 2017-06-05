#ifndef TAREFA_H
#define TAREFA_H

namespace ProblemaDistribuicaoTarefas
{

    class Tarefa
    {

        private:
            int id;
            int tempoExecucao;

        public:
            Tarefa(int, int);
            int getId();
            int getTempoExecucao();

    };

}

#endif // TAREFA_H
