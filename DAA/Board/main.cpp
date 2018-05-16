#include <stdio.h>

unsigned short n = 0, m =0;
char board[1001][1001];

bool valid_move(unsigned short, unsigned short);
unsigned short component_sum(unsigned short, unsigned short);

int main()
{

    scanf("%hu %hu",&n, &m);

    char ch = ' ';
    for(unsigned short row = 0; row < n; ++row)
    {
        scanf("%c",&ch);

        for(unsigned short col = 0; col < m; ++col)
        {
            scanf("%c", &board[row][col]);
        }
        board[row][m] = '\n';
        board[row][m+1] = '0';
    }

     for(unsigned short row = 0; row < n; ++row)
    {
        for(unsigned short col = 0; col < m; ++col)
        {

        }
    }
    
    char result[1001][1001];

 /*    for(unsigned short row = 0; row < n; ++row)
    {
            printf("%s", result[row]);
    }
 */


    return 0;
}


short step[2] = {-1,1};

bool valid_move(unsigned short x, unsigned short y)
{
    return (x >=0 && x <= m) && (y >= 0 && y <=n);
}

unsigned short component_sum(unsigned short x,
                            unsigned short y)
{   
    if (board[y][x] == '*')
        return 0;
        
    unsigned short sum = 1;
    for (unsigned int i =0; i <= 1; ++i)
    {
        if(valid_move(x+step[i],y))
        {
            sum += component_sum(x+step[i],y);
        }
    }
    
    for (unsigned int i =0; i <= 1; ++i)
    {
        if(valid_move(x,y+step[i]))
        {
            sum += component_sum(x,y+step[i]);
        }
    }
}
