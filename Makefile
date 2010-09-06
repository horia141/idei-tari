out: out/opt-st-rs-rf1d \
     out/opt-st-hc-rf1d \
     out/opt-st-es-rf1d \
     out/opt-st-ga-rs-opc-rf1d \
     out/opt-st-ga-rs-tpc-rf1d \
     out/opt-st-ga-rs-spc-rf1d \
     out/opt-st-ga-rs-uc-rf1d \
     out/opt-st-ga-tos-opc-rf1d \
     out/opt-st-ga-tos-tpc-rf1d \
     out/opt-st-ga-tos-spc-rf1d \
     out/opt-st-ga-tos-uc-rf1d \
     out/opt-st-rs-rf2d \
     out/opt-st-hc-rf2d \
     out/opt-st-es-rf2d \
     out/opt-st-ga-rs-opc-rf2d \
     out/opt-st-ga-rs-tpc-rf2d \
     out/opt-st-ga-rs-spc-rf2d \
     out/opt-st-ga-rs-uc-rf2d \
     out/opt-st-ga-tos-opc-rf2d \
     out/opt-st-ga-tos-tpc-rf2d \
     out/opt-st-ga-tos-spc-rf2d \
     out/opt-st-ga-tos-uc-rf2d \
     out/opt-st-rs-an \
     out/opt-st-hc-an \
     out/opt-st-es-an \
     out/opt-st-ga-rs-opc-an \
     out/opt-st-ga-rs-tpc-an \
     out/opt-st-ga-rs-spc-an \
     out/opt-st-ga-rs-uc-an \
     out/opt-st-ga-tos-opc-an \
     out/opt-st-ga-tos-tpc-an \
     out/opt-st-ga-tos-spc-an \
     out/opt-st-ga-tos-uc-an

grind: grind-st-rs-rf1d \
       grind-st-hc-rf1d \
       grind-st-es-rf1d \
       grind-st-ga-rs-opc-rf1d \
       grind-st-ga-rs-tpc-rf1d \
       grind-st-ga-rs-spc-rf1d \
       grind-st-ga-rs-uc-rf1d \
       grind-st-ga-tos-opc-rf1d \
       grind-st-ga-tos-tpc-rf1d \
       grind-st-ga-tos-spc-rf1d \
       grind-st-ga-tos-uc-rf1d \
       grind-st-rs-rf2d \
       grind-st-hc-rf2d \
       grind-st-es-rf2d \
       grind-st-ga-rs-opc-rf2d \
       grind-st-ga-rs-tpc-rf2d \
       grind-st-ga-rs-spc-rf2d \
       grind-st-ga-rs-uc-rf2d \
       grind-st-ga-tos-opc-rf2d \
       grind-st-ga-tos-tpc-rf2d \
       grind-st-ga-tos-spc-rf2d \
       grind-st-ga-tos-uc-rf2d \
       grind-st-rs-an \
       grind-st-hc-an \
       grind-st-es-an \
       grind-st-ga-rs-opc-an \
       grind-st-ga-rs-tpc-an \
       grind-st-ga-rs-spc-an \
       grind-st-ga-rs-uc-an \
       grind-st-ga-tos-opc-an \
       grind-st-ga-tos-tpc-an \
       grind-st-ga-tos-spc-an \
       grind-st-ga-tos-uc-an

out/opt-st-rs-rf1d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/RandomSearch/Method.c \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf1d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-rs-rf1d: out/opt-st-rs-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/rs dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-rs-rf1d
	valgrind --leak-check=full out/opt-st-rs-rf1d < dev/grind/tmp/cfg-st-rs-rf1d
	rm dev/grind/tmp/cfg-st-rs-rf1d

out/opt-st-hc-rf1d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/HillClimbing/Method.c \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf1d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-hc-rf1d: out/opt-st-hc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/hc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-hc-rf1d
	valgrind --leak-check=full out/opt-st-hc-rf1d < dev/grind/tmp/cfg-st-hc-rf1d
	rm dev/grind/tmp/cfg-st-hc-rf1d

out/opt-st-es-rf1d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/EvolutionStrategy/Method.c \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-es-rf1d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-es-rf1d: out/opt-st-es-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/es dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-es-rf1d
	valgrind --leak-check=full out/opt-st-es-rf1d < dev/grind/tmp/cfg-st-es-rf1d
	rm dev/grind/tmp/cfg-st-es-rf1d

