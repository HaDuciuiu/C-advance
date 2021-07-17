
#include<stdio.h>
#include<math.h>
#include<time.h>
#include<locale.h>
#include<stdlib.h>

#include"soundex.h"

//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
void main(void)
{
    puts("-----------------");
    puts("| codedrome.com |");
    puts("| Soundex       |");
    puts("-----------------\n");

    char* names1[] = {"Johnson", "Adams", "Davis", "Simons", "Richards", "Taylor", "Carter", "Stevenson", "Taylor", "Smith", "McDonald", "Harris", "Sim", "Williams", "Baker", "Wells", "Fraser", "Jones", "Wilks", "Hunt", "Sanders", "Parsons", "Robson", "Harker"};

    char* names2[] = {"Jonson", "Addams", "Davies", "Simmons", "Richardson", "Tailor", "Chater", "Stephenson", "Naylor", "Smythe", "MacDonald", "Harrys", "Sym", "Wilson", "Barker", "Wills", "Frazer", "Johns", "Wilkinson", "Hunter", "Saunders", "Pearson", "Robertson", "Parker"};

    int namecount = sizeof(names1) / sizeof(names1[0]);

    char s1[] = "     ";
    char s2[] = "     ";

    for(int i = 0; i < namecount; i++)
    {
        soundex(names1[i], s1);
        soundex(names2[i], s2);

        printf("%-20s%-6s%-20s%-6s\n", names1[i], s1, names2[i], s2);
    }
}
