int main()
{
    char input;
    int upper = 100;
    int lower = 0;
    int interval = 50;
    int guess = (upper+lower)/2;

    while(input != '=') {
        printf("How about %d (<, =, >)?", guess);
        scanf("%s", &input);

        if (input == '=') {
           printf("It was a good game!\n");
            break;
        }
        else if(input == '<') {
            upper -= interval;
        }
        else if(input == '>') {
            lower += interval;
        }
        guess = (upper+lower)/2;
        if (interval != 1)
            interval /= 2;
        else
            interval = 1;
    }

    return 0;
}