out/opt-st-ga-rs-opc-rf1d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		           src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-rs-opc-rf1d: out/opt-st-ga-rs-opc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-opc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-rs-opc-rf1d
	valgrind --leak-check=full out/opt-st-ga-rs-opc-rf1d < dev/grind/tmp/cfg-st-ga-rs-opc-rf1d
	rm dev/grind/tmp/cfg-st-ga-rs-opc-rf1d

out/opt-st-ga-rs-tpc-rf1d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		           src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-rs-tpc-rf1d: out/opt-st-ga-rs-tpc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-tpc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-rs-tpc-rf1d
	valgrind --leak-check=full out/opt-st-ga-rs-tpc-rf1d < dev/grind/tmp/cfg-st-ga-rs-tpc-rf1d
	rm dev/grind/tmp/cfg-st-ga-rs-tpc-rf1d

out/opt-st-ga-rs-spc-rf1d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		           src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-rs-spc-rf1d: out/opt-st-ga-rs-spc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-spc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-rs-spc-rf1d
	valgrind --leak-check=full out/opt-st-ga-rs-spc-rf1d < dev/grind/tmp/cfg-st-ga-rs-spc-rf1d
	rm dev/grind/tmp/cfg-st-ga-rs-spc-rf1d

out/opt-st-ga-rs-uc-rf1d: src/opt-fw/Main.c \
		          src/opt-fw/Driver/SingleThreaded/Driver.c \
		          src/opt-fw/Method/GeneticAlgorithm/Method.c \
			  src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			  src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		          src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-rs-uc-rf1d: out/opt-st-ga-rs-uc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-uc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-rs-uc-rf1d
	valgrind --leak-check=full out/opt-st-ga-rs-uc-rf1d < dev/grind/tmp/cfg-st-ga-rs-uc-rf1d
	rm dev/grind/tmp/cfg-st-ga-rs-uc-rf1d

out/opt-st-ga-tos-opc-rf1d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		            src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-tos-opc-rf1d: out/opt-st-ga-tos-opc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-opc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-tos-opc-rf1d
	valgrind --leak-check=full out/opt-st-ga-tos-opc-rf1d < dev/grind/tmp/cfg-st-ga-tos-opc-rf1d
	rm dev/grind/tmp/cfg-st-ga-tos-opc-rf1d

out/opt-st-ga-tos-tpc-rf1d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		            src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-tos-tpc-rf1d: out/opt-st-ga-tos-tpc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-tpc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-tos-tpc-rf1d
	valgrind --leak-check=full out/opt-st-ga-tos-tpc-rf1d < dev/grind/tmp/cfg-st-ga-tos-tpc-rf1d
	rm dev/grind/tmp/cfg-st-ga-tos-tpc-rf1d

out/opt-st-ga-tos-spc-rf1d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		            src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-tos-spc-rf1d: out/opt-st-ga-tos-spc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-spc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-tos-spc-rf1d
	valgrind --leak-check=full out/opt-st-ga-tos-spc-rf1d < dev/grind/tmp/cfg-st-ga-tos-spc-rf1d
	rm dev/grind/tmp/cfg-st-ga-tos-spc-rf1d

out/opt-st-ga-tos-uc-rf1d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		           src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf1d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

grind-st-ga-tos-uc-rf1d: out/opt-st-ga-tos-uc-rf1d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-uc dev/grind/cfg/rf1d > dev/grind/tmp/cfg-st-ga-tos-uc-rf1d
	valgrind --leak-check=full out/opt-st-ga-tos-uc-rf1d < dev/grind/tmp/cfg-st-ga-tos-uc-rf1d
	rm dev/grind/tmp/cfg-st-ga-tos-uc-rf1d

out/opt-st-rs-rf2d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/RandomSearch/Method.c \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf2d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-rs-rf2d: out/opt-st-rs-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/rs dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-rs-rf2d
	valgrind --leak-check=full out/opt-st-rs-rf2d < dev/grind/tmp/cfg-st-rs-rf2d
	rm dev/grind/tmp/cfg-st-rs-rf2d

