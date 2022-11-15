#!/bin/bash

# RULEZI SCRIPTUL INTR-UN FOLDER CARE CONTINE DOAR: CONTINUTUL ARHIVEI CU TESTE (SI IN SI OUT, ARHIVA IN SINE NU), EXECUTABILUL SI SCRIPTUL (LOGIC)
# (DE)COMENTEZI AICI CA SA ITI TESTEZE CU TOATE TESTELE DE INPUT, CU 1,2,4,8 THREADURI (PE RAND PE FIECARE TEST DE INPUT) SI SA COMPARE CU OUTPUT
# runs="1 2 4 8"
# outFile="out.txt"
# for FILE in *; do 
# 	aux="${FILE/in/out}"
# 	if [[ $FILE == *"in_"* ]]; then
# 		for P in $runs; do
# 			./homework $FILE "out.test.$P" $P	
# 		done
# 		diff -q --from-file $aux out.test.*
# 		if [ $? -eq 0 ]; then
# 			echo Output correct on intensive test
# 			rm out.test.*
# 		fi
# 	fi
# done

# (DE)COMENTEZI AICI CA SA ITI TESTEZE SCALABILITATEA+SALVATI TIMPI (POATE DURA MULT)
# runs="1 2 4 8"
# for P in $runs; do
# 	{ time ./homework "in_3D_3.601.txt" out.$P.txt $P ; } 2>> timpi_masurati_in_3D_3.601.txt
# done
# for P in $runs; do
# 	{ time ./homework "in_2D_7.1000.txt" out.$P.txt $P ; } 2>> timpi_masurati_in_2D_7.1000.txt
# done
