n=('' E4 B3 G3 D3 A2 E2)

while read -n1 -p 'string? ' i
do
	case $i in 
		[1-6])
			play -n synth pl ${n[$i]} fade 0 1
			;;
		*)
			echo
			break
			;;
	esac
done
