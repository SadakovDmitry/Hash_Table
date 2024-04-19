make comp
names_hash=(Hash_Zero Hash_First_Letter Hash_Len_Word Hash_Sum_Letters Hash_Rol Hash_Ror Hash_Crc32 Hash_My_Crc32)

for ((i = 0; i < 7; i++))
do
    ./hash_table text_out.txt ${i}
    python3 Distribution.py Graphics/${names_hash[i]}.png ${names_hash[i]}
done
