NAME=projet_pa
ARRAYLISTINC = -I ./lib/arraylist/includes
GNLINC= -I ./lib/getNextLine
STRINGBUILDERINC=-I ./lib/stringbuilder/includes
INCLUDES= -I ./includes \
			$(ARRAYLISTINC) \
			$(GNLINC) \
			$(STRINGBUILDERINC)

SRC = *.c ./lib/getNextLine/*.c ./src/*.c
LIB  = lib/arraylist/arraylist.a lib/stringbuilder/lib_string_builder.a

arryalist:
	$(MAKE) -C ./lib/arraylist/

stringbuilder:
	$(MAKE) -C ./lib/stringbuilder/

$(NAME): $(stringbuilder) $(arryalist)
	gcc -fsanitize=address -g $(SRC) $(LIB) $(INCLUDES) -o $(NAME)

all:  $(NAME)


clean:	
	rm -f  $(OBJ)

fclean: clean	
	rm -f $(NAME)	
	rm -f includes/*.*.gch	

re: fclean all 

re-all: arryalist_re stringbuilder_re fclean all
arryalist_re:
	$(MAKE) re -C ./lib/arraylist/

stringbuilder_re:
	$(MAKE) re -C ./lib/stringbuilder/