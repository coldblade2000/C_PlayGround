#include <stdio.h>
//Visual Studio se queja si no uso escribo esta bandera
#define _CRT_SECURE_NO_WARNINGS

//Defino prototipo
short procedimiento(char caracter, short bitsParidad);

struct Estructura {
	short bitsParidad;
	char cadena[17];
};
int main()
{
	struct Estructura datos;
	datos.bitsParidad = 0;
	char input[17];
	
	printf("Por favor ingresa la cadena de numeros\n");
	scanf("%s", input);
	datos.bitsParidad = 0;
	printf("This is the output: %s", input);
	memcpy(&datos.cadena, &input, 17);
	for (char i = 0; i < 17; i++)
	{
		datos.bitsParidad = procedimiento(datos.cadena[i], datos.bitsParidad);
		printf("%hu \n", datos.bitsParidad);
	}


	for (char i = 0; i < 17; i++)
	{
		printf("%hu", datos.bitsParidad & 1);
		datos.bitsParidad  = datos.bitsParidad >> 1;
	}
	/*printf("%hu\n", procedimiento(105, 2)); //0
	printf("%hu\n", procedimiento(106, 2)); //0
	printf("%hu\n", procedimiento(107, 2)); //1
	printf("%hu\n", procedimiento(108, 2)); //0
	printf("%hu\n", procedimiento(109, 2)); //1
	printf("%hu\n", procedimiento(110, 2)); //1
	printf("%hu\n", procedimiento(111, 2)); //0*/
	return 0;
};
short procedimiento(char caracter, short bitsParidad) {
	short count = 0;
	for (short ind = 0; ind < 8; ind++){
		__asm {
			mov cx, count    //move count into the cx register
			mov al, cl       //move the least significant part of count  into AL, to save space since CX will get overwritten anyways
			mov ah, caracter //move char into AH register
			mov cx, ind      //move index into CX register
			shr ah, cl       //ShiftRight the character n times, where n=index
			and ah, 1        //zero out everything but the least significant bit in the char
			cmp ah, 1        //if(char last bit == 1)
			jne donothing    //if bit !=1, jump past the next line
			inc al			 //count++
			donothing:
			mov cx, 0        //zero out the BX register
			mov cl, al       //move the count var into CL
			mov count, cx   //move the count value back into the count variable in memory
		}
		/*
		Este es el codigo en C correspondiente, solo que queria intentar lograrlo en Assembly. Si eso no se permitia, por favor considerar el
		codigo dentro de este comentario en cambio
		if ( ( (caracter>>ind) & 1) == 1) {
			count++;
		}*/
	}
	count = count & 1;//gets the amount of zeroes and checks if its even or odd

	//Aca solo sumo count a bitsDePartidad y roto a la derecha. Era mas facil con assembly, ya que con C me toca hacer dos shifts y despues una union... 
	__asm {
		mov ax,bitsParidad
		add ax, count
		ror ax, 1
		mov bitsParidad, ax
	}
	return bitsParidad;

}