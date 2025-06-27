#!/bin/bash

# FEITO PARA RODAR COM BASH.
# ESTE É APENAS UM TEMPLATE/BASE PARA UM FUTURO INSTALADOR E ESTÁ SUJEITO Á MUDANÇAS.
# - @kyanaston

clear
function printnOS {
  echo " "
  echo "      _       _    _      ___  ___"
  echo " _ _ (_)_ __ | |__| |___ / _ \/ __|"
  echo "| ' \| | '  \| '_ \ / -_) (_) \__ \ "
  echo "|_||_|_|_|_|_|_.__/_\___|\___/|___/ "
  echo " "
  echo "-----------------------------------"
  echo " "
}

printnOS
echo "[ 1 ] Iniciar Instalação Assistida"
echo "[ 2 ] Abortar Instalação"
echo " "
read -p "[ installer ]: " OPTION
if [[ "$OPTION" == "1" ]]; then
  # COMANDOS AQUI.
elif [[ "$OPTION" == "2" ]]; then
  break
else
  echo "[-] Abortar instalação: error"
fi
