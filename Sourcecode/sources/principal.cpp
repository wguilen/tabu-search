#include <iostream>
#include <ctime>
#include <vector>
#include <cmath>
#include "maquina.h"
#include "buscaheuristica.h"
#include "primeiramelhora.h"
#include "tabu.h"

using namespace std;

const int TOTAL_EXECUCAO = 10;
const string ARQUIVO_LOG = "C:\\Users\\Wilhelm\\Desktop\\\BuscaHeuristica.log";

void instanciarTarefas(vector<ProblemaDistribuicaoTarefas::Maquina*>&, int);

int main()
{
    srand(time(NULL));

    vector<int> totalMaquinas = { 10, 20, 50 };
    vector<float> totalTarefas = { 1.5, 2.0 };

    vector<ProblemaDistribuicaoTarefas::Maquina*> maquinas;
    BuscaHeuristica::BuscaHeuristica* primeiraMelhora = new BuscaLocalMonotona::PrimeiraMelhora();
    BuscaHeuristica::BuscaHeuristica* tabu = new BuscaLocalNaoMonotona::Tabu();

    for (auto qtdMaquinas : totalMaquinas)
    {
        // Instancia as novas máquinas
        for (size_t i = maquinas.size(); i < qtdMaquinas; ++i)
        {
            ProblemaDistribuicaoTarefas::Maquina* maquina = new ProblemaDistribuicaoTarefas::Maquina((int)(i + 1));
            maquinas.push_back(maquina);
        }

        for (auto qtdTarefas : totalTarefas)
        {
            // Calcula o total de tarefas da instância de execução
            int qtdTarefasInstanciar = (int)(round(powf(qtdMaquinas, qtdTarefas)));

            // Executa as buscas
            for (int i = 1; i <= TOTAL_EXECUCAO; ++i)
            {
                // BLM: PrimeiraMelhora
                instanciarTarefas(maquinas, qtdTarefasInstanciar);
                primeiraMelhora->definirMaquinas(maquinas);
                primeiraMelhora->definirParametrosLog(qtdMaquinas, qtdTarefasInstanciar, i);
                primeiraMelhora->executar();
                primeiraMelhora->gerarLog(ARQUIVO_LOG);

                // BLNM: Tabu
                instanciarTarefas(maquinas, qtdTarefasInstanciar);
                tabu->definirMaquinas(maquinas);
                ((BuscaLocalNaoMonotona::Tabu*)tabu)->definirReplicacao(i - 1);
                ((BuscaLocalNaoMonotona::Tabu*)tabu)->definirNumeroTarefas(qtdTarefasInstanciar);
                tabu->definirParametrosLog(qtdMaquinas, qtdTarefasInstanciar, i);
                tabu->executar();
                tabu->gerarLog(ARQUIVO_LOG);

                // Imprime o resultado na tela
                #ifdef _DEBUG
                    cout << "Exec -- Machines: " << qtdMaquinas << " - Tasks: " << qtdTarefasInstanciar << endl << endl;
                    tabu->imprimirEstadoMaquinas();
                    cout << endl;
                #endif
            }
        }
    }

    // Libera a memória utilizada
    maquinas.clear();
    maquinas.shrink_to_fit();
    delete primeiraMelhora;
    delete tabu;

    return 0;
}

void instanciarTarefas(vector<ProblemaDistribuicaoTarefas::Maquina*>& maquinas, int quantidade)
{
    // Limpa a lista de tarefas das máquinas existentes, caso haja
    for (auto maquina : maquinas)
    {
        maquina->limparTarefas();
    }

    // Instancia as tarefas na primeira máquina
    maquinas.front()->instanciarTarefas(quantidade);
}