out/opt-st-hc-rf2d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/HillClimbing/Method.c \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf2d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-hc-rf2d: out/opt-st-hc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/hc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-hc-rf2d
	valgrind --leak-check=full out/opt-st-hc-rf2d < dev/grind/tmp/cfg-st-hc-rf2d
	rm dev/grind/tmp/cfg-st-hc-rf2d

out/opt-st-es-rf2d: src/opt-fw/Main.c \
		    src/opt-fw/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Method/EvolutionStrategy/Method.c \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-es-rf2d -Isrc/opt-fw \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-es-rf2d: out/opt-st-es-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/es dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-es-rf2d
	valgrind --leak-check=full out/opt-st-es-rf2d < dev/grind/tmp/cfg-st-es-rf2d
	rm dev/grind/tmp/cfg-st-es-rf2d

out/opt-st-ga-rs-opc-rf2d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		           src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-rs-opc-rf2d: out/opt-st-ga-rs-opc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-opc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-rs-opc-rf2d
	valgrind --leak-check=full out/opt-st-ga-rs-opc-rf2d < dev/grind/tmp/cfg-st-ga-rs-opc-rf2d
	rm dev/grind/tmp/cfg-st-ga-rs-opc-rf2d

out/opt-st-ga-rs-tpc-rf2d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		           src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-rs-tpc-rf2d: out/opt-st-ga-rs-tpc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-tpc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-rs-tpc-rf2d
	valgrind --leak-check=full out/opt-st-ga-rs-tpc-rf2d < dev/grind/tmp/cfg-st-ga-rs-tpc-rf2d
	rm dev/grind/tmp/cfg-st-ga-rs-tpc-rf2d

out/opt-st-ga-rs-spc-rf2d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		           src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-rs-spc-rf2d: out/opt-st-ga-rs-spc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-spc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-rs-spc-rf2d
	valgrind --leak-check=full out/opt-st-ga-rs-spc-rf2d < dev/grind/tmp/cfg-st-ga-rs-spc-rf2d
	rm dev/grind/tmp/cfg-st-ga-rs-spc-rf2d

out/opt-st-ga-rs-uc-rf2d: src/opt-fw/Main.c \
		          src/opt-fw/Driver/SingleThreaded/Driver.c \
		          src/opt-fw/Method/GeneticAlgorithm/Method.c \
			  src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			  src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		          src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-rs-uc-rf2d: out/opt-st-ga-rs-uc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-uc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-rs-uc-rf2d
	valgrind --leak-check=full out/opt-st-ga-rs-uc-rf2d < dev/grind/tmp/cfg-st-ga-rs-uc-rf2d
	rm dev/grind/tmp/cfg-st-ga-rs-uc-rf2d

out/opt-st-ga-tos-opc-rf2d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		            src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-tos-opc-rf2d: out/opt-st-ga-tos-opc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-opc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-tos-opc-rf2d
	valgrind --leak-check=full out/opt-st-ga-tos-opc-rf2d < dev/grind/tmp/cfg-st-ga-tos-opc-rf2d
	rm dev/grind/tmp/cfg-st-ga-tos-opc-rf2d

out/opt-st-ga-tos-tpc-rf2d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		            src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-tos-tpc-rf2d: out/opt-st-ga-tos-tpc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-tpc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-tos-tpc-rf2d
	valgrind --leak-check=full out/opt-st-ga-tos-tpc-rf2d < dev/grind/tmp/cfg-st-ga-tos-tpc-rf2d
	rm dev/grind/tmp/cfg-st-ga-tos-tpc-rf2d

out/opt-st-ga-tos-spc-rf2d: src/opt-fw/Main.c \
		            src/opt-fw/Driver/SingleThreaded/Driver.c \
		            src/opt-fw/Method/GeneticAlgorithm/Method.c \
			    src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			    src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		            src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-tos-spc-rf2d: out/opt-st-ga-tos-spc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-spc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-tos-spc-rf2d
	valgrind --leak-check=full out/opt-st-ga-tos-spc-rf2d < dev/grind/tmp/cfg-st-ga-tos-spc-rf2d
	rm dev/grind/tmp/cfg-st-ga-tos-spc-rf2d

