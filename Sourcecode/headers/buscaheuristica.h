#ifndef BUSCAHEURISTICA_H
#define BUSCAHEURISTICA_H

#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <chrono>
#include <fstream>
#include <cmath>
#include "maquina.h"

namespace BuscaHeuristica
{

    class BuscaHeuristica
    {

        private:
            std::map<std::string, int> parametrosLog;

        protected:
            std::string nome;
            std::vector<ProblemaDistribuicaoTarefas::Maquina*> maquinas;
            std::vector<std::string> log;
            virtual void gerarRegistroLog(const double&, const int&, const int&, const std::string&);

        public:
            BuscaHeuristica(std::string);
            BuscaHeuristica(std::string, std::vector<ProblemaDistribuicaoTarefas::Maquina*>);
            void definirMaquinas(std::vector<ProblemaDistribuicaoTarefas::Maquina*>);
            void definirParametrosLog(const int&, const int&, const int&);
            virtual ProblemaDistribuicaoTarefas::Maquina* getMaquinaCritica();
            virtual void gerarLog(const std::string&);
            virtual void imprimirEstadoMaquinas();
            virtual void executar() = 0;

    };

}

#endif // BUSCAHEURISTICA_H
