bfs: out/bfs-st-rf1d \
	 out/bfs-st-rf2d \
	 out/bfs-st-an

opt: out/opt-st-rs-rf1d \
	 out/opt-st-rs-rf2d \
	 out/opt-st-rs-an \
     out/opt-st-hc-rf1d \
     out/opt-st-hc-rf2d \
     out/opt-st-hc-an \
     out/opt-st-es-rf1d \
     out/opt-st-es-rf2d \
     out/opt-st-es-an \
	 out/opt-st-ga-rs-opc-rf1d \
	 out/opt-st-ga-rs-opc-rf2d \
	 out/opt-st-ga-rs-opc-an \
	 out/opt-st-ga-rs-tpc-rf1d \
	 out/opt-st-ga-rs-tpc-rf2d \
	 out/opt-st-ga-rs-tpc-an \
	 out/opt-st-ga-rs-spc-rf1d \
	 out/opt-st-ga-rs-spc-rf2d \
	 out/opt-st-ga-rs-spc-an \
	 out/opt-st-ga-rs-uc-rf1d \
	 out/opt-st-ga-rs-uc-rf2d \
	 out/opt-st-ga-rs-uc-an \
	 out/opt-st-ga-tos-opc-rf1d \
	 out/opt-st-ga-tos-opc-rf2d \
	 out/opt-st-ga-tos-opc-an \
	 out/opt-st-ga-tos-tpc-rf1d \
	 out/opt-st-ga-tos-tpc-rf2d \
	 out/opt-st-ga-tos-tpc-an \
	 out/opt-st-ga-tos-spc-rf1d \
	 out/opt-st-ga-tos-spc-rf2d \
	 out/opt-st-ga-tos-spc-an \
	 out/opt-st-ga-tos-uc-rf1d \
	 out/opt-st-ga-tos-uc-rf2d \
	 out/opt-st-ga-tos-uc-an

out/bfs-st-rf1d: src/opt-fw/MainBfs.c \
		 src/opt-fw/Bfs/Driver.h \
	         src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
		 src/opt-fw/Problem.h \
	         src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/bfs-st-rf1d -Isrc/opt-fw \
		src/opt-fw/MainBfs.c \
		src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/bfs-st-rf2d: src/opt-fw/MainBfs.c \
		 src/opt-fw/Bfs/Driver.h \
	         src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
		 src/opt-fw/Problem.h \
	         src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/bfs-st-rf2d -Isrc/opt-fw \
		src/opt-fw/MainBfs.c \
		src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/bfs-st-an: src/opt-fw/MainBfs.c \
	       src/opt-fw/Bfs/Driver.h \
	       src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
	       src/opt-fw/Problem.h \
	       src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/bfs-st-an -Isrc/opt-fw -D_GNU_SOURCE -lm -DHACK \
		src/opt-fw/MainBfs.c \
		src/opt-fw/Bfs/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-rs-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/RandomSearch/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-rs-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/RandomSearch/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-rs-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-rs-an: src/opt-fw/MainOpt.c \
		  src/opt-fw/Opt/Driver.h \
		  src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Opt/Method.h \
		  src/opt-fw/Opt/Method/RandomSearch/Method.c \
		  src/opt-fw/Problem.h \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-rs-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/RandomSearch/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-hc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/HillClimbing/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-hc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/HillClimbing/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-hc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-hc-an: src/opt-fw/MainOpt.c \
		  src/opt-fw/Opt/Driver.h \
		  src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Opt/Method.h \
		  src/opt-fw/Opt/Method/HillClimbing/Method.c \
		  src/opt-fw/Problem.h \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-hc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/HillClimbing/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-es-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-es-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-es-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-es-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-es-an: src/opt-fw/MainOpt.c \
		  src/opt-fw/Opt/Driver.h \
		  src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		  src/opt-fw/Opt/Method.h \
		  src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		  src/opt-fw/Problem.h \
		  src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-es-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/EvolutionStrategy/Method.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-rs-opc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-rs-opc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-rs-opc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-opc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-rs-tpc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-rs-tpc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-rs-tpc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-tpc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-rs-spc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-rs-spc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-rs-spc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-spc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-rs-uc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-rs-uc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-rs-uc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-rs-uc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/RandomSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-tos-opc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-tos-opc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-tos-opc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-opc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/OnePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-tos-tpc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-tos-tpc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-tos-tpc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-tpc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/TwoPointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-tos-spc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-tos-spc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-tos-spc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-spc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/SinglePointCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c

out/opt-st-ga-tos-uc-rf1d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction1D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf1d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction1D/Problem.c

out/opt-st-ga-tos-uc-rf2d: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/RealFunction2D/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-rf2d -Isrc/opt-fw \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/RealFunction2D/Problem.c

out/opt-st-ga-tos-uc-an: src/opt-fw/MainOpt.c \
		    src/opt-fw/Opt/Driver.h \
		    src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		    src/opt-fw/Opt/Method.h \
		    src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/Selection.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
			src/opt-fw/Opt/Method/GeneticAlgorithm/CrossOver.h \
			src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		    src/opt-fw/Problem.h \
		    src/opt-fw/Problem/AccessNetwork/Problem.c
	gcc -g -Wall -o out/opt-st-ga-tos-uc-an -Isrc/opt-fw -D_GNU_SOURCE -lm \
		src/opt-fw/MainOpt.c \
		src/opt-fw/Opt/Driver/SingleThreaded/Driver.c \
		src/opt-fw/Opt/Method/GeneticAlgorithm/Method.c \
	    src/opt-fw/Opt/Method/GeneticAlgorithm/TournamentSelection.c \
        src/opt-fw/Opt/Method/GeneticAlgorithm/UniformCrossOver.c \
		src/opt-fw/Problem/AccessNetwork/Problem.c