out/opt-st-ga-tos-uc-rf2d: src/opt-fw/Main.c \
		           src/opt-fw/Driver/SingleThreaded/Driver.c \
		           src/opt-fw/Method/GeneticAlgorithm/Method.c \
			   src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			   src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		           src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf2d -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

grind-st-ga-tos-uc-rf2d: out/opt-st-ga-tos-uc-rf2d
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-uc dev/grind/cfg/rf2d > dev/grind/tmp/cfg-st-ga-tos-uc-rf2d
	valgrind --leak-check=full out/opt-st-ga-tos-uc-rf2d < dev/grind/tmp/cfg-st-ga-tos-uc-rf2d
	rm dev/grind/tmp/cfg-st-ga-tos-uc-rf2d

out/opt-st-rs-an: src/opt-fw/Main.c \
		  src/opt-fw/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Method/RandomSearch/Method.c \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-rs-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-rs-an: out/opt-st-rs-an
	cat dev/grind/cfg/st dev/grind/cfg/rs dev/grind/cfg/an > dev/grind/tmp/cfg-st-rs-an
	valgrind --leak-check=full out/opt-st-rs-an < dev/grind/tmp/cfg-st-rs-an
	rm dev/grind/tmp/cfg-st-rs-an

out/opt-st-hc-an: src/opt-fw/Main.c \
		  src/opt-fw/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Method/HillClimbing/Method.c \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-hc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-hc-an: out/opt-st-hc-an
	cat dev/grind/cfg/st dev/grind/cfg/hc dev/grind/cfg/an > dev/grind/tmp/cfg-st-hc-an
	valgrind --leak-check=full out/opt-st-hc-an < dev/grind/tmp/cfg-st-hc-an
	rm dev/grind/tmp/cfg-st-hc-an

out/opt-st-es-an: src/opt-fw/Main.c \
		  src/opt-fw/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Method/EvolutionStrategy/Method.c \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-es-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-es-an: out/opt-st-es-an
	cat dev/grind/cfg/st dev/grind/cfg/es dev/grind/cfg/an > dev/grind/tmp/cfg-st-es-an
	valgrind --leak-check=full out/opt-st-es-an < dev/grind/tmp/cfg-st-es-an
	rm dev/grind/tmp/cfg-st-es-an

out/opt-st-ga-rs-opc-an: src/opt-fw/Main.c \
		         src/opt-fw/Driver/SingleThreaded/Driver.c \
		         src/opt-fw/Method/GeneticAlgorithm/Method.c \
			 src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			 src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		         src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-rs-opc-an: out/opt-st-ga-rs-opc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-opc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-rs-opc-an
	valgrind --leak-check=full out/opt-st-ga-rs-opc-an < dev/grind/tmp/cfg-st-ga-rs-opc-an
	rm dev/grind/tmp/cfg-st-ga-rs-opc-an

out/opt-st-ga-rs-tpc-an: src/opt-fw/Main.c \
		         src/opt-fw/Driver/SingleThreaded/Driver.c \
		         src/opt-fw/Method/GeneticAlgorithm/Method.c \
			 src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			 src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		         src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-rs-tpc-an: out/opt-st-ga-rs-tpc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-tpc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-rs-tpc-an
	valgrind --leak-check=full out/opt-st-ga-rs-tpc-an < dev/grind/tmp/cfg-st-ga-rs-tpc-an
	rm dev/grind/tmp/cfg-st-ga-rs-tpc-an

out/opt-st-ga-rs-spc-an: src/opt-fw/Main.c \
		         src/opt-fw/Driver/SingleThreaded/Driver.c \
		         src/opt-fw/Method/GeneticAlgorithm/Method.c \
			 src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			 src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		         src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-rs-spc-an: out/opt-st-ga-rs-spc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-spc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-rs-spc-an
	valgrind --leak-check=full out/opt-st-ga-rs-spc-an < dev/grind/tmp/cfg-st-ga-rs-spc-an
	rm dev/grind/tmp/cfg-st-ga-rs-spc-an

out/opt-st-ga-rs-uc-an: src/opt-fw/Main.c \
		        src/opt-fw/Driver/SingleThreaded/Driver.c \
		        src/opt-fw/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		        src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/RandomSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-rs-uc-an: out/opt-st-ga-rs-uc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-rs-uc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-rs-uc-an
	valgrind --leak-check=full out/opt-st-ga-rs-uc-an < dev/grind/tmp/cfg-st-ga-rs-uc-an
	rm dev/grind/tmp/cfg-st-ga-rs-uc-an

