#!/bin/env bash


# ARQUIVO COM LISTA DE LINKS PARA PACOTES

Listurl=https://github.com/jox0101011/nimbleOS/nimblepmlist

# DIRETORIOS ESSENCIAIS

Sourcedir=/nimble
Packagedir=$Sourcedir/packages

# FUNCOES

function cleanuptrigger {
	echo "Executando triggers de limpeza..."
	rm -rf $Packagedir > /dev/null
	sync
}

function setuppackagemanager {
	echo "Criando diretorios necessarios..."
	mkdir $Sourcedir
	mkdir $Packagedir
	chown root:root $Sourcedir
	chown root:root $Packagedir
}

function downloadlist {
	rm $Sourcedir/nimblepmlist
	wget -P $Sourcedir $Listurl
}

function packagemanagerhelp {
	echo "pm update | Atualiza a lista de pacotes."
	echo "pm setup | Cria e configura diretorios necessarios."
	echo "pm help | Mostra essa mensagem."
}

# CODIGO PARA GERENCIADOR

if [ "$EUID" -ne 0 ]; then
  echo "error: Você não pode executar essa operação a não ser que seja root."
  exit 1
fi

if [ "$1" == "update" || "$1" == "-Sy" ]; then
	"Atualizando lista de pacotes..."
	downloadlist
elif [ "$1" == "setup" || "$1" == "-C" ]; then
	setuppackagemanager
elif [ "$1" == "help" || "$1" == "-h" ]; then
	packagemanagerhelp
	else
	echo "Argumento invalido, use o argumento help para ver as opcoes disponiveis."
fi
