N=tlots123
SCRPT=check_master.bash
KT = ken_tool
KI = ken_init
KS = ken_self
KO = ken_output

$(KT): $(KT).c
	gcc -o $(KT) $(KT).c

$(KI).c: $(KT) ken_source.c
	./$(KT) < ken_source.c > $(KI).c
	cat ken_source.c >> $(KI).c

$(KI): $(KI).c
	gcc -o $(KI) $(KI).c

$(KS).c: $(KI)
	./$(KI) > $(KS).c

$(KS): $(KS).c
	gcc -o $(KS) $(KS).c

$(KO).diff: $(KS).c
	/bin/rm -f $(KS) $(KO) $(KO).diff
	gcc -o $(KS) $(KS).c
	./$(KS) > $(KO)
	diff $(KS).c $(KO) > $(KO).diff

ken_check: $(KO).diff
	./checkdiff.bash $(KO).diff; /bin/rm -f $(KO) $(KO).diff

clean:
	/bin/rm -f a.out *.o $(M) diff_*.txt $(E0) $(E1) $(KT) $(KI)* $(KS)* ken_0*.c ken_0*

tgz: clean
	cd .. ; tar cvzf $(N).tgz $(N)

