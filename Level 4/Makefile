pairs: 
	g++ generate_pairs.cpp
	./a.out

outputs:
	bash script.sh

	
differential:
	python3 differential_analysis.py

keys:
	python3 key_generator.py

frequency:
	python3 freq_calculator.py

create_keys:
	g++ key_creator.cpp
	./a.out

check:
	gcc DES.c
	./a.out Output_keys.txt

clean:
	rm input_S_box.txt output_S_box.txt output_expansion.txt a.out generated_keys.txt Output_keys.txt