#include <iostream>
#include <string>
#include <vector>
#include "inputout.h"

_NODISCARD bool verify(std::string&& mensagem, std::vector<std::string>&& opt1, std::vector<std::string>&& opt2) noexcept;

void multiple_questions(std::vector<std::string>& results,std::vector<std::string>&& questions_list) noexcept;

int main()
{
    std::vector<std::string> container;
    multiple_questions(container,
        {
            "Digite o genero musical\n",
            "Digite a lingua da musica\n",
            "Digite o nome do artista em ingles caso seja pertinente\n",
            "Digite o nome da musica em ingles caso seja pertinente\n",
            "Digite o nome do album na lingua original\n",
            "Digite o nome do album romanizado\n",
            "Digite o nome do album em ingles caso seja pertinente\n",
            "Digite o nome do compositor\n",
            "Digite o nome do compositor romanizado caso seja pertinente\n",
            "Digite o ano de lancamento da musica\n",
            "Digite a decada de lancamento da musica\n",
            "Digite o nome da empresa/label da musica ou do artista\n",
            "No caso de uma banda, digite o nome dos artistas do grupo no idioma original\n",
            "No caso de uma banda, digite o nome dos artistas do grupo romanizado\n",
            "Digite o nome das pessoas que fizeram gd/storyboard/hitsound do mapa\n",
            "Digite as tags para identificar o mapping usado, como jump, stream, deathstream, alternate, tech, etc\n",
            "Digite o nome do artista do background usado\n",
            "Digite o nome do artista do background romanizado caso seja necessario\n" 
        });
    if (verify(std::string("O seu mapa tem source?\n"),
        {"YES","Yes","yes","Y","y","SIM","Sim","sim","S","s","1","true","TRUE","True"},
        {"NO","No","no","N","n","NAO","Nao","nao","N","n","0","false","False","FALSE"}))
    {
        multiple_questions(container,
            {
                "Digite o nome da source romanizado\n",
                "Digite o nome da source em ingles caso seja pertinente\n",
                "Digite o nome do estudio/produtora\n",
                "Digite o genero da source\n",
                "Nigite se a musica se encaixa como opening(op) ending(ed) ou insert song(ost)\n",
                "Digite o nome do(a) personagem da musica caso haja\n",
                "Digite o nome do(a) personagem romanizado da musica caso haja\n"
            });
    }
    // verify for repetitions
    for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
    {
        for (auto iterator2 = container.begin(); iterator2 != container.end(); ++iterator2)
        { 
            if (*iterator == *iterator2 && iterator != iterator2)
            {
                *iterator = "";
            }
        }
    }
    // convert to a string
    std::string temporario;
    for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
    {
        if (*iterator != std::string())
        {
            temporario += *iterator;
            temporario += " ";
        }
   
    }
    // verify for max size
    if (temporario.size() > 1019)
    {
        output("Suas tags sao maiores do que o permitido (Você extrapolou em ", temporario.size() - 1019, "). Por favor delete ou simplifique algumas delas\n");
    }
    // show results
    output("Suas tags sao:\n",temporario);
    std::cin.get();
}

void multiple_questions(std::vector<std::string>& results,std::vector<std::string>&& questions_list) noexcept
{
    std::vector<std::string> temp;
    for (auto iterator = questions_list.begin(); iterator != questions_list.end(); ++iterator)
    {
        output(*iterator);
        temp = input_many<std::string>();
        if (!temp.empty())
        {
            results.insert(results.end(), temp.begin(), temp.end());            
            temp.clear();
        }
    }
}

_NODISCARD bool verify(std::string&& mensagem, std::vector<std::string>&& opt1, std::vector<std::string>&& opt2) noexcept
{
    while (true)
    {
        output(mensagem);
        std::string text = input<std::string>();
        if(text.empty())
        {
            output("Nenhuma Entrada! Tente novamente.\n");
            continue;
        }
        for(auto it = opt1.begin(); it != opt1.end(); ++it)
        {
            if (text == *it)
            {
                return true;
            }    
        }
        for(auto it = opt2.begin(); it != opt2.end(); ++it)
        {
            if (text == *it)
            {
                return false;
            }    
        }
        text.clear();
        output("Entrada inválida! Tente novamente.\n");
    }
}
