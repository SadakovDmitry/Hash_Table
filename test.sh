g++ Hash_Table.cpp Hash_func.cpp Hash_Table_func.cpp -fsanitize=address -Wall -Wextra -O3 -o hash_table
names_hash=(Hash_Zero Hash_First_Letter Hash_Len_Word Hash_Sum_Letters Hash_Rol Hash_Ror Hash_Crc32)

for ((i = 0; i < 7; i++))
do
    ./hash_table text_out.txt ${i}
    python3 Distribution.py Graphics/${names_hash[i]}.png
done
