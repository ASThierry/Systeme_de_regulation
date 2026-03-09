executable: consigne.o visualisationC.o visualisationT.o main_sim.c
		gcc $^ -o $@
consigne.o: consigne.c
			gcc -c $< -o $@
visualisationC.o: visualisationC.c
			gcc -c $< -o $@
visualisationT.o: visualisationT.c 
			gcc -c $< -o $@
clean:
			rm –f *.o executable