#include <stdio.h>
#include <math.h>
//Visual Studio se queja si no uso escribo esta bandera
#define _CRT_SECURE_NO_WARNINGS
//Por Diego Granada 201922383



//Defino prototipo
void procedimiento(unsigned char caracter, unsigned short * bitsActualParidad);


int main()
{

	struct Estructura {
		char cadena[17];
		unsigned short bitsParidad;
	}datos;

	datos.bitsParidad = 0;
	char input[17];
	
	printf("Por favor ingresa la cadena cuya paridad quieres revisar: \n");
	scanf("%s", input);

	//printf("This is the output: %s\n", input);
	memcpy(&datos.cadena, &input, 17);

	

	//Creo un apuntador a datos.bitsParidad
	unsigned short * pointer = &(datos.bitsParidad);

	//Ejecuta el procedimiento para cada caracter, ignora caracteres que son invalidos
	for (char i = 16; i >= 0; i--)
	{
		if (datos.cadena[i] > 0) {
			procedimiento(datos.cadena[i],pointer);
		}else {
			procedimiento(0, pointer);
			
		}
		
		//printf("%hu \n", datos.bitsParidad);

	}

	//Imprime el numero de resultado (que ya esta codificado bien en binario). Imprime bit por bit de mas a menos significante
	for (char i = 16; i > 0; i--)
	{
		//Imprime un bit de la cadena de bits de paridad. Si ese bit es 0, se imprime 0. Si no, se imprime 1.
		unsigned int temp = datos.bitsParidad & (int)pow(2,(i-1));
		printf("%hu", temp==0? 0: 1);
		
	}
	return 0;
}
void procedimiento(unsigned char caracter, unsigned short  * bitsActualParidad) {
	short count = 0;
	for (short index = 0; index < 8; index++){
		/*
		Este es el codigo en C correspondiente, solo que queria intentar lograrlo en Assembly
		if ( ( (caracter>>ind) & 1) == 1) {
			count++;
		}*/
		__asm {
			mov cx, count    //move count into the cx register
			mov al, cl       //move the least significant part of count  into AL, to save space since CX will get overwritten anyways
			mov ah, caracter //move char into AH register
			mov cx, index      //move index into CX register
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
		
	}
	count = count & 1;//gets the amount of zeroes and checks if its even or odd
	unsigned short bitsParidad = *bitsActualParidad;
	
	//Aca solo sumo count a bitsDePartidad y roto a la derecha. Era mas facil con assembly, ya que con C me toca hacer dos shifts y despues una union... 
	//Esto permite poner el bit de paridad en el digito mas significativo
	__asm {
		mov ax,bitsParidad
		add ax, count
		ror ax, 1
		mov bitsParidad, ax
	}

	*bitsActualParidad = bitsParidad;

}