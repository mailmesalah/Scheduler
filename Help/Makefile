all: p4sol

p4: p4-start.cpp
	g++ -g $< -o $@

p4sol: p4-solution.cpp
	g++ -g $< -o p4

debug: p4-solution.cpp
	g++ -DDEBUG_BUILD=1 -g $< -o p4

p4test:
	./p4 processtable-01.sim rr 1 > sim-01-rr-1.tst
	@diff -s -q sim-01-rr-1.tst sim-01-rr-1.res
	./p4 processtable-01.sim rr 4 > sim-01-rr-4.tst
	@diff -s -q sim-01-rr-4.tst sim-01-rr-4.res
	./p4 processtable-01.sim srt > sim-01-srt.tst
	@diff -s -q sim-01-srt.tst sim-01-srt.res

	./p4 processtable-02.sim rr 1 > sim-02-rr-1.tst
	@diff -s -q sim-02-rr-1.tst sim-02-rr-1.res
	./p4 processtable-02.sim rr 4 > sim-02-rr-4.tst
	@diff -s -q sim-02-rr-4.tst sim-02-rr-4.res
	./p4 processtable-02.sim srt > sim-02-srt.tst
	@diff -s -q sim-02-srt.tst sim-02-srt.res

	./p4 processtable-03.sim rr 1 > sim-03-rr-1.tst
	@diff -s -q sim-03-rr-1.tst sim-03-rr-1.res
	./p4 processtable-03.sim rr 5 > sim-03-rr-5.tst
	@diff -s -q sim-03-rr-5.tst sim-03-rr-5.res
	./p4 processtable-03.sim srt > sim-03-srt.tst
	@diff -s -q sim-03-srt.tst sim-03-srt.res

	@rm sim-01-rr-1.tst sim-01-rr-4.tst sim-01-srt.tst sim-02-rr-1.tst sim-02-rr-4.tst sim-02-srt.tst sim-03-rr-1.tst sim-03-rr-5.tst sim-03-srt.tst

p4zip:
	zip ../ProgrammingAssignment-04.zip p4-start.cpp ProgrammingAssignment-04.pdf ProgrammingAssignment-04.org processtable-01.sim processtable-02.sim processtable-03.sim Makefile *.res

p4solzip:
	zip ../ProgrammingAssignment-04-sol.zip p4-solution.cpp process-*.*

clean:
	rm -f p4 sim-*.tst core* *~
