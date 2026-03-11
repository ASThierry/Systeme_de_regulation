executable: consigne.o visualisationC.o visualisationT.o main_sin.o simulateur.o regulation.o
		gcc  $^ -o $@
consigne.o: consigne.c
		gcc -g -c $< -o $@
visualisationC.o: visualisationC.c
		gcc -g -c $< -o $@
visualisationT.o: visualisationT.c 
		gcc -g -c $< -o $@
main_sin.o: main_sim.c 
		gcc -g -c $< -o $@
simulateur.o: simulateur.c 
		gcc -g -c $< -o $@
regulation.o: regulation.c 
		gcc -g -c $< -o $@

clean:
		rm -f *.o executable .verrouData .verrouConsigne