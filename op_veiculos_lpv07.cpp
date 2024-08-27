#include <iostream>
#include <iomanip>

class Veiculo {
private:
    double precoLitro;
    double capacidadeMaxTanque;
    double consumoKmPorLitro;
    double quantidadeLitrosNoTanque;
    double quilometragem;
    double totalGasto;

public:
    // Construtor com parâmetros
    Veiculo(double precoLitro, double capacidadeMaxTanque, double consumoKmPorLitro, double quilometragem) 
        : precoLitro(precoLitro), capacidadeMaxTanque(capacidadeMaxTanque), 
          consumoKmPorLitro(consumoKmPorLitro), quilometragem(quilometragem), 
          totalGasto(0.0) {
        quantidadeLitrosNoTanque = capacidadeMaxTanque * 0.10; // Inicializa com 10% da capacidade
    }

    // Construtor padrão
    Veiculo() 
        : precoLitro(0.0), capacidadeMaxTanque(0.0), consumoKmPorLitro(0.0), 
          quantidadeLitrosNoTanque(0.0), quilometragem(0.0), totalGasto(0.0) {}

    // Destrutor
    ~Veiculo() {
        std::cout << "Destrutor chamado. Atributos atuais:\n";
        std::cout << "Preço do Litro: " << precoLitro << "\n";
        std::cout << "Capacidade Máxima do Tanque: " << capacidadeMaxTanque << "\n";
        std::cout << "Consumo: " << consumoKmPorLitro << "\n";
        std::cout << "Quantidade de Litros no Tanque: " << quantidadeLitrosNoTanque << "\n";
        std::cout << "Quilometragem: " << quilometragem << "\n";
        std::cout << "Total Gasto: " << totalGasto << "\n";
    }

    // Métodos get e set
    double getPrecoLitro() const { return precoLitro; }
    void setPrecoLitro(double preco) { precoLitro = preco; }

    double getCapacidadeMaxTanque() const { return capacidadeMaxTanque; }
    void setCapacidadeMaxTanque(double capacidade) { capacidadeMaxTanque = capacidade; }

    double getConsumoKmPorLitro() const { return consumoKmPorLitro; }
    void setConsumoKmPorLitro(double consumo) { consumoKmPorLitro = consumo; }

    double getQuantidadeLitrosNoTanque() const { return quantidadeLitrosNoTanque; }
    void setQuantidadeLitrosNoTanque(double quantidade) { quantidadeLitrosNoTanque = quantidade; }

    double getQuilometragem() const { return quilometragem; }
    void setQuilometragem(double quilometragem) { this->quilometragem = quilometragem; }

    double getTotalGasto() const { return totalGasto; }
    void setTotalGasto(double total) { totalGasto = total; }

    // Método para abastecimento
    double abastecimento(double litros) {
        double valorTotal = litros * precoLitro;
        double valorImposto = valorTotal * 0.025;
        valorTotal += valorImposto;

        if (quantidadeLitrosNoTanque + litros > capacidadeMaxTanque) {
            std::cout << "Capacidade do tanque excedida. Abastecimento cancelado.\n";
            return 0.0;
        }

        quantidadeLitrosNoTanque += litros;
        Custos(valorTotal);
        return valorTotal;
    }

    // Método para adicionar ao total gasto
    void Custos(double valor) {
        totalGasto += valor;
    }

    // Método para calcular a autonomia
    double autonomia() const {
        return quantidadeLitrosNoTanque * consumoKmPorLitro;
    }

    // Método para verificar se é possível percorrer a distância
    bool percorrerDistancia(double distancia) const {
        return distancia <= autonomia();
    }

    // Método para realizar o deslocamento
    void deslocamento(double distancia) {
        if (percorrerDistancia(distancia)) {
            double litrosConsumidos = distancia / consumoKmPorLitro;
            quantidadeLitrosNoTanque -= litrosConsumidos;
            quilometragem += distancia;
        } else {
            std::cout << "Distância maior do que a autonomia. Deslocamento não realizado.\n";
        }
    }
};

// Função principal para testar a classe
int main() {
    // Criando um objeto do tipo Veiculo
    Veiculo carro(6.5, 50, 12, 10000);

    // Exibindo informações iniciais
    std::cout << "Autonomia inicial: " << carro.autonomia() << " km\n";

    // Realizando um abastecimento
    double valorAbastecimento = carro.abastecimento(20);
    std::cout << "Valor do abastecimento: R$ " << std::fixed << std::setprecision(2) << valorAbastecimento << "\n";

    // Verificando nova autonomia
    std::cout << "Autonomia após abastecimento: " << carro.autonomia() << " km\n";

    // Tentando percorrer uma distância
    double distancia = 100;
    if (carro.percorrerDistancia(distancia)) {
        std::cout << "Deslocando " << distancia << " km...\n";
        carro.deslocamento(distancia);
    } else {
        std::cout << "Não é possível percorrer a distância solicitada.\n";
    }

    // Exibindo informações finais
    std::cout << "Quilometragem atual: " << carro.getQuilometragem() << " km\n";
    std::cout << "Quantidade de litros no tanque: " << carro.getQuantidadeLitrosNoTanque() << " L\n";
    std::cout << "Total gasto em abastecimentos: R$ " << carro.getTotalGasto() << "\n";

    return 0;
}
