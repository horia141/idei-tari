all:
# Real Function 1D
	gcc -g -Wall -o out/opt-st-rs-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-hc-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-es-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/EvolutionStrategy/Method.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

# Real Function 2D
	gcc -g -Wall -o out/opt-st-rs-rf2d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-hc-rf2d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-es-rf2d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/EvolutionStrategy/Method.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

# Access Network
	gcc -g -Wall -o out/opt-st-rs-an -Isrc -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-hc-an -Isrc -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-es-an -Isrc -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/EvolutionStrategy/Method.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-opc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-tpc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-uc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-rs-spc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/RandomSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-opc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-tpc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-uc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-tos-spc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

out/opt-st-rs-rf1d: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/RandomSearch/Method.c \
		    src/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/RealFunction1D/Problem.c

grind-st-rs-rf1d: out/opt-st-rs-rf1d
	cat out/grind-run/cfg/st out/grind-run/cfg/rs out/grind-run/cfg/rf1d > out/grind-run/tmp/cfg-st-rs-rf1d
	valgrind --leak-check=full out/opt-st-rs-rf1d < out/grind-run/tmp/cfg-st-rs-rf1d
	rm out/grind-run/tmp/cfg-st-rs-rf1d

out/opt-st-hc-rf1d: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/HillClimbing/Method.c \
		    src/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/RealFunction1D/Problem.c

grind-st-hc-rf1d: out/opt-st-hc-rf1d
	cat out/grind-run/cfg/st out/grind-run/cfg/hc out/grind-run/cfg/rf1d > out/grind-run/tmp/cfg-st-hc-rf1d
	valgrind --leak-check=full out/opt-st-hc-rf1d < out/grind-run/tmp/cfg-st-hc-rf1d
	rm out/grind-run/tmp/cfg-st-hc-rf1d

out/opt-st-es-rf1d: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/EvolutionStrategy/Method.c \
		    src/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-es-rf1d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/EvolutionStrategy/Method.c \
		src/Problem/RealFunction1D/Problem.c

grind-st-es-rf1d: out/opt-st-es-rf1d
	cat out/grind-run/cfg/st out/grind-run/cfg/es out/grind-run/cfg/rf1d > out/grind-run/tmp/cfg-st-es-rf1d
	valgrind --leak-check=full out/opt-st-es-rf1d < out/grind-run/tmp/cfg-st-es-rf1d
	rm out/grind-run/tmp/cfg-st-es-rf1d

out/opt-st-rs-rf2d: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/RandomSearch/Method.c \
		    src/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf2d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/RealFunction2D/Problem.c

grind-st-rs-rf2d: out/opt-st-rs-rf2d
	cat out/grind-run/cfg/st out/grind-run/cfg/rs out/grind-run/cfg/rf2d > out/grind-run/tmp/cfg-st-rs-rf2d
	valgrind --leak-check=full out/opt-st-rs-rf2d < out/grind-run/tmp/cfg-st-rs-rf2d
	rm out/grind-run/tmp/cfg-st-rs-rf2d

out/opt-st-hc-rf2d: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/HillClimbing/Method.c \
		    src/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf2d -Isrc \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/RealFunction2D/Problem.c

grind-st-hc-rf2d: out/opt-st-hc-rf2d
	cat out/grind-run/cfg/st out/grind-run/cfg/hc out/grind-run/cfg/rf2d > out/grind-run/tmp/cfg-st-hc-rf2d
	valgrind --leak-check=full out/opt-st-hc-rf2d < out/grind-run/tmp/cfg-st-hc-rf2d
	rm out/grind-run/tmp/cfg-st-hc-rf2d

out/opt-st-rs-an: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/RandomSearch/Method.c \
		    src/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-rs-an -Isrc -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/RandomSearch/Method.c \
		src/Problem/AccessNetwork/Problem.c

grind-st-rs-an: out/opt-st-rs-an
	cat out/grind-run/cfg/st out/grind-run/cfg/rs out/grind-run/cfg/an > out/grind-run/tmp/cfg-st-rs-an
	valgrind --leak-check=full out/opt-st-rs-an < out/grind-run/tmp/cfg-st-rs-an
	rm out/grind-run/tmp/cfg-st-rs-an

out/opt-st-hc-an: src/Main.c \
		    src/Driver/SingleThreaded/Driver.c \
		    src/Method/HillClimbing/Method.c \
		    src/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-hc-an -Isrc -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/HillClimbing/Method.c \
		src/Problem/AccessNetwork/Problem.c

grind-st-hc-an: out/opt-st-hc-an
	cat out/grind-run/cfg/st out/grind-run/cfg/hc out/grind-run/cfg/an > out/grind-run/tmp/cfg-st-hc-an
	valgrind --leak-check=full out/opt-st-hc-an < out/grind-run/tmp/cfg-st-hc-an
	rm out/grind-run/tmp/cfg-st-hc-an

runtest:
	./dev/runtest.tcl
