make:
	g++ -o trap-omp trap-omp.cpp -fopenmp
	g++ -o matrix-omp matrix-omp.cpp -fopenmp

clean:
	rm matrix-omp
	rm trap-omp