out/opt-st-ga-tos-opc-an: src/opt-fw/Main.c \
		          src/opt-fw/Driver/SingleThreaded/Driver.c \
		          src/opt-fw/Method/GeneticAlgorithm/Method.c \
			  src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			  src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		          src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-tos-opc-an: out/opt-st-ga-tos-opc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-opc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-tos-opc-an
	valgrind --leak-check=full out/opt-st-ga-tos-opc-an < dev/grind/tmp/cfg-st-ga-tos-opc-an
	rm dev/grind/tmp/cfg-st-ga-tos-opc-an

out/opt-st-ga-tos-tpc-an: src/opt-fw/Main.c \
		          src/opt-fw/Driver/SingleThreaded/Driver.c \
		          src/opt-fw/Method/GeneticAlgorithm/Method.c \
			  src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			  src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		          src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-tos-tpc-an: out/opt-st-ga-tos-tpc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-tpc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-tos-tpc-an
	valgrind --leak-check=full out/opt-st-ga-tos-tpc-an < dev/grind/tmp/cfg-st-ga-tos-tpc-an
	rm dev/grind/tmp/cfg-st-ga-tos-tpc-an

out/opt-st-ga-tos-spc-an: src/opt-fw/Main.c \
		          src/opt-fw/Driver/SingleThreaded/Driver.c \
		          src/opt-fw/Method/GeneticAlgorithm/Method.c \
			  src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			  src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		          src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-tos-spc-an: out/opt-st-ga-tos-spc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-spc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-tos-spc-an
	valgrind --leak-check=full out/opt-st-ga-tos-spc-an < dev/grind/tmp/cfg-st-ga-tos-spc-an
	rm dev/grind/tmp/cfg-st-ga-tos-spc-an

out/opt-st-ga-tos-uc-an: src/opt-fw/Main.c \
		         src/opt-fw/Driver/SingleThreaded/Driver.c \
		         src/opt-fw/Method/GeneticAlgorithm/Method.c \
			 src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
			 src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		         src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-an -Isrc/opt-fw -Isrc/opt-fw/opt-fw/Method/GeneticAlgorithm -D_GNU_SOURCE -lm \
		src/opt-fw/Main.c \
		src/opt-fw/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Method/GeneticAlgorithm/Method.c \
		src/opt-fw/Method/GeneticAlgorithm/TournamentSelection.c \
		src/opt-fw/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

grind-st-ga-tos-uc-an: out/opt-st-ga-tos-uc-an
	cat dev/grind/cfg/st dev/grind/cfg/ga-tos-uc dev/grind/cfg/an > dev/grind/tmp/cfg-st-ga-tos-uc-an
	valgrind --leak-check=full out/opt-st-ga-tos-uc-an < dev/grind/tmp/cfg-st-ga-tos-uc-an
	rm dev/grind/tmp/cfg-st-ga-tos-uc-an

out/plot-rf1d/plot-rf1d.tcl: src/plot-rf1d/plot-rf1d.tcl \
	       		     $(wildcard src/plot-rf1d/cfg/*)
	mkdir -p out/plot-rf1d
	mkdir -p out/plot-rf1d/cfg
	mkdir -p out/plot-rf1d/tmp

	cp src/plot-rf1d/plot-rf1d.tcl out/plot-rf1d
	cp -r src/plot-rf1d/cfg out/plot-rf1d

out/run-an-tests/run-an-tests.tcl: src/run-an-tests/run-an-tests.tcl \
				   $(wildcard src/run-an-tests/cfg/small-run/*) \
				   $(wildcard src/run-an-tests/cfg/large-run/*)
	mkdir -p out/run-an-tests
	mkdir -p out/run-an-tests/cfg
	mkdir -p out/run-an-tests/tmp

	cp src/run-an-tests/run-an-tests.tcl out/run-an-tests
	cp -r src/run-an-tests/cfg/small-run out/run-an-tests/cfg
	cp -r src/run-an-tests/cfg/large-run out/run-an-tests/cfg
