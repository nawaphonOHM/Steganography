#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void encoder();
void decoder();

int main(){

    char input, isDone = 0;

    do{
        printf("What kind of function are you perfer?\nencode[1]\ndecode[2]\ninput: ");
        scanf("%c", &input);
        if(input == '1'){
            encoder();
            isDone = 1;
        } else if(input == '2'){
            decoder();
            isDone = 1;
        } else { 
                printf("Your input did not match any function.\n");
                getchar();
            }
    } while(!isDone);

    return 0;
}

void encoder(){
    FILE* datas = fopen("./origin.gif", "rb");
    unsigned int size, counter;
    unsigned int textSize;
    unsigned int position;

    fseek(datas, 0, SEEK_END);
    size = ftell(datas);
    rewind(datas);

    char data[size];
    fread(&(data[0]), 1, size, datas);
    fclose(datas);

    printf("How much length do you perfer?: ");
    scanf("%u", &textSize);
    getchar();
    char text[textSize + 1];
    
    printf("Please give your favor message: ");
    scanf("%[0-9a-zA-z ]s", &(text[0]));

    srand(time(NULL));
    do{
        position = rand() % size;
    } while(size + 1 < textSize + position);  //size - position < textSize - 1

    for(counter = 0; counter < textSize && counter < size; counter++){
        data[position] = text[counter];
        position = position + 1;
    }

    datas = fopen("./modified.gif", "wb");
    fwrite(&(data[0]), 1, size, datas);
    fclose(datas);

    return;
}

void decoder(){
    FILE* originDatas = fopen("./origin.gif", "rb");
    FILE* newDatas = fopen("./modified.gif", "rb");
    char oldData, newData;
    unsigned int size, counter;
    unsigned char hasMessage = 0;

    fseek(originDatas, 0, SEEK_END);
    size = ftell(originDatas);
    rewind(originDatas);


    for(counter = 0; counter < size; counter++){
        fread(&oldData, 1, 1, originDatas);
        fread(&newData, 1, 1, newDatas);

        if(oldData != newData && hasMessage == 0){
            printf("There is a message: ");
            hasMessage = 1;
        }
        if(oldData != newData) printf("%c", newData);
    }

    if(!hasMessage) printf("There is no a message.");

    printf("\n");

    return;
}
