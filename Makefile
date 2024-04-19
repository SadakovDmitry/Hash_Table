TARGET = hash_table
#-fsanitize=address -Wall -Wextra
FLAGS  = -O3 -mavx -mavx2 -g
MY_OPT = -DWITH_MY_STRCMP -DWITH_MY_CRC32 -DWITH_MY_STRLEN

.PHONY : clean
clean :
		rm $(TARGET)
		rm crc32.o
		rm callgrind.out.*
		rm text_processing

proc_file :
	@g++ Text_Processing.cpp $(FLAGS) -o text_processing
	@./text_processing text_in.txt text_out.txt

comp :
	@nasm -f macho64 Crc32.asm -o crc32.o
	@g++ crc32.o Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp  $(FLAGS) -o $(TARGET) -Wl,-no_pie -Wformat=2

run :
	@nasm -f macho64 Crc32.asm -o crc32.o
	@g++ crc32.o Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp  $(FLAGS) $(MY_OPT) -o $(TARGET) -Wl,-no_pie -Wformat=2
	@./$(TARGET) text_out.txt 6
	@make chart

chart :
	@python3 Distribution.py Graphics/hash.png

run_for_kcashe :
	@nasm -g -f elf64 Crc32.asm -o crc32.o
	@g++ -g crc32.o Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp $(MY_OPT) $(FLAGS) -o $(TARGET) -no-pie -g
	@valgrind --tool=callgrind ./hash_table text_out.txt 6
