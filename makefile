executable: consigne.o visualisationC.o visualisationT.o main_sin.o simulateur.o regulation.o
		gcc $^ -o $@
consigne.o: consigne.c
		gcc -c $< -o $@
visualisationC.o: visualisationC.c
		gcc -c $< -o $@
visualisationT.o: visualisationT.c 
		gcc -c $< -o $@
main_sin.o: main_sim.c 
		gcc -c $< -o $@
simulateur.o: simulateur.c 
		gcc -c $< -o $@
regulation.o: regulation.c 
		gcc -c $< -o $@

clean:
		rm –f *.o executable