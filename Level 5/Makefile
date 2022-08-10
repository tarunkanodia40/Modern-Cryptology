all:
	g++ decrypt.cpp -o find_password.out
	./find_password.out

password:
	g++ decrypt.cpp -o find_password.out
	./find_password.out
inputs:
	python3 generate_inputs.py
outputs:
	bash script.sh

matrix:
	g++ find_matrix.cpp -o matrix.out
	./matrix.out

clean:
	rm *.out


.SILENT: all clean inputs matrix password outputs