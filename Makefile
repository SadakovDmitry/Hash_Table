TARGET = hash_table
FLAGS = -fsanitize=address -Wall -Wextra -O3 -mavx -mavx2

.PHONY : clean
clean :
		rm callgrind.out.*
		rm $(TARGET)

proc_file :
	g++ Text_Processing.cpp $(FLAGS) -o text_processing
	./text_processing text_in.txt text_out.txt

comp :
	g++ Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp $(FLAGS) -o $(TARGET) -g

run :
	g++ Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp $(FLAGS) -o $(TARGET) -g
	./$(TARGET) text_out.txt
	make chart

chart :
	/usr/local/bin/python3 Distribution.py

run_for_kchache :
	g++ Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp -o $(TARGET) -g
	valgrind --tool=callgrind ./hash_table text_out.txt
