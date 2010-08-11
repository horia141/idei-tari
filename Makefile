all:
# Real Function 1D
	gcc -g -o out/opt-rf1d-rs -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/RandomSearch/Method.c

	gcc -g -o out/opt-rf1d-hc -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/HillClimbing/Method.c

	gcc -g -o out/opt-rf1d-es-mal -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/EvolutionStrategy/Method.c

	gcc -g -o out/opt-rf1d-ga-rs-opc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/OnePointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-rs-tpc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/TwoPointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-rs-uc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/UniformCrossOver.c

	gcc -g -o out/opt-rf1d-ga-ts-opc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/OnePointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-ts-tpc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/TwoPointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-ts-uc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/UniformCrossOver.c

# Real Function 2D

	gcc -g -o out/opt-rf2d-rs -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction2D/Problem.c src/Method/RandomSearch/Method.c

	gcc -g -o out/opt-rf2d-hc -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction2D/Problem.c src/Method/HillClimbing/Method.c

	gcc -g -o out/opt-rf2d-es-mal -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction2D/Problem.c src/Method/EvolutionStrategy/Method.c

	gcc -g -o out/opt-rf2d-ga-rs-opc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/OnePointCrossOver.c
	gcc -g -o out/opt-rf2d-ga-rs-tpc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/TwoPointCrossOver.c
	gcc -g -o out/opt-rf2d-ga-rs-uc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/UniformCrossOver.c

	gcc -g -o out/opt-rf2d-ga-ts-opc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/OnePointCrossOver.c
	gcc -g -o out/opt-rf2d-ga-ts-tpc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/TwoPointCrossOver.c
	gcc -g -o out/opt-rf2d-ga-ts-uc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction2D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/TournamentSelection.c src/Method/GeneticAlgorithm/UniformCrossOver.c

# Access Network
