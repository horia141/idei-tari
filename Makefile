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

	gcc -g -Wall -o out/opt-st-ga-ts-opc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-tpc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction1D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-uc-rf1d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
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

	gcc -g -Wall -o out/opt-st-ga-ts-opc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-tpc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/RealFunction2D/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-uc-rf2d -Isrc -Isrc/Method/GeneticAlgorithm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
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

	gcc -g -Wall -o out/opt-st-ga-ts-opc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-tpc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/Problem/AccessNetwork/Problem.c

	gcc -g -Wall -o out/opt-st-ga-ts-uc-an -Isrc -Isrc/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/Main.c \
		src/Driver/SingleThreaded/Driver.c \
		src/Method/GeneticAlgorithm/Method.c \
		src/Method/GeneticAlgorithm/TournamentSelection.c \
		src/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/Problem/AccessNetwork/Problem.c
