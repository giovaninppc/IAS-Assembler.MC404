# Scrpit: Testador para labs de mc102 
#!/bin/bash
 
j=15
baixado=1
if [  -d "TEST" ]; then
    rm -fr TEST
fi
mkdir TEST
if [  -d "IN" ]; then
    cd IN
    j=$(ls -l | grep -v ^l | wc -l)
    j=$[$j-1]
    cp *.in ../TEST
    cd ../RES
    cp *.res ../TEST
    cd ..
    cp *.h *.c TEST
    cd TEST

else
    cp *.in TEST
    cp *.res TEST
    cp *.c   TEST
    cd TEST
fi
trap 'rm -rf ../TEST ; echo "NÃO ME MATE!!!" ; exit'   1 2 3 15 

#Compila o 'arquivo.c'

#Mudar aqui o $lab no fim por *.c
gcc -std=c99 -pedantic -Wall -g -o ias-as *.c  
#Caso de Erro de Compilacao
if [ $? -ne 0 ] ; then
    trap 'rm -rf ../TEST ; echo "NÃO ME MATE!!!" ; exit'   1 2 3 15 
    echo -e "\e[93mERRO NA COMPILAÇÃO,ESSE \e[4mNEGOCIO\e[24m NAO COMPILA"
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
    if [  -d "TEST" ]; then
        rm -fr TEST
    fi
    exit
fi
clear
function echo_erro {
    echo -e "\e[91m\e[4m\e[5mOs erros até o Teste $i  "
    echo -e "Total de erros:$erros \e[0m"
}
#Roda os Testes


echo "Executando os testes..."
erros=0
trap ' Organiza ; clear ; echo_erro  ; exit'  1 2 3 15 
for (( i=0; i<$j; i++ )); do
    arq="arq$(printf '%02d' $i)"
    ./ias-as $arq.in > $arq.out

    #Compara com os arquivos da Resolucao
    cmp=$(diff $arq.res $arq.out)
    if [ "$cmp" != "" ]; then
        echo -e "\e[93m----Teste $i----"
    else
        echo -e "\e[92m----Teste $i----"
    fi
    if [ "$cmp" != "" ]; then
        echo
        echo -e "\e[93m"
        echo "========================================="
        echo "Erro encontrado com a entrada '$arq.in':"
        echo
        echo -e "\e[91m\e[4m\e[5m\tSAÍDA ESPERADA(SuSy) \t-\t-\t-\t-\t-\tSAÍDA DO SEU PROGRAMA\e[0m"
        diff -yt   $arq.res $arq.out 
        echo -e "\e[93m"
        echo "========================================="
        erros=$(($erros+1))
    fi
done

echo
echo -e "\e[91m\e[4m\e[5mTotal de erros lógicos:$erros \e[0m"

if [ "$baixado" = 1 ]
then
    cd ..
fi
#Verifica se Existe a pasta TEST
if [  -d "TEST" ]; then
    rm -fr TEST
else
    mkdir OUT > /dev/null 2>&1
    mv *.out OUT  
    mkdir IN > /dev/null 2>&1
    mv *.in IN  
    mkdir RES > /dev/null 2>&1
    mv *.res RES  
fi
echo
trap 'rm *.out -f ; exit'  1 2 3 15 
echo -e "\e[93m Deu certo??"
read resp
#Entra no site do SuSy caso o usuario responda sim
if [ "$resp" = sim ] || [ "$resp" = s ]
then
    echo -e "\e[5m\e[1m\e[96m\e[4m PARABÉNS\e[25m\e[21m\e[24m, Agora eh soh submeter!"
    echo -e "\e[92mVocê vai submeter agora??"
    read resp2
    if [ "$resp2" = sim ] || [ "$resp2" = s ]
    then
        trap 'rm nohup* -f ; exit' 0 1 2 3 15  
        nohup firefox https://susy.ic.unicamp.br:9999/mc102ijkl/$num & > /dev/null
        rm nohup.out -f
        clear
    fi
else
    echo -e "\e[93mTente Outra Vez, ainda da tempo!"
fi
exit 0
