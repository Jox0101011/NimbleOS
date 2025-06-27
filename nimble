#!/bin/sh
# !!! C U I D A D O !!! ISSO VAI DESTRUIR TODO O SEU DISCO, TESTE APENAS EM AMBIENTES CONTROLADOS
# Feito especificamente para Alquimist Shell, mas deve funcionar perfeitamente com outros shells.
# Faça alteraçoes com cuidado para nao quebrar o script.
# - Kyanaston

case "$1" in

install)
  echo "Especifique a partiçao para a raiz (Ex.: /dev/sda2)"
  lsblk
  read particao
  echo "Tem Certeza? isso vai DESTRUIR todos os dados na partiçao (s/n)"
  read confirmacao
  case "$confirmacao" in

  s)
    umount /mnt >/dev/null
    mount "$disco" /mnt
    rm -rf /mnt/* >/dev/null
    cp /* -r /mnt >/dev/null
    umount /mnt >/dev/null
    echo "Especifique a particao EFI (Ex.: /dev/sda1)"
    exit 0
    ;;

  n)
    echo "Abortando..."
    exit 0
    ;;

  esac
  ;;

version)
  echo "1.0"
  ;;

*)
  echo "Argumento invalido, aqui está as opçoes:"
  echo "nimble install | Instala o sistema"
  echo "nimble version | Mostra a versao do instalador."
  ;;

esac
