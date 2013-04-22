PROGRAMA="./sort"
GERAR="./gerarNumeros"
METODOS="heap merge quick"
SAIDA="teste"
NUMEROS=1000`printf "%0$1d"`
arquivo="numeros1000e$1"
declare -A RESULTADOS

function clean() {
for resultado in ${RESULTADOS[@]}
do
	> $resultado
done
}

function init() {
for metodo in $METODOS
do
	RESULTADOS[$metodo]=$SAIDA`echo -n "${metodo:0:1}" | tr "[:lower:]" "[:upper:]"``echo -n ${metodo:1}`
done
}

function executaTestes() {
for metodo in $METODOS
do
	resultado="${RESULTADOS["$metodo"]}"
	
	echo "$arquivo" | tee -a $resultado
	echo "$metodo"
	
	for teste in {1..50}
	do
		echo "${teste}.:" | tee -a $resultado
		$GERAR $NUMEROS $arquivo
		$PROGRAMA $metodo $arquivo >> $resultado
	done
	
	echo "-----------------------" >> $resultado
done
}

init
if [ "$2" = "novo" ]
then
	clean
fi
executaTestes
