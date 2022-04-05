#include <iostream>
#include <string>
#include <vector>
#include "inputout.h"
namespace neto
{
    using netochar = wchar_t;
    using netostring = std::basic_string<netochar>;

    _NODISCARD bool verify(netostring&& mensagem, std::vector<netostring> opt1 = { L"YES",L"Yes",L"yes",L"Y",L"y",L"SIM",L"Sim",L"sim",L"S",L"s",L"1",L"true",L"TRUE",L"True" },
        std::vector<netostring> opt2 = { L"NO",L"No",L"no",L"N",L"n",L"NAO",L"Nao",L"nao",L"N",L"n",L"0",L"false",L"False",L"FALSE" }) noexcept;

    void multiple_questions(std::vector<netostring>& results, std::vector<netostring>&& questions_list) noexcept;

    void tagmaker()
    {
        std::vector<netostring> container;
        multiple_questions(container,
            {
                L"Digite o genero musical\n",
                L"Digite a lingua da musica\n",
                L"Digite o nome do artista em ingles caso seja pertinente\n",
                L"Digite o nome da musica em ingles caso seja pertinente\n",
                L"Digite o nome do album na lingua original\n",
                L"Digite o nome do album romanizado\n",
                L"Digite o nome do album em ingles caso seja pertinente\n",
                L"Digite o nome do compositor\n",
                L"Digite o nome do compositor romanizado caso seja pertinente\n",
                L"Digite o ano de lancamento da musica\n",
                L"Digite a decada de lancamento da musica\n",
                L"Digite o nome da empresa/label da musica ou do artista\n",
                L"Digite o nome das pessoas que fizeram gd/storyboard/hitsound do mapa\n",
                L"Digite as tags para identificar o mapping usado, como jump, stream, deathstream, alternate, tech, etc\n",
                L"Digite o nome do artista do background usado\n",
                L"Digite o nome do artista do background romanizado caso seja necessario\n"
            });
        if (verify(netostring(L"A musica pertence a uma banda/grupo?\n")))
        {
            multiple_questions(container,
                {
                    L"Digite o nome dos artistas do grupo no idioma original\n",
                    L"Digite o nome dos artistas do grupo romanizado\n",
                    L"Digite o nome de outras bandas/grupos dos quais os artistas participam/estejam relacionados\n"
                });
        }
        if (verify(netostring(L"O seu mapa tem source?\n")))
        {
            multiple_questions(container,
                {
                    L"Digite o nome da source romanizado\n",
                    L"Digite o nome da source em ingles caso seja pertinente\n",
                    L"Digite o nome do estudio/produtora\n",
                    L"Digite o genero da source\n",
                    L"Digite se a musica se encaixa como opening(op) ending(ed) ou insert song(ost)\n",
                    L"Digite o nome do(a) personagem da musica caso haja\n",
                    L"Digite o nome do(a) personagem romanizado da musica caso haja\n"
                });
        }
        if (verify(netostring(L"Deseja colocar outras tags?\n")))
        {
            multiple_questions(container,
                {
                    L"Digite outras tags que deseja colocar no seu mapa\n"
                });
        }

        // verify for repetitions
        for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
        {
            for (auto iterator2 = container.begin(); iterator2 != container.end(); ++iterator2)
            {
                if (*iterator == *iterator2 && iterator != iterator2)
                {
                    *iterator = netostring ();
                }
            }
        }
        // convert to a string
        netostring temporario;
        for (auto iterator = container.begin(); iterator != container.end(); ++iterator)
        {
            if (*iterator != netostring())
            {
                temporario += *iterator;
                temporario += L" ";
            }

        }
        // verify for max size
        if (temporario.size() > 1019)
        {
            basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(L"Suas tags sao maiores do que o permitido. Por favor delete ou simplifique algumas delas\n", std::wcout);
            basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(L"Você extrapolou em:\n", std::wcout);
            basic_out<int, std::basic_ostream<netochar, std::char_traits<netochar>>>(temporario.size() - 1019, std::wcout);
        }
        // show results
        //output(L"Suas tags sao:\n", temporario, "\n");
        basic_out<netostring,std::basic_ostream<netochar, std::char_traits<netochar>>>(L"Suas tags são:\n",std::wcout);
        basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(temporario, std::wcout);
        basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(L"\n", std::wcout);
        //std::cin.get();
    }

    void multiple_questions(std::vector<netostring>& results, std::vector<netostring>&& questions_list) noexcept
    {
        std::vector<netostring> temp;
        for (auto iterator = questions_list.begin(); iterator != questions_list.end(); ++iterator)
        {
            basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(*iterator, std::wcout);
            temp = input_many<netostring,netochar>(std::wcin);
            if (!temp.empty())
            {
                results.insert(results.end(), temp.begin(), temp.end());
                temp.clear();
            }
        }
    }

    _NODISCARD bool verify(netostring&& mensagem, std::vector<netostring> opt1, std::vector<netostring> opt2) noexcept
    {
        while (true)
        {
            basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(mensagem, std::wcout);
            netostring text = input<netostring,netochar>(std::wcin);
            if (text.empty())
            {
                basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(L"Nenhuma Entrada! Tente novamente.\n", std::wcout);
                continue;
            }
            for (auto it = opt1.begin(); it != opt1.end(); ++it)
            {
                if (text == *it)
                {
                    return true;
                }
            }
            for (auto it = opt2.begin(); it != opt2.end(); ++it)
            {
                if (text == *it)
                {
                    return false;
                }
            }
            text.clear();
            basic_out<netostring, std::basic_ostream<netochar, std::char_traits<netochar>>>(L"Entrada invalida! Tente novamente.\n", std::wcout);
        }
    }
    void run()
    {
        while (true)
        {
            tagmaker();
            if (verify(L"Deseja continuar?") == false)
            {
                break;
            }
        }
    }
}
