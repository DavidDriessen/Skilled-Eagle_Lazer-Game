#include <stdio.h>
void print_encoded_stream(char a, char b);
void print_binary(char print, int lenght);
char * encode_stream(char speler , char data, char control);
char * decode_stream(unsigned char streamA, unsigned char streamB);

int main(int argc, char **argv)
{
	char speler = 4; //0b00000110;
	char data =  2;  //0b00011000;//3
	char control = 0; //0b00000110;


	printf("speler %d \n", speler);
	print_binary(speler, 8);
	printf("\ndata %d \n", data);
	print_binary(data, 8);
	printf("\ncontrol %d \n", control);
	print_binary(control , 8);
	
	printf("\n\nencoded stream\n\n");
	char * stream_encode = encode_stream(speler,data,control);
	
	
	printf("\n\ntest return\n");
	
	print_binary(stream_encode[0] ,8);
	print_binary(stream_encode[1] , 8);
	
	printf("\n\ntest decode\n");
	char * stream_decode = decode_stream(stream_encode[0], stream_encode[1]);
	
	printf("\ndecoded speler %d \n",stream_decode[0]);
	print_binary(stream_decode[0] ,8);
	printf("\ndecoded data %d \n",stream_decode[1]);
	print_binary(stream_decode[1] , 8);
	printf("\ndecoded control %d \n",stream_decode[2]);
	print_binary(stream_decode[2] ,8);
	
	
	return 0;
}


void print_binary(char print, int lenght){
	for(int h = 0; h < lenght; h++){
		if(( print << h ) & 0x80){
			//std::cout<< "1";
			printf("1");
		}
		else{
			//std::cout<< "0";
			printf("0");
		}
	}
	//printf("\n");
}

void print_encoded_stream(char a, char b){
	print_binary(a,8);
	print_binary(b,8);
	printf("\n\n");
}


char * encode_stream(char speler , char data, char control){
	unsigned char streamA = 0;
	unsigned char streamB = 0;
	char list[2];
	printf("stream after start\n");
	streamA = streamA | 0x01;
	streamA = streamA << 1;

	print_encoded_stream(streamA,streamB);
	
	
	
	for(int y = 0; y < 5; y++){
		if((speler << y) & 0x10 ){
			streamA = streamA | 0x01;
			streamA = streamA << 1;
			printf("speler A1\n");
		}
		else{
			streamA = streamA << 1;
			printf("speler A0\n");
		}
	}
	
	printf("stream after speler\n");
	print_encoded_stream(streamA,streamB);

	for(int y = 0; y < 5; y++){
		if(y > 1){

			if((data << y) & 0x10 ){
				streamB = streamB | 0x01;
				streamB = streamB << 1;
				printf("data B1\n");
			}
			else{
				streamB = streamB << 1;
				printf("data B0\n");
			}
			
		}
		
		else{

			if(((data << y) & 0x10) && y == 1 ){
				streamA = streamA | 0x01;
				printf("data_end byteA A1\n");
			}
			else if( (data << y) & 0x10 ){
				streamA = streamA | 0x01;
				streamA = streamA << 1;
				printf("data A1\n");
			}
			else{
				if(y == 1){
					printf("data_end byteA  A0\n");
				}
				else{
					streamA = streamA << 1;
					printf("data A0\n");
				}
				
			}
		}
	}
	
	printf("stream after data\n");
	print_encoded_stream(streamA,streamB);
	
	for(int y = 0; y < 5; y++){
		if(((control << y) & 0x10) && y == 4 ){
			streamB = streamB | 0x01;
			printf("control_end byteB B1\n");
		}
		else if((control << y) & 0x10 ){
			streamB = streamB | 0x01;
			streamB = streamB << 1;
			printf("control B1\n");
		}
		else{
			if(y == 4){
				printf("control_end byteB B0\n");
			}
			else{
				printf("control B0\n");
				streamB = streamB << 1;;
				
			}
			
		}
	}
	
	printf("stream after control\n");
	print_encoded_stream(streamA,streamB);;
	
	list[0] = streamA;
	list[1] = streamB;
	
	return  list;
	
	
	
}

char * decode_stream(unsigned char streamA, unsigned char streamB){

	char speler =0;
	char data = 0;
	char control = 0;
	char list[3];
	
	
	for(int y = 1; y < 6; y++){
		if(((streamA << y) & 0x80) && y == 5){
			speler = speler | 0x01;
			printf("speler_end A1\n");
		}
		else if((streamA << y) & 0x80 ){
			speler = speler | 0x01;
			speler = speler << 1;
			printf("speler A1\n");
		}
		else{
			if(y == 5){
				printf("speler_end A0\n");
			}
			else{
				speler = speler << 1;
				printf("speler A0\n");
			}				
		}
	}
	printf("\n%d speler\n\n", speler);
	
	for(int y = 6; y < 11; y++){
		if(y > 7){
			if(((streamB << (y-8)) & 0x80) && y == 10 ){
				data = data | 0x01;
				printf("data_end B1\n");
			}
			else if((streamB << (y-8)) & 0x80 ){
				data = data | 0x01;
				data = data << 1;
				printf("data B1\n");
			}
			else{
				if(y == 10){
					printf("data_end B0\n");
				}
				else{
					data = data << 1;
					printf("data B0\n");
				}

			}				
		}
		else{
			if((streamA << y) & 0x80 ){
				data = data | 0x01;
				data = data << 1;
				printf("data A1\n");
			}
			else{
				data = data << 1;
				printf("data A0\n");
				}				
			}
	}
	
	printf("\n%d data\n\n", data);
	
	
	for(int y = 11; y < 16; y++){
		if(((streamB << (y-8)) & 0x80) && y == 15){
			control = control | 0x01;
			printf("control_end B1\n");
		}
		else if((streamB << (y-8)) & 0x80 ){
			control = control | 0x01;
			control = control << 1;
			printf("control B1\n");
		}
		else{
			if(y == 15){
				printf("control_end B0\n");
			}
			else{
				control = control << 1;
				printf("control B0\n");
			}				
		}
	}
	
	printf("\n%d control\n", control);
	list[0] = speler;
	list[1] = data;
	list[2] = control;
	
	return list;
	
}