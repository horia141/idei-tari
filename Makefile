all:
	gcc -g -o out/opt-rf1d-rs -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/RandomSearch/Method.c
	gcc -g -o out/opt-rf1d-hc -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/HillClimbing/Method.c
	gcc -g -o out/opt-rf1d-es-mal -Isrc src/Main.c src/ProblemVector.c src/Problem/RealFunction1D/Problem.c src/Method/EvolutionStrategy/Method.c
	gcc -g -o out/opt-rf1d-ga-rs-opc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/OnePointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-rs-tpc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/TwoPointCrossOver.c
	gcc -g -o out/opt-rf1d-ga-rs-uc -Isrc -Isrc/Method/GeneticAlgorithm src/Main.c src/Problem/RealFunction1D/Problem.c src/Method/GeneticAlgorithm/Method.c src/Method/GeneticAlgorithm/RandomSelection.c src/Method/GeneticAlgorithm/UniformCrossOver.c